set(zeta80_cfiles
    opcodes.c
    )

set(zeta80_hfiles
    cpu.h
    opcodes.h
    types.h
    )

add_library(zeta80 STATIC ${zeta80_cfiles} ${zeta80_hfiles})

target_include_directories(zeta80 PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

install(TARGETS zeta80 DESTINATION lib)
install(FILES ${zeta80_hfiles} DESTINATION include/zeta80)

