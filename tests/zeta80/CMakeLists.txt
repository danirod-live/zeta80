include_directories(${z80_SOURCE_DIR}/libzeta80/include)

set(tests_src
    zetatest.c
    cpu_test.c
    )

set(tests_inc
    cpu_test.h
    )

add_executable(zetatest ${tests_src} ${tests_inc})
target_link_libraries(zetatest ${CHECK_LIBRARIES} zeta80)
add_test(zetatest ${CMAKE_CURRENT_BINARY_DIR}/zetatest)
