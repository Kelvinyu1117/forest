include(CTest)

add_executable(test_bst test_bst.cpp)
target_link_libraries(test_bst PRIVATE forest Catch2::Catch2WithMain)
