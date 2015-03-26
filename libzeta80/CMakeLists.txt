add_library(zeta80 STATIC
    cpu.h
    opcodes.c
    opcodes.h
    types.h
    )

target_include_directories(zeta80 PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

