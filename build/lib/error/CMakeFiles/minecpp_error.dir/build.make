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
include lib/error/CMakeFiles/minecpp_error.dir/depend.make

# Include the progress variables for this target.
include lib/error/CMakeFiles/minecpp_error.dir/progress.make

# Include the compile flags for this target's objects.
include lib/error/CMakeFiles/minecpp_error.dir/flags.make

lib/error/CMakeFiles/minecpp_error.dir/error.cpp.o: lib/error/CMakeFiles/minecpp_error.dir/flags.make
lib/error/CMakeFiles/minecpp_error.dir/error.cpp.o: ../lib/error/error.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ego/projects/minecpp/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object lib/error/CMakeFiles/minecpp_error.dir/error.cpp.o"
	cd /home/ego/projects/minecpp/build/lib/error && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/minecpp_error.dir/error.cpp.o -c /home/ego/projects/minecpp/lib/error/error.cpp

lib/error/CMakeFiles/minecpp_error.dir/error.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/minecpp_error.dir/error.cpp.i"
	cd /home/ego/projects/minecpp/build/lib/error && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ego/projects/minecpp/lib/error/error.cpp > CMakeFiles/minecpp_error.dir/error.cpp.i

lib/error/CMakeFiles/minecpp_error.dir/error.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/minecpp_error.dir/error.cpp.s"
	cd /home/ego/projects/minecpp/build/lib/error && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ego/projects/minecpp/lib/error/error.cpp -o CMakeFiles/minecpp_error.dir/error.cpp.s

# Object files for target minecpp_error
minecpp_error_OBJECTS = \
"CMakeFiles/minecpp_error.dir/error.cpp.o"

# External object files for target minecpp_error
minecpp_error_EXTERNAL_OBJECTS =

lib/error/libminecpp_error.a: lib/error/CMakeFiles/minecpp_error.dir/error.cpp.o
lib/error/libminecpp_error.a: lib/error/CMakeFiles/minecpp_error.dir/build.make
lib/error/libminecpp_error.a: lib/error/CMakeFiles/minecpp_error.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/ego/projects/minecpp/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libminecpp_error.a"
	cd /home/ego/projects/minecpp/build/lib/error && $(CMAKE_COMMAND) -P CMakeFiles/minecpp_error.dir/cmake_clean_target.cmake
	cd /home/ego/projects/minecpp/build/lib/error && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/minecpp_error.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
lib/error/CMakeFiles/minecpp_error.dir/build: lib/error/libminecpp_error.a

.PHONY : lib/error/CMakeFiles/minecpp_error.dir/build

lib/error/CMakeFiles/minecpp_error.dir/clean:
	cd /home/ego/projects/minecpp/build/lib/error && $(CMAKE_COMMAND) -P CMakeFiles/minecpp_error.dir/cmake_clean.cmake
.PHONY : lib/error/CMakeFiles/minecpp_error.dir/clean

lib/error/CMakeFiles/minecpp_error.dir/depend:
	cd /home/ego/projects/minecpp/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ego/projects/minecpp /home/ego/projects/minecpp/lib/error /home/ego/projects/minecpp/build /home/ego/projects/minecpp/build/lib/error /home/ego/projects/minecpp/build/lib/error/CMakeFiles/minecpp_error.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : lib/error/CMakeFiles/minecpp_error.dir/depend

