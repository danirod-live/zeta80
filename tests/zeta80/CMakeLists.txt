include_directories(${z80_SOURCE_DIR}/libzeta80/include)
add_executable(zetatest zetatest.c)
target_link_libraries(zetatest ${CHECK_LIBRARIES} zeta80)
add_test(zetatest ${CMAKE_CURRENT_BINARY_DIR}/zetatest)
