# CMakeLists.txt for libzeta80
# Description: libzeta80 is the core library that emulates a Z80 CPU.
# This CMakeLists describes how to properly build the library.

# Header files are in include/ folder, source files are in src/ folder.
include_directories(include)

# Header files. If you create a new header file, don't forget to list it here.
set(zeta_h
    include/cpu.h
    include/opcodes.h
    include/types.h
    )

# Source files. IF you create a new source file, don't forget to list it here.
set(zeta_c
    src/opcodes.c
    )

# libzeta80 is a library. Build library using header and source files.
add_library(zeta80 SHARED ${zeta_c} ${zeta_h})

# This library can be globally installed onto your system so that you can
# build your own software on top of this library. Copy library into lib/
# and source files into include/.
install(TARGETS zeta80 DESTINATION lib)
install(FILES ${zeta_h} DESTINATION include/zeta80)
