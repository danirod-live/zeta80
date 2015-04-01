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

# Initialize testing framework.
include(CTest)
find_package(Check REQUIRED)
enable_testing()

# Source files for our test units.
set(ZETA80_TEST_SRC
    zeta80_test.c
    cpu_test.c
    opcodes_test.c
    opcodes_test/extract_opcodes.c
    opcodes_test/x0_z0.c
    opcodes_test/x0_z1.c
    opcodes_test/x0_z2.c
    opcodes_test/x0_z3.c
    )

set(ZETA80_TEST_INCLUDE
    cpu_test.h
    opcodes_test.h
    )

# Generate test program using Check.
include_directories(${ZETA80_INCLUDE})
add_executable(zeta80_test ${ZETA80_TEST_SRC})
target_link_libraries(zeta80_test ${CHECK_LIBRARIES} zeta80)

# Add this target as a unit test for CUnit.
add_test(zeta80_test ${CMAKE_CURRENT_BINARY_DIR}/zeta80_test)
