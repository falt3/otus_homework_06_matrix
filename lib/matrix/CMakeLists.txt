add_library(matrix_lib matrix.h)

target_link_libraries(matrix_lib helper_lib)

target_include_directories(matrix_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})