# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.19

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Disable VCS-based implicit rules.
% : %,v


# Disable VCS-based implicit rules.
% : RCS/%


# Disable VCS-based implicit rules.
% : RCS/%,v


# Disable VCS-based implicit rules.
% : SCCS/s.%


# Disable VCS-based implicit rules.
% : s.%


.SUFFIXES: .hpux_make_needs_suffix_list


# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/ego/projects/minecpp

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/ego/projects/minecpp/build

# Include any dependencies generated for this target.
include lib/squeeze/CMakeFiles/minecpp_squeeze.dir/depend.make

# Include the progress variables for this target.
include lib/squeeze/CMakeFiles/minecpp_squeeze.dir/progress.make

# Include the compile flags for this target's objects.
include lib/squeeze/CMakeFiles/minecpp_squeeze.dir/flags.make

lib/squeeze/CMakeFiles/minecpp_squeeze.dir/vector.cpp.o: lib/squeeze/CMakeFiles/minecpp_squeeze.dir/flags.make
lib/squeeze/CMakeFiles/minecpp_squeeze.dir/vector.cpp.o: ../lib/squeeze/vector.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ego/projects/minecpp/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object lib/squeeze/CMakeFiles/minecpp_squeeze.dir/vector.cpp.o"
	cd /home/ego/projects/minecpp/build/lib/squeeze && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/minecpp_squeeze.dir/vector.cpp.o -c /home/ego/projects/minecpp/lib/squeeze/vector.cpp

lib/squeeze/CMakeFiles/minecpp_squeeze.dir/vector.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/minecpp_squeeze.dir/vector.cpp.i"
	cd /home/ego/projects/minecpp/build/lib/squeeze && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ego/projects/minecpp/lib/squeeze/vector.cpp > CMakeFiles/minecpp_squeeze.dir/vector.cpp.i

lib/squeeze/CMakeFiles/minecpp_squeeze.dir/vector.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/minecpp_squeeze.dir/vector.cpp.s"
	cd /home/ego/projects/minecpp/build/lib/squeeze && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ego/projects/minecpp/lib/squeeze/vector.cpp -o CMakeFiles/minecpp_squeeze.dir/vector.cpp.s

# Object files for target minecpp_squeeze
minecpp_squeeze_OBJECTS = \
"CMakeFiles/minecpp_squeeze.dir/vector.cpp.o"

# External object files for target minecpp_squeeze
minecpp_squeeze_EXTERNAL_OBJECTS =

lib/squeeze/libminecpp_squeeze.a: lib/squeeze/CMakeFiles/minecpp_squeeze.dir/vector.cpp.o
lib/squeeze/libminecpp_squeeze.a: lib/squeeze/CMakeFiles/minecpp_squeeze.dir/build.make
lib/squeeze/libminecpp_squeeze.a: lib/squeeze/CMakeFiles/minecpp_squeeze.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/ego/projects/minecpp/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libminecpp_squeeze.a"
	cd /home/ego/projects/minecpp/build/lib/squeeze && $(CMAKE_COMMAND) -P CMakeFiles/minecpp_squeeze.dir/cmake_clean_target.cmake
	cd /home/ego/projects/minecpp/build/lib/squeeze && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/minecpp_squeeze.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
lib/squeeze/CMakeFiles/minecpp_squeeze.dir/build: lib/squeeze/libminecpp_squeeze.a

.PHONY : lib/squeeze/CMakeFiles/minecpp_squeeze.dir/build

lib/squeeze/CMakeFiles/minecpp_squeeze.dir/clean:
	cd /home/ego/projects/minecpp/build/lib/squeeze && $(CMAKE_COMMAND) -P CMakeFiles/minecpp_squeeze.dir/cmake_clean.cmake
.PHONY : lib/squeeze/CMakeFiles/minecpp_squeeze.dir/clean

lib/squeeze/CMakeFiles/minecpp_squeeze.dir/depend:
	cd /home/ego/projects/minecpp/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ego/projects/minecpp /home/ego/projects/minecpp/lib/squeeze /home/ego/projects/minecpp/build /home/ego/projects/minecpp/build/lib/squeeze /home/ego/projects/minecpp/build/lib/squeeze/CMakeFiles/minecpp_squeeze.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : lib/squeeze/CMakeFiles/minecpp_squeeze.dir/depend
