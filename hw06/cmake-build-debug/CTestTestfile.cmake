# CMake generated Testfile for 
# Source directory: C:/Users/ktwic/Documents/CC/hw06
# Build directory: C:/Users/ktwic/Documents/CC/hw06/cmake-build-debug
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(Test_model_test "model_test")
set_tests_properties(Test_model_test PROPERTIES  _BACKTRACE_TRIPLES "C:/Users/ktwic/Documents/CC/hw06/.cs211/cmake/211commands.cmake;47;add_test;C:/Users/ktwic/Documents/CC/hw06/CMakeLists.txt;24;add_test_program;C:/Users/ktwic/Documents/CC/hw06/CMakeLists.txt;0;")
add_test(Test_helper_test "helper_test")
set_tests_properties(Test_helper_test PROPERTIES  _BACKTRACE_TRIPLES "C:/Users/ktwic/Documents/CC/hw06/.cs211/cmake/211commands.cmake;47;add_test;C:/Users/ktwic/Documents/CC/hw06/CMakeLists.txt;31;add_test_program;C:/Users/ktwic/Documents/CC/hw06/CMakeLists.txt;0;")
subdirs(".cs211/lib/catch")
subdirs(".cs211/lib/ge211")
