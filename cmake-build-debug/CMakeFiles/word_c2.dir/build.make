# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.15

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
CMAKE_COMMAND = /snap/clion/107/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /snap/clion/107/bin/cmake/linux/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/student/CLionProjects/word_c2

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/student/CLionProjects/word_c2/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/word_c2.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/word_c2.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/word_c2.dir/flags.make

CMakeFiles/word_c2.dir/main.cpp.o: CMakeFiles/word_c2.dir/flags.make
CMakeFiles/word_c2.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/student/CLionProjects/word_c2/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/word_c2.dir/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/word_c2.dir/main.cpp.o -c /home/student/CLionProjects/word_c2/main.cpp

CMakeFiles/word_c2.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/word_c2.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/student/CLionProjects/word_c2/main.cpp > CMakeFiles/word_c2.dir/main.cpp.i

CMakeFiles/word_c2.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/word_c2.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/student/CLionProjects/word_c2/main.cpp -o CMakeFiles/word_c2.dir/main.cpp.s

# Object files for target word_c2
word_c2_OBJECTS = \
"CMakeFiles/word_c2.dir/main.cpp.o"

# External object files for target word_c2
word_c2_EXTERNAL_OBJECTS =

word_c2: CMakeFiles/word_c2.dir/main.cpp.o
word_c2: CMakeFiles/word_c2.dir/build.make
word_c2: CMakeFiles/word_c2.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/student/CLionProjects/word_c2/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable word_c2"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/word_c2.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/word_c2.dir/build: word_c2

.PHONY : CMakeFiles/word_c2.dir/build

CMakeFiles/word_c2.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/word_c2.dir/cmake_clean.cmake
.PHONY : CMakeFiles/word_c2.dir/clean

CMakeFiles/word_c2.dir/depend:
	cd /home/student/CLionProjects/word_c2/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/student/CLionProjects/word_c2 /home/student/CLionProjects/word_c2 /home/student/CLionProjects/word_c2/cmake-build-debug /home/student/CLionProjects/word_c2/cmake-build-debug /home/student/CLionProjects/word_c2/cmake-build-debug/CMakeFiles/word_c2.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/word_c2.dir/depend

