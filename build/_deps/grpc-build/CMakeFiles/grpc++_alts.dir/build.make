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
include _deps/grpc-build/CMakeFiles/grpc++_alts.dir/depend.make

# Include the progress variables for this target.
include _deps/grpc-build/CMakeFiles/grpc++_alts.dir/progress.make

# Include the compile flags for this target's objects.
include _deps/grpc-build/CMakeFiles/grpc++_alts.dir/flags.make

_deps/grpc-build/CMakeFiles/grpc++_alts.dir/src/cpp/common/alts_context.cc.o: _deps/grpc-build/CMakeFiles/grpc++_alts.dir/flags.make
_deps/grpc-build/CMakeFiles/grpc++_alts.dir/src/cpp/common/alts_context.cc.o: _deps/grpc-src/src/cpp/common/alts_context.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ego/projects/minecpp/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object _deps/grpc-build/CMakeFiles/grpc++_alts.dir/src/cpp/common/alts_context.cc.o"
	cd /home/ego/projects/minecpp/build/_deps/grpc-build && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/grpc++_alts.dir/src/cpp/common/alts_context.cc.o -c /home/ego/projects/minecpp/build/_deps/grpc-src/src/cpp/common/alts_context.cc

_deps/grpc-build/CMakeFiles/grpc++_alts.dir/src/cpp/common/alts_context.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/grpc++_alts.dir/src/cpp/common/alts_context.cc.i"
	cd /home/ego/projects/minecpp/build/_deps/grpc-build && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ego/projects/minecpp/build/_deps/grpc-src/src/cpp/common/alts_context.cc > CMakeFiles/grpc++_alts.dir/src/cpp/common/alts_context.cc.i

_deps/grpc-build/CMakeFiles/grpc++_alts.dir/src/cpp/common/alts_context.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/grpc++_alts.dir/src/cpp/common/alts_context.cc.s"
	cd /home/ego/projects/minecpp/build/_deps/grpc-build && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ego/projects/minecpp/build/_deps/grpc-src/src/cpp/common/alts_context.cc -o CMakeFiles/grpc++_alts.dir/src/cpp/common/alts_context.cc.s

_deps/grpc-build/CMakeFiles/grpc++_alts.dir/src/cpp/common/alts_util.cc.o: _deps/grpc-build/CMakeFiles/grpc++_alts.dir/flags.make
_deps/grpc-build/CMakeFiles/grpc++_alts.dir/src/cpp/common/alts_util.cc.o: _deps/grpc-src/src/cpp/common/alts_util.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ego/projects/minecpp/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object _deps/grpc-build/CMakeFiles/grpc++_alts.dir/src/cpp/common/alts_util.cc.o"
	cd /home/ego/projects/minecpp/build/_deps/grpc-build && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/grpc++_alts.dir/src/cpp/common/alts_util.cc.o -c /home/ego/projects/minecpp/build/_deps/grpc-src/src/cpp/common/alts_util.cc

_deps/grpc-build/CMakeFiles/grpc++_alts.dir/src/cpp/common/alts_util.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/grpc++_alts.dir/src/cpp/common/alts_util.cc.i"
	cd /home/ego/projects/minecpp/build/_deps/grpc-build && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ego/projects/minecpp/build/_deps/grpc-src/src/cpp/common/alts_util.cc > CMakeFiles/grpc++_alts.dir/src/cpp/common/alts_util.cc.i

_deps/grpc-build/CMakeFiles/grpc++_alts.dir/src/cpp/common/alts_util.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/grpc++_alts.dir/src/cpp/common/alts_util.cc.s"
	cd /home/ego/projects/minecpp/build/_deps/grpc-build && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ego/projects/minecpp/build/_deps/grpc-src/src/cpp/common/alts_util.cc -o CMakeFiles/grpc++_alts.dir/src/cpp/common/alts_util.cc.s

# Object files for target grpc++_alts
grpc_______alts_OBJECTS = \
"CMakeFiles/grpc++_alts.dir/src/cpp/common/alts_context.cc.o" \
"CMakeFiles/grpc++_alts.dir/src/cpp/common/alts_util.cc.o"

# External object files for target grpc++_alts
grpc_______alts_EXTERNAL_OBJECTS =

_deps/grpc-build/libgrpc++_alts.a: _deps/grpc-build/CMakeFiles/grpc++_alts.dir/src/cpp/common/alts_context.cc.o
_deps/grpc-build/libgrpc++_alts.a: _deps/grpc-build/CMakeFiles/grpc++_alts.dir/src/cpp/common/alts_util.cc.o
_deps/grpc-build/libgrpc++_alts.a: _deps/grpc-build/CMakeFiles/grpc++_alts.dir/build.make
_deps/grpc-build/libgrpc++_alts.a: _deps/grpc-build/CMakeFiles/grpc++_alts.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/ego/projects/minecpp/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX static library libgrpc++_alts.a"
	cd /home/ego/projects/minecpp/build/_deps/grpc-build && $(CMAKE_COMMAND) -P CMakeFiles/grpc++_alts.dir/cmake_clean_target.cmake
	cd /home/ego/projects/minecpp/build/_deps/grpc-build && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/grpc++_alts.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
_deps/grpc-build/CMakeFiles/grpc++_alts.dir/build: _deps/grpc-build/libgrpc++_alts.a

.PHONY : _deps/grpc-build/CMakeFiles/grpc++_alts.dir/build

_deps/grpc-build/CMakeFiles/grpc++_alts.dir/clean:
	cd /home/ego/projects/minecpp/build/_deps/grpc-build && $(CMAKE_COMMAND) -P CMakeFiles/grpc++_alts.dir/cmake_clean.cmake
.PHONY : _deps/grpc-build/CMakeFiles/grpc++_alts.dir/clean

_deps/grpc-build/CMakeFiles/grpc++_alts.dir/depend:
	cd /home/ego/projects/minecpp/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ego/projects/minecpp /home/ego/projects/minecpp/build/_deps/grpc-src /home/ego/projects/minecpp/build /home/ego/projects/minecpp/build/_deps/grpc-build /home/ego/projects/minecpp/build/_deps/grpc-build/CMakeFiles/grpc++_alts.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : _deps/grpc-build/CMakeFiles/grpc++_alts.dir/depend
