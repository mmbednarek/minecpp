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
include _deps/grpc-build/third_party/re2/CMakeFiles/compile_test.dir/depend.make

# Include the progress variables for this target.
include _deps/grpc-build/third_party/re2/CMakeFiles/compile_test.dir/progress.make

# Include the compile flags for this target's objects.
include _deps/grpc-build/third_party/re2/CMakeFiles/compile_test.dir/flags.make

_deps/grpc-build/third_party/re2/CMakeFiles/compile_test.dir/re2/testing/compile_test.cc.o: _deps/grpc-build/third_party/re2/CMakeFiles/compile_test.dir/flags.make
_deps/grpc-build/third_party/re2/CMakeFiles/compile_test.dir/re2/testing/compile_test.cc.o: _deps/grpc-src/third_party/re2/re2/testing/compile_test.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ego/projects/minecpp/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object _deps/grpc-build/third_party/re2/CMakeFiles/compile_test.dir/re2/testing/compile_test.cc.o"
	cd /home/ego/projects/minecpp/build/_deps/grpc-build/third_party/re2 && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/compile_test.dir/re2/testing/compile_test.cc.o -c /home/ego/projects/minecpp/build/_deps/grpc-src/third_party/re2/re2/testing/compile_test.cc

_deps/grpc-build/third_party/re2/CMakeFiles/compile_test.dir/re2/testing/compile_test.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/compile_test.dir/re2/testing/compile_test.cc.i"
	cd /home/ego/projects/minecpp/build/_deps/grpc-build/third_party/re2 && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ego/projects/minecpp/build/_deps/grpc-src/third_party/re2/re2/testing/compile_test.cc > CMakeFiles/compile_test.dir/re2/testing/compile_test.cc.i

_deps/grpc-build/third_party/re2/CMakeFiles/compile_test.dir/re2/testing/compile_test.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/compile_test.dir/re2/testing/compile_test.cc.s"
	cd /home/ego/projects/minecpp/build/_deps/grpc-build/third_party/re2 && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ego/projects/minecpp/build/_deps/grpc-src/third_party/re2/re2/testing/compile_test.cc -o CMakeFiles/compile_test.dir/re2/testing/compile_test.cc.s

_deps/grpc-build/third_party/re2/CMakeFiles/compile_test.dir/util/test.cc.o: _deps/grpc-build/third_party/re2/CMakeFiles/compile_test.dir/flags.make
_deps/grpc-build/third_party/re2/CMakeFiles/compile_test.dir/util/test.cc.o: _deps/grpc-src/third_party/re2/util/test.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ego/projects/minecpp/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object _deps/grpc-build/third_party/re2/CMakeFiles/compile_test.dir/util/test.cc.o"
	cd /home/ego/projects/minecpp/build/_deps/grpc-build/third_party/re2 && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/compile_test.dir/util/test.cc.o -c /home/ego/projects/minecpp/build/_deps/grpc-src/third_party/re2/util/test.cc

_deps/grpc-build/third_party/re2/CMakeFiles/compile_test.dir/util/test.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/compile_test.dir/util/test.cc.i"
	cd /home/ego/projects/minecpp/build/_deps/grpc-build/third_party/re2 && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ego/projects/minecpp/build/_deps/grpc-src/third_party/re2/util/test.cc > CMakeFiles/compile_test.dir/util/test.cc.i

_deps/grpc-build/third_party/re2/CMakeFiles/compile_test.dir/util/test.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/compile_test.dir/util/test.cc.s"
	cd /home/ego/projects/minecpp/build/_deps/grpc-build/third_party/re2 && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ego/projects/minecpp/build/_deps/grpc-src/third_party/re2/util/test.cc -o CMakeFiles/compile_test.dir/util/test.cc.s

# Object files for target compile_test
compile_test_OBJECTS = \
"CMakeFiles/compile_test.dir/re2/testing/compile_test.cc.o" \
"CMakeFiles/compile_test.dir/util/test.cc.o"

# External object files for target compile_test
compile_test_EXTERNAL_OBJECTS =

_deps/grpc-build/third_party/re2/compile_test: _deps/grpc-build/third_party/re2/CMakeFiles/compile_test.dir/re2/testing/compile_test.cc.o
_deps/grpc-build/third_party/re2/compile_test: _deps/grpc-build/third_party/re2/CMakeFiles/compile_test.dir/util/test.cc.o
_deps/grpc-build/third_party/re2/compile_test: _deps/grpc-build/third_party/re2/CMakeFiles/compile_test.dir/build.make
_deps/grpc-build/third_party/re2/compile_test: _deps/grpc-build/third_party/re2/libtesting.a
_deps/grpc-build/third_party/re2/compile_test: _deps/grpc-build/third_party/re2/libre2.a
_deps/grpc-build/third_party/re2/compile_test: _deps/grpc-build/third_party/re2/CMakeFiles/compile_test.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/ego/projects/minecpp/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable compile_test"
	cd /home/ego/projects/minecpp/build/_deps/grpc-build/third_party/re2 && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/compile_test.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
_deps/grpc-build/third_party/re2/CMakeFiles/compile_test.dir/build: _deps/grpc-build/third_party/re2/compile_test

.PHONY : _deps/grpc-build/third_party/re2/CMakeFiles/compile_test.dir/build

_deps/grpc-build/third_party/re2/CMakeFiles/compile_test.dir/clean:
	cd /home/ego/projects/minecpp/build/_deps/grpc-build/third_party/re2 && $(CMAKE_COMMAND) -P CMakeFiles/compile_test.dir/cmake_clean.cmake
.PHONY : _deps/grpc-build/third_party/re2/CMakeFiles/compile_test.dir/clean

_deps/grpc-build/third_party/re2/CMakeFiles/compile_test.dir/depend:
	cd /home/ego/projects/minecpp/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ego/projects/minecpp /home/ego/projects/minecpp/build/_deps/grpc-src/third_party/re2 /home/ego/projects/minecpp/build /home/ego/projects/minecpp/build/_deps/grpc-build/third_party/re2 /home/ego/projects/minecpp/build/_deps/grpc-build/third_party/re2/CMakeFiles/compile_test.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : _deps/grpc-build/third_party/re2/CMakeFiles/compile_test.dir/depend

