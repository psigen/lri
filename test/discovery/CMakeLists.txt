enable_testing()
include_directories(${gtest_INCLUDE_DIRS})

# Discovery tests
add_executable(discovery_test discovery_test.cc)
target_link_libraries(discovery_test ${gtest_LIBRARIES})
add_test(run_discovery_test ${CMAKE_CURRENT_BINARY_DIR}/discovery_test)
