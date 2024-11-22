cmake_minimum_required(VERSION 3.13)

# Project name
project(final_project VERSION 1.0)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Enable testing
enable_testing()

# Add GoogleTest subdirectory
add_subdirectory(googletest)

# Include directories
include_directories(
    Difficulty/CPP_Files
    Main_Menu/CPP_Files
)


# Add MainMenu tests
add_executable(MainMenuTests
    Main_Menu/Tests/MainMenuTests.cpp
    Main_Menu/CPP_Files/MainMenu.cpp
)
target_link_libraries(MainMenuTests gtest gtest_main pthread)

# Add all executables to CTest
add_test(NAME DifficultyTests COMMAND DifficultyTests)
add_test(NAME MainMenuTests COMMAND MainMenuTests)
