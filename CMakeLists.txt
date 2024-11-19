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

# Add main program executable
add_executable(main_program
  Main_Menu/src/main.cpp
  Main_Menu/src/MainMenu.cpp
)

# Link the main program with necessary libraries
target_link_libraries(main_program gtest gtest_main)

# Add test executable for unit tests
add_executable(unit_tests
  Main_Menu/tests/MainMenuTests.cpp  # Replace with the path to your test files
  Main_Menu/src/MainMenu.cpp
)

# Link the unit test executable with GoogleTest
target_link_libraries(unit_tests gtest gtest_main)

# Add unit tests to the CTest framework
add_test(NAME MainMenuTests COMMAND unit_tests)
