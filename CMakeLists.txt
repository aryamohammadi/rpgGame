cmake_minimum_required(VERSION 3.13)

# Project name
project(final_project VERSION 1.0)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/bin")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/lib")

# Enable testing
enable_testing()

# Add GoogleTest subdirectory
add_subdirectory(googletest)

# Add all executables to CTest
add_test(NAME DifficultyTests COMMAND DifficultyTests)

# Add the difficulty simulation executable 
add_executable(DifficultySim
    Difficulty/CPP_Files/Difficulty.cpp
    Difficulty/CPP_Files/main.cpp
)
target_link_libraries(DifficultySim pthread)

# Add Difficulty tests
add_executable(DifficultyTests
    Difficulty/Tests/DifficultyTests.cpp
    Difficulty/CPP_Files/Difficulty.cpp
)
target_link_libraries(DifficultyTests gtest gtest_main pthread)


