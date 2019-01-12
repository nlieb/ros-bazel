# Source derived from https://svwh.dl.sourceforge.net/project/libjpeg/libjpeg/6b/jpegsrc.v6b.tar.gz
# with addition of jconfig.h

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

package(default_visibility = ["//visibility:public"])

licenses(["notice"])  # permissive

cc_library(
    name = "libjpeg",
    srcs = [
        "cderror.h",
        "cdjpeg.h",
        "jcapimin.c",
        "jcapistd.c",
        "jccoefct.c",
        "jccolor.c",
        "jcdctmgr.c",
        "jchuff.c",
        "jchuff.h",
        "jcinit.c",
        "jcmainct.c",
        "jcmarker.c",
        "jcmaster.c",
        "jcomapi.c",
        "jcparam.c",
        "jcphuff.c",
        "jcprepct.c",
        "jcsample.c",
        "jctrans.c",
        "jdapimin.c",
        "jdapistd.c",
        "jdatadst.c",
        "jdatasrc.c",
        "jdcoefct.c",
        "jdcolor.c",
        "jdct.h",
        "jddctmgr.c",
        "jdhuff.c",
        "jdhuff.h",
        "jdinput.c",
        "jdmainct.c",
        "jdmarker.c",
        "jdmaster.c",
        "jdmerge.c",
        "jdphuff.c",
        "jdpostct.c",
        "jdsample.c",
        "jdtrans.c",
        "jerror.c",
        "jfdctflt.c",
        "jfdctfst.c",
        "jfdctint.c",
        "jidctflt.c",
        "jidctfst.c",
        "jidctint.c",
        "jidctred.c",
        "jinclude.h",
        "jmemansi.c",
        "jmemmgr.c",
        "jmemsys.h",
        "jpegint.h",
        "jquant1.c",
        "jquant2.c",
        "jutils.c",
        "jversion.h",
        "transupp.h",
    ],
    hdrs = [
        "jconfig.h",
        "jerror.h",
        "jmorecfg.h",
        "jpeglib.h",
    ],
    copts = [
        "-Wno-main",
        "-Wno-shift-negative-value",
    ],
    includes = ["."],
)
