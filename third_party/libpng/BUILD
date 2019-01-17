# Code from http://prdownloads.sourceforge.net/libpng/libpng-1.6.35.tar.xz?download

# Copyright 2018 Josh Pieper, jjp@pobox.com.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

load(
    "//bzl:autoconf_config.bzl",
    "autoconf_config",
    "autoconf_standard_defines",
)

licenses(["notice"])  # permissive

package(default_visibility = ["//visibility:public"])

cc_library(
    name = "libpng",
    srcs = [
        "pngconf.h",
        "pngdebug.h",
        "png.h",
        "pnginfo.h",
        "pngpriv.h",
        "pngstruct.h",
        "pnglibconf.h",
        "config.h",  # FIXME: should be in private directory
        "png.c",
        "pngerror.c",
        "pngget.c",
        "pngmem.c",
        "pngpread.c",
        "pngread.c",
        "pngrio.c",
        "pngrtran.c",
        "pngrutil.c",
        "pngset.c",
        "pngtrans.c",
        "pngwio.c",
        "pngwrite.c",
        "pngwtran.c",
        "pngwutil.c",
    ] + select({
        "//bzl/constraints:arm": [
            "arm/arm_init.c",
            "arm/filter_neon.S",
            "arm/filter_neon_intrinsics.c",
        ],
        "//bzl/constraints:x86_64": [
            "intel/filter_sse2_intrinsics.c",
            "intel/intel_init.c",
        ],
    }),
    hdrs = [
        "png.h",
        "pngconf.h",
        "pngdebug.h",
        "pnginfo.h",
        "pnglibconf.h",
        "pngpriv.h",
        "pngstruct.h",
    ],
    copts = [
        "-DHAVE_CONFIG_H",
        "-I$(GENDIR)/third_party/libpng/private",
    ],
    include_prefix = "libpng",
    includes = ["."],
    deps = ["@net_zlib_zlib//:zlib"],
)

autoconf_config(
    name = "config.h",  # FIXME: should be in private directory
    src = "config.h.in",
    defines = autoconf_standard_defines + select({
        "//bzl/constraints:arm": [
            "PNG_ARM_NEON_OPT=0",
        ],
        "//bzl/constraints:x86_64": [
            "PNG_INTEL_SSE_OPT",
        ],
    }),
    package = "libpng",
    version = "1.6.35",
)

genrule(
    name = "pnglibconf",
    srcs = ["scripts/pnglibconf.h.prebuilt"],
    outs = ["pnglibconf.h"],
    cmd = "cp $< $@",
)
