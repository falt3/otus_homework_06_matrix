add_executable(matrix_test test.cpp)

find_package(GTest)

target_include_directories(matrix_test PRIVATE ${GTEST_INCLUDE_DIRS})

target_link_libraries(matrix_test PRIVATE 
    ${GTEST_BOTH_LIBRARIES}
    matrix_lib
)

add_test(
    NAME test1 
    COMMAND ${PROJECT_NAME}_test
)