add_executable(zetatest zetatest.c)
target_link_libraries(zetatest ${CHECK_LIBRARIES} zeta80)
add_test(zetatest ${CMAKE_CURRENT_BINARY_DIR}/zetatest)
