# zeta80 configuration script
# This script is intented to be used by CMake
# Copyright (c) 2015, Dani Rodríguez
# All rights reserved.
# 
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions
# are met:
# 
# * Redistributions of source code must retain the above copyright notice,
#   this list of conditions and the following disclaimer.
# 
# * Redistributions in binary form must reproduce the above copyright
#   notice, this list of conditions and the following disclaimer in the
#   documentation and/or other materials provided with the distribution.
# 
# * Neither the name of the project's author nor the names of its
#   contributors may be used to endorse or promote products derived from
#   this software without specific prior written permission.
# 
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
# "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
# LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
# for a particular purpose are disclaimed. in no event shall the copyright
# holder or contributors be liable for any direct, indirect, incidental,
# special, exemplary, or consequential damages (including, but not limited
# to, procurement of substitute goods or services; loss of use, data, or
# profits; or business interruption) however caused and on any theory of
# liability, whether in contract, strict liability, or tort (including
# negligence or otherwise) arising in any way out of the use of this
# software, even if advised of the possibility of such damage.

# Header files are on include/ folder.
include_directories(${ZETA80_INCLUDE})

# Source code files. If you add a new source code file, list it here.
set(ZETA80_SOURCE_FILES
    opcodes.c
    )

# libzeta80 is a library. Build library using header and source files.
add_library(zeta80 SHARED ${ZETA80_SOURCE_FILES})

# Install library and all header files.
install(TARGETS zeta80 DESTINATION lib)
install(DIRECTORY ${ZETA80_INCLUDE}
    DESTINATION include/zeta80
    FILES_MATCHING PATTERN "*.h")
