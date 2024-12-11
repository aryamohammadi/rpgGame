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

# Specify the include directory for MainMenuTests
add_executable(MainMenuTests
    Main_Menu/Tests/MainMenuTests.cpp
    Main_Menu/CPP_Files/MainMenu.cpp
)
target_include_directories(MainMenuTests PRIVATE ${CMAKE_SOURCE_DIR}/header)
target_link_libraries(MainMenuTests gtest gtest_main pthread)

# Add executable for the MainMenuSim program
add_executable(MainMenuSim
    Main_Menu/CPP_Files/main.cpp
    Main_Menu/CPP_Files/MainMenu.cpp
)

# Link necessary libraries for MainMenuSim
target_link_libraries(MainMenuSim pthread)

# Add MainMenuTests to CTest
add_test(NAME MainMenuTests COMMAND MainMenuTests)
