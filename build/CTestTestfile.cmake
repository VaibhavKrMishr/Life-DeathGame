# CMake generated Testfile for 
# Source directory: /home/vaibhav/Desktop/Projects/LifeAndDeathGame
# Build directory: /home/vaibhav/Desktop/Projects/LifeAndDeathGame/build
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test("GameOfLifeTests" "/home/vaibhav/Desktop/Projects/LifeAndDeathGame/build/GameOfLifeTests")
set_tests_properties("GameOfLifeTests" PROPERTIES  _BACKTRACE_TRIPLES "/home/vaibhav/Desktop/Projects/LifeAndDeathGame/CMakeLists.txt;95;add_test;/home/vaibhav/Desktop/Projects/LifeAndDeathGame/CMakeLists.txt;0;")
subdirs("_deps/sfml-build")
subdirs("_deps/json-build")
subdirs("_deps/googletest-build")
