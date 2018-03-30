add_executable (Test test.cpp)
target_link_libraries(Test gtest)
add_test(NAME MyTest COMMAND Test)
