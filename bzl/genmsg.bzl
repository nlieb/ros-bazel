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

def _cc_rosmsg_library_impl(ctx):
    gen_cpp = ctx.executable._gen_cpp
    trans_srcs = get_transitive_srcs([ctx.file.src], ctx.attr.deps)
    pkg = ctx.attr.pkg
    srcs_list = trans_srcs.to_list()
    src_filename = ctx.file.src.basename

    out_filename = src_filename.split(".")[-2]
    outs = [ctx.actions.declare_file(out_filename + ".h")]
    if src_filename.endswith(".srv"):
        outs.append(ctx.actions.declare_file(out_filename + "Request.h"))
        outs.append(ctx.actions.declare_file(out_filename + "Response.h"))

    includes = []
    for src in srcs_list:
        dirname = src.dirname
        pkg = dirname.split("/")[-2]
        includes.append("-I%s:%s" % (pkg, dirname))

    ctx.actions.run(
        executable = gen_cpp,
        arguments = ["-p%s" % pkg, "-o%s" % outs[0].dirname] +
                    includes +  # TODO: remove dups
                    [ctx.file.src.path],
        inputs = srcs_list,
        tools = [gen_cpp],
        outputs = outs,
    )

    transitive_out_list = []
    for dep in ctx.attr.deps:
        transitive_out_list += [file for file in dep[DefaultInfo].files if not file.is_source]

    transitive_outs = depset(
        outs,
        transitive = [depset(transitive_out_list)],
    )
    return [
        RosmsgFiles(transitive_sources = trans_srcs),
        DefaultInfo(files = transitive_outs),
    ]

cc_rosmsg_library = rule(
    implementation = _cc_rosmsg_library_impl,
    attrs = {
        "src": attr.label(allow_single_file = [".msg", ".srv"]),
        "pkg": attr.string(mandatory = True),
        "deps": attr.label_list(),
        "_gen_cpp": attr.label(
            default = Label("//third_party/py/gencpp:gen_cpp"),
            allow_files = True,
            executable = True,
            cfg = "host",
        ),
    },
    output_to_genfiles = True,
)
