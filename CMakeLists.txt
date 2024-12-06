cmake_minimum_required(VERSION 3.10)
project(SaveLoadTests)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)

# Add Google Test subdirectory (if it's included in your project)
add_subdirectory(googletest)

# Include directories
include_directories(
    ${CMAKE_SOURCE_DIR}/header
    ${CMAKE_SOURCE_DIR}/Save_Load/header
)

# Add source files
set(SOURCE_FILES
    CPP_Files/Game.cpp
    Save_Load/CPP_Files/SaveGame.cpp
    Save_Load/CPP_Files/LoadGame.cpp
)

# Add test files
set(TEST_FILES
    Save_Load/Tests/SaveGameTests.cpp
    Save_Load/Tests/LoadGameTests.cpp
)

# Add the test executable
add_executable(SaveLoadTests ${SOURCE_FILES} ${TEST_FILES})

# Link Google Test libraries and pthread
target_link_libraries(SaveLoadTests gtest gtest_main pthread)
