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


# Add Other Tests
add_executable(Test
    CPP_Files/item.cpp
    CPP_Files/inventory.cpp
    CPP_Files/itemStack.cpp
    CPP_Files/mergeSortItem.cpp
    CPP_Files/armour.cpp
    CPP_Files/weapon.cpp
    Tests/HungryInventory&ItemTest.cpp
    Tests/HungrySortTest.cpp
    CPP_Files/Map.cpp
    CPP_Files/Room.cpp
    CPP_Files/Enemy.cpp
)

# Specify the include directory after defining the target
target_include_directories(Test PRIVATE ${CMAKE_SOURCE_DIR}/header)

# Link GoogleTest libraries
target_link_libraries(Test gmock gtest gtest_main)


# Add executable for the MainMenuSim program
add_executable(MainMenuSim
    Main_Menu/CPP_Files/main.cpp
    Main_Menu/CPP_Files/MainMenu.cpp
)


# Add MainMenu tests
add_executable(MainMenuTests
    Main_Menu/Tests/MainMenuTests.cpp
    Main_Menu/CPP_Files/MainMenu.cpp
)
target_link_libraries(MainMenuTests gtest gtest_main pthread)

# Add all executables to CTest
add_test(NAME MainMenuTests COMMAND MainMenuTests)
