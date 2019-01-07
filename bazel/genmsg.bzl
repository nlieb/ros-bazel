RosmsgFiles = provider("transitive_sources")

def get_transitive_srcs(srcs, deps):
    """Obtain the source files for a target and its transitive dependencies.
    Args:
      srcs: a list of source files
      deps: a list of targets that are direct dependencies
    Returns:
      a collection of the transitive sources
    """
    return depset(
        srcs,
        transitive = [dep[RosmsgFiles].transitive_sources for dep in deps],
    )

def _rosmsg_library_impl(ctx):
    trans_srcs = get_transitive_srcs(ctx.files.srcs, ctx.attr.deps)
    return [
        RosmsgFiles(transitive_sources = trans_srcs),
        DefaultInfo(files = trans_srcs),
    ]

rosmsg_library = rule(
    implementation = _rosmsg_library_impl,
    attrs = {
        "srcs": attr.label_list(allow_files = True),
        "deps": attr.label_list(),
    },
)

def _cc_rosmsg_library_impl(ctx):
    gen_cpp = ctx.executable._gen_cpp
    print(ctx.build_file_path)
    trans_srcs = get_transitive_srcs([ctx.file.src], ctx.attr.deps)
    pkg = ctx.attr.pkg
    srcs_list = trans_srcs.to_list()
    src_filename = ctx.file.src.basename
    out_filename = src_filename.split(".")[-2] + ".h"

    out = ctx.actions.declare_file(out_filename)
    ctx.actions.run(
        executable = gen_cpp,
        arguments = ["-p%s" % pkg, "-o%s" % out.dirname] +
                    ["-I" + src.dirname for src in srcs_list] +  # TODO: remove dups
                    [ctx.file.src.path],
        inputs = srcs_list,
        tools = [gen_cpp],
        outputs = [out],
    )
    return [DefaultInfo(files = depset([out]))]

cc_rosmsg_library = rule(
    implementation = _cc_rosmsg_library_impl,
    attrs = {
        "src": attr.label(allow_single_file = [".msg"]),
        "pkg": attr.string(mandatory = True),
        "deps": attr.label_list(),
        "_gen_cpp": attr.label(
            default = Label("//third_party/py/gencpp:gen_cpp"),
            allow_files = True,
            executable = True,
            cfg = "host",
        ),
    },
)
