cmake_minimum_required(VERSION 3.20)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/bin")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/lib")
add_subdirectory(test/googletest)

add_executable(Test
    CPPFiles/item.cpp
    CPPFiles/inventory.cpp
    Tests/Test.cpp 
)

target_link_libraries(Test gmock gtest gtest_main)


