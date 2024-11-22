# CMake generated Testfile for 
# Source directory: /home/csmajs/rjour001/final-project-the-computer-enthusiasts
# Build directory: /home/csmajs/rjour001/final-project-the-computer-enthusiasts/build
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(DifficultyTests "/home/csmajs/rjour001/final-project-the-computer-enthusiasts/build/DifficultyTests")
set_tests_properties(DifficultyTests PROPERTIES  _BACKTRACE_TRIPLES "/home/csmajs/rjour001/final-project-the-computer-enthusiasts/CMakeLists.txt;44;add_test;/home/csmajs/rjour001/final-project-the-computer-enthusiasts/CMakeLists.txt;0;")
add_test(MainMenuTests "/home/csmajs/rjour001/final-project-the-computer-enthusiasts/build/MainMenuTests")
set_tests_properties(MainMenuTests PROPERTIES  _BACKTRACE_TRIPLES "/home/csmajs/rjour001/final-project-the-computer-enthusiasts/CMakeLists.txt;45;add_test;/home/csmajs/rjour001/final-project-the-computer-enthusiasts/CMakeLists.txt;0;")
subdirs("googletest")
