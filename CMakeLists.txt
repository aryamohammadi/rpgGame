cmake_minimum_required(VERSION 3.13)

# Project name
project(final_project VERSION 1.0)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE Debug)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/bin")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/lib")

# Enable testing
enable_testing()

# Add GoogleTest subdirectory
add_subdirectory(googletest)

# Main game executable
add_executable(RunGame
    CPP_Files/Game.cpp
    CPP_Files/MainMenu.cpp
    CPP_Files/Map.cpp
    CPP_Files/Difficulty.cpp
    CPP_Files/character.cpp
    CPP_Files/item.cpp
    CPP_Files/weapon.cpp
    CPP_Files/armour.cpp
    CPP_Files/potion.cpp
    CPP_Files/inventory.cpp
    CPP_Files/itemStack.cpp
    CPP_Files/Room.cpp
    CPP_Files/main.cpp
)

# Specify include directories
target_include_directories(RunGame PRIVATE ${CMAKE_SOURCE_DIR}/header)

# Add library dependencies
target_link_libraries(RunGame pthread)

# Add test executables

# Difficulty Tests
add_executable(DifficultyTests
    Tests/DifficultyTests.cpp
    CPP_Files/Difficulty.cpp
    CPP_Files/MainMenu.cpp
    CPP_Files/main.cpp
)

target_include_directories(DifficultyTests PRIVATE ${CMAKE_SOURCE_DIR}/header)
target_link_libraries(DifficultyTests gtest gtest_main pthread)
add_test(NAME DifficultyTests COMMAND DifficultyTests)

# Main Menu Tests
add_executable(MainMenuTests
    Tests/MainMenuTests.cpp
    CPP_Files/MainMenu.cpp
    CPP_Files/Difficulty.cpp
    CPP_Files/Game.cpp
)

target_include_directories(MainMenuTests PRIVATE ${CMAKE_SOURCE_DIR}/header)
target_link_libraries(MainMenuTests gtest gtest_main pthread)
add_test(NAME MainMenuTests COMMAND MainMenuTests)

# Combat Tests
add_executable(CombatTests
    CPP_Files/combat.cpp
    Tests/combat_test.cpp
    CPP_Files/item.cpp
    CPP_Files/itemStack.cpp
    CPP_Files/inventory.cpp
    CPP_Files/weapon.cpp
    CPP_Files/potion.cpp
    CPP_Files/armour.cpp
    CPP_Files/character.cpp
    CPP_Files/mergeSortItem.cpp
    CPP_Files/compare.cpp
    CPP_Files/Heap.cpp
)

target_include_directories(CombatTests PRIVATE ${CMAKE_SOURCE_DIR}/header)
target_link_libraries(CombatTests gmock gtest gtest_main)
add_test(NAME CombatTests COMMAND CombatTests)

# Save/Load Game Tests (Uncomment these if the tests exist)
# add_executable(SaveGameTests Save_Load/Tests/SaveGameTests.cpp)
# target_include_directories(SaveGameTests PRIVATE ${CMAKE_SOURCE_DIR}/header)
# target_link_libraries(SaveGameTests gtest gtest_main)
# add_test(NAME SaveGameTests COMMAND SaveGameTests)

# add_executable(LoadGameTests Save_Load/Tests/LoadGameTests.cpp)
# target_include_directories(LoadGameTests PRIVATE ${CMAKE_SOURCE_DIR}/header)
# target_link_libraries(LoadGameTests gtest gtest_main)
# add_test(NAME LoadGameTests COMMAND LoadGameTests)
