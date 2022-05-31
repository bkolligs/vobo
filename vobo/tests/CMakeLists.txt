find_package(GTest REQUIRED)

add_executable(test_one test.cpp)
target_link_libraries(test_one vobo ${GTEST_LIBRARIES} pthread)

gtest_discover_tests(test_one)