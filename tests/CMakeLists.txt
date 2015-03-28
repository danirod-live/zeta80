enable_testing()

include_directories(${z80_SOURCE_DIR}/libzeta80/include)

set(tests_src
    zeta80_test.c
    cpu_test.c
    opcodes_test.c
    )

set(tests_inc
    cpu_test.h
    opcodes_test.h
    )

add_executable(zeta80_test ${tests_src} ${tests_inc})
target_link_libraries(zeta80_test ${CHECK_LIBRARIES} zeta80)
add_test(zeta80_test ${CMAKE_CURRENT_BINARY_DIR}/zeta80_test)
