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

# Add all executables to CTest
add_test(NAME DifficultyTests COMMAND DifficultyTests)


# Add the difficulty simulation executable 
add_executable(DifficultySim
    CPP_Files/Difficulty.cpp
    CPP_Files/main.cpp
    CPP_Files/MainMenu.cpp
    CPP_Files/combat.cpp
    CPP_Files/item.cpp
    CPP_Files/itemStack.cpp
    CPP_Files/compare.cpp
    CPP_Files/inventory.cpp
    CPP_Files/weapon.cpp
    CPP_Files/potion.cpp
    CPP_Files/armour.cpp
    CPP_Files/character.cpp
    CPP_Files/mergeSortItem.cpp
    CPP_Files/Heap.cpp
    CPP_Files/LoadGame.cpp
    CPP_Files/SaveGame.cpp
    CPP_Files/Room.cpp
    CPP_Files/Map.cpp
    CPP_Files/Game.cpp
)
target_link_libraries(DifficultySim pthread)


# Add Difficulty tests
add_executable(DifficultyTests
    Tests/DifficultyTests.cpp
    CPP_Files/Difficulty.cpp
    CPP_Files/main.cpp
    CPP_Files/MainMenu.cpp
    CPP_Files/combat.cpp
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
    CPP_Files/LoadGame.cpp
    CPP_Files/SaveGame.cpp
    CPP_Files/Room.cpp
    CPP_Files/Map.cpp
    CPP_Files/Game.cpp
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
    CPP_Files/compare.cpp
    CPP_Files/Heap.cpp
    CPP_Files/character.cpp
    CPP_Files/potion.cpp
    Tests/HungryCharacterTest.cpp
    Tests/HungryInventory&ItemTest.cpp
    Tests/HungrySortTest.cpp
    CPP_Files/Map.cpp
    CPP_Files/Room.cpp
)

# Specify the include directory after defining the target
target_include_directories(Test PRIVATE ${CMAKE_SOURCE_DIR}/header)

# Link GoogleTest libraries
target_link_libraries(Test gmock gtest gtest_main)


# Add executable for the MainMenuSim program
add_executable(MainMenuSim
    CPP_Files/main.cpp
    CPP_Files/MainMenu.cpp
    CPP_Files/Difficulty.cpp
    CPP_Files/combat.cpp
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
    CPP_Files/LoadGame.cpp
    CPP_Files/SaveGame.cpp
    CPP_Files/Room.cpp
    CPP_Files/Map.cpp
    CPP_Files/Game.cpp
)


# Add MainMenu tests
add_executable(MainMenuTests
    Tests/MainMenuTests.cpp
    CPP_Files/MainMenu.cpp
    CPP_Files/Difficulty.cpp
    CPP_Files/main.cpp
    CPP_Files/combat.cpp
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
    CPP_Files/LoadGame.cpp
    CPP_Files/SaveGame.cpp
    CPP_Files/Room.cpp
    CPP_Files/Map.cpp
    CPP_Files/Game.cpp
    CPP_Files/MainMenu.cpp
)
target_link_libraries(MainMenuTests gtest gtest_main pthread)

# Add all executables to CTest
add_test(NAME MainMenuTests COMMAND MainMenuTests)


# Add the test files
# add_executable(LoadGameTests Save_Load/Tests/LoadGameTests.cpp) //commented as not in master yet. Uncomment on your local branch until in master
# add_executable(SaveGameTests Save_Load/Tests/SaveGameTests.cpp)

# Link Google Test libraries
# target_link_libraries(LoadGameTests gtest gtest_main)
# target_link_libraries(SaveGameTests gtest gtest_main)

#Add Combat test executable
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
# Specify include directories for CombatTests
target_include_directories(CombatTests PRIVATE ${CMAKE_SOURCE_DIR}/header)

# Link Google Test libraries
target_link_libraries(CombatTests gmock gtest gtest_main)

# Add to CTest
add_test(NAME CombatTests COMMAND CombatTests)

add_executable(Game
CPP_Files/combat.cpp
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
CPP_Files/Difficulty.cpp
CPP_Files/LoadGame.cpp
CPP_Files/SaveGame.cpp
CPP_Files/Room.cpp
CPP_Files/Map.cpp
CPP_Files/Game.cpp
CPP_Files/main.cpp
CPP_Files/MainMenu.cpp

)

# Specify include directories for CombatTests
target_include_directories(Game PRIVATE ${CMAKE_SOURCE_DIR}/header)

target_include_directories(DifficultySim PRIVATE ${CMAKE_SOURCE_DIR}/header)
target_include_directories(DifficultyTests PRIVATE ${CMAKE_SOURCE_DIR}/header)
target_include_directories(MainMenuTests PRIVATE ${CMAKE_SOURCE_DIR}/header)
target_include_directories(MainMenuSim PRIVATE ${CMAKE_SOURCE_DIR}/header)
target_include_directories(Game PRIVATE ${CMAKE_SOURCE_DIR}/header)
