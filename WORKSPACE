workspace(name = "ros_bazel")

SOURCEFORGE_MIRRORS = [
    "phoenixnap",
    "newcontinuum",
    "cfhcable",
    "superb-sea2",
    "cytranet",
    "iweb",
    "gigenet",
    "ayera",
    "astuteinternet",
    "pilotfiber",
    "svwh",
]

new_http_archive(
    name = "clang_toolchain",
    build_file = "third_party/BUILD.clang-toolchain",
    strip_prefix = "clang+llvm-7.0.0-x86_64-linux-gnu-ubuntu-14.04",
    url = "http://releases.llvm.org/7.0.0/clang+llvm-7.0.0-x86_64-linux-gnu-ubuntu-14.04.tar.xz",
)

new_local_repository(
    name = "sysroot_amd64_xenial_linux_gnu",
    build_file = "third_party/BUILD.sysroot",
    path = "/home/nathan/trusty-sysroot",
)

new_http_archive(
    name = "net_zlib_zlib",
    build_file = "third_party/BUILD.zlib",
    sha256 = "c3e5e9fdd5004dcb542feda5ee4f0ff0744628baf8ed2dd5d66f8ca1197cb1a1",
    strip_prefix = "zlib-1.2.11",
    urls = [
        "https://mirror.bazel.build/zlib.net/zlib-1.2.11.tar.gz",
        "https://zlib.net/zlib-1.2.11.tar.gz",
    ],
)

new_http_archive(
    name = "org_bzip_bzip2",
    build_file = "third_party/BUILD.bzip2",
    sha256 = "a2848f34fcd5d6cf47def00461fcb528a0484d8edef8208d6d2e2909dc61d9cd",
    strip_prefix = "bzip2-1.0.6",
    urls = [
        "https://mirror.bazel.build/www.bzip.org/1.0.6/bzip2-1.0.6.tar.gz",
        "http://www.bzip.org/1.0.6/bzip2-1.0.6.tar.gz",
    ],
)

new_http_archive(
    name = "org_lzma_lzma",
    build_file = "third_party/BUILD.lzma",
    sha256 = "71928b357d0a09a12a4b4c5fafca8c31c19b0e7d3b8ebb19622e96f26dbf28cb",
    strip_prefix = "xz-5.2.3",
    urls = [
        "https://%s.dl.sourceforge.net/project/lzmautils/xz-5.2.3.tar.gz" % m
        for m in SOURCEFORGE_MIRRORS
    ],
)

git_repository(
    name = "com_github_nelhage_rules_boost",
    commit = "6d6fd834281cb8f8e758dd9ad76df86304bf1869",
    remote = "https://github.com/nelhage/rules_boost",
)

new_http_archive(
    name = "boost",
    build_file = "@com_github_nelhage_rules_boost//:BUILD.boost",
    sha256 = "8aa4e330c870ef50a896634c931adf468b21f8a69b77007e45c444151229f665",
    strip_prefix = "boost_1_67_0",
    urls = [
        "https://%s.dl.sourceforge.net/project/boost/boost/1.67.0/boost_1_67_0.tar.gz" % m
        for m in SOURCEFORGE_MIRRORS
    ],
)

new_http_archive(
    name = "opencv",
    build_file = "third_party/BUILD.opencv",
    sha256 = "4eef85759d5450b183459ff216b4c0fa43e87a4f6aa92c8af649f89336f002ec",
    strip_prefix = "opencv-3.4.3",
    urls = [
        "https://github.com/opencv/opencv/archive/3.4.3.tar.gz",
    ],
)

new_http_archive(
    name = "eigen",
    build_file = "third_party/BUILD.eigen",
    sha256 = "dd254beb0bafc695d0f62ae1a222ff85b52dbaa3a16f76e781dce22d0d20a4a6",
    strip_prefix = "eigen-eigen-5a0156e40feb",
    urls = [
        "http://bitbucket.org/eigen/eigen/get/3.3.4.tar.bz2",
    ],
)
