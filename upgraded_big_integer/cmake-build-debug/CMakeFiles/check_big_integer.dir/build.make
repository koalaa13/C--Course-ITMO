# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.14

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /snap/clion/70/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /snap/clion/70/bin/cmake/linux/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/koalaa13/CLionProjects/big_integer

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/koalaa13/CLionProjects/big_integer/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/check_big_integer.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/check_big_integer.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/check_big_integer.dir/flags.make

CMakeFiles/check_big_integer.dir/main.cpp.o: CMakeFiles/check_big_integer.dir/flags.make
CMakeFiles/check_big_integer.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/koalaa13/CLionProjects/big_integer/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/check_big_integer.dir/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/check_big_integer.dir/main.cpp.o -c /home/koalaa13/CLionProjects/big_integer/main.cpp

CMakeFiles/check_big_integer.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/check_big_integer.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/koalaa13/CLionProjects/big_integer/main.cpp > CMakeFiles/check_big_integer.dir/main.cpp.i

CMakeFiles/check_big_integer.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/check_big_integer.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/koalaa13/CLionProjects/big_integer/main.cpp -o CMakeFiles/check_big_integer.dir/main.cpp.s

CMakeFiles/check_big_integer.dir/my_vector.cpp.o: CMakeFiles/check_big_integer.dir/flags.make
CMakeFiles/check_big_integer.dir/my_vector.cpp.o: ../my_vector.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/koalaa13/CLionProjects/big_integer/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/check_big_integer.dir/my_vector.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/check_big_integer.dir/my_vector.cpp.o -c /home/koalaa13/CLionProjects/big_integer/my_vector.cpp

CMakeFiles/check_big_integer.dir/my_vector.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/check_big_integer.dir/my_vector.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/koalaa13/CLionProjects/big_integer/my_vector.cpp > CMakeFiles/check_big_integer.dir/my_vector.cpp.i

CMakeFiles/check_big_integer.dir/my_vector.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/check_big_integer.dir/my_vector.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/koalaa13/CLionProjects/big_integer/my_vector.cpp -o CMakeFiles/check_big_integer.dir/my_vector.cpp.s

CMakeFiles/check_big_integer.dir/big_integer.cpp.o: CMakeFiles/check_big_integer.dir/flags.make
CMakeFiles/check_big_integer.dir/big_integer.cpp.o: ../big_integer.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/koalaa13/CLionProjects/big_integer/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/check_big_integer.dir/big_integer.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/check_big_integer.dir/big_integer.cpp.o -c /home/koalaa13/CLionProjects/big_integer/big_integer.cpp

CMakeFiles/check_big_integer.dir/big_integer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/check_big_integer.dir/big_integer.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/koalaa13/CLionProjects/big_integer/big_integer.cpp > CMakeFiles/check_big_integer.dir/big_integer.cpp.i

CMakeFiles/check_big_integer.dir/big_integer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/check_big_integer.dir/big_integer.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/koalaa13/CLionProjects/big_integer/big_integer.cpp -o CMakeFiles/check_big_integer.dir/big_integer.cpp.s

# Object files for target check_big_integer
check_big_integer_OBJECTS = \
"CMakeFiles/check_big_integer.dir/main.cpp.o" \
"CMakeFiles/check_big_integer.dir/my_vector.cpp.o" \
"CMakeFiles/check_big_integer.dir/big_integer.cpp.o"

# External object files for target check_big_integer
check_big_integer_EXTERNAL_OBJECTS =

check_big_integer: CMakeFiles/check_big_integer.dir/main.cpp.o
check_big_integer: CMakeFiles/check_big_integer.dir/my_vector.cpp.o
check_big_integer: CMakeFiles/check_big_integer.dir/big_integer.cpp.o
check_big_integer: CMakeFiles/check_big_integer.dir/build.make
check_big_integer: CMakeFiles/check_big_integer.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/koalaa13/CLionProjects/big_integer/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX executable check_big_integer"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/check_big_integer.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/check_big_integer.dir/build: check_big_integer

.PHONY : CMakeFiles/check_big_integer.dir/build

CMakeFiles/check_big_integer.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/check_big_integer.dir/cmake_clean.cmake
.PHONY : CMakeFiles/check_big_integer.dir/clean

CMakeFiles/check_big_integer.dir/depend:
	cd /home/koalaa13/CLionProjects/big_integer/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/koalaa13/CLionProjects/big_integer /home/koalaa13/CLionProjects/big_integer /home/koalaa13/CLionProjects/big_integer/cmake-build-debug /home/koalaa13/CLionProjects/big_integer/cmake-build-debug /home/koalaa13/CLionProjects/big_integer/cmake-build-debug/CMakeFiles/check_big_integer.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/check_big_integer.dir/depend

