# CMake generated Testfile for 
# Source directory: /home/mactavish/hdd/mactavish/verinet
# Build directory: /home/mactavish/hdd/mactavish/verinet
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(test1, "verinet_test")
subdirs(src)
subdirs(gtest-1.7.0)
