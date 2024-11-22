cmake_minimum_required(VERSION 3.20)


set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/bin")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/lib")


add_subdirectory(googletest)

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
