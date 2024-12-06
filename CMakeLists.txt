cmake_minimum_required(VERSION 3.10)
project(SaveLoadGameTests)

set(CMAKE_CXX_STANDARD 17)

# Add Google Test
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

# Add source files
add_executable(SaveLoadGameTests
    test_SaveLoadGame.cpp
    CPP_Files/SaveGame.cpp
    CPP_Files/LoadGame.cpp
)

# Link Google Test
target_link_libraries(SaveLoadGameTests ${GTEST_LIBRARIES} pthread)