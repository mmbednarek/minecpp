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

# Utility rule file for plugins.

# Include the progress variables for this target.
include _deps/grpc-build/CMakeFiles/plugins.dir/progress.make

_deps/grpc-build/CMakeFiles/plugins: _deps/grpc-build/grpc_cpp_plugin
_deps/grpc-build/CMakeFiles/plugins: _deps/grpc-build/grpc_csharp_plugin
_deps/grpc-build/CMakeFiles/plugins: _deps/grpc-build/grpc_node_plugin
_deps/grpc-build/CMakeFiles/plugins: _deps/grpc-build/grpc_objective_c_plugin
_deps/grpc-build/CMakeFiles/plugins: _deps/grpc-build/grpc_php_plugin
_deps/grpc-build/CMakeFiles/plugins: _deps/grpc-build/grpc_python_plugin
_deps/grpc-build/CMakeFiles/plugins: _deps/grpc-build/grpc_ruby_plugin


plugins: _deps/grpc-build/CMakeFiles/plugins
plugins: _deps/grpc-build/CMakeFiles/plugins.dir/build.make

.PHONY : plugins

# Rule to build all files generated by this target.
_deps/grpc-build/CMakeFiles/plugins.dir/build: plugins

.PHONY : _deps/grpc-build/CMakeFiles/plugins.dir/build

_deps/grpc-build/CMakeFiles/plugins.dir/clean:
	cd /home/ego/projects/minecpp/build/_deps/grpc-build && $(CMAKE_COMMAND) -P CMakeFiles/plugins.dir/cmake_clean.cmake
.PHONY : _deps/grpc-build/CMakeFiles/plugins.dir/clean

_deps/grpc-build/CMakeFiles/plugins.dir/depend:
	cd /home/ego/projects/minecpp/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ego/projects/minecpp /home/ego/projects/minecpp/build/_deps/grpc-src /home/ego/projects/minecpp/build /home/ego/projects/minecpp/build/_deps/grpc-build /home/ego/projects/minecpp/build/_deps/grpc-build/CMakeFiles/plugins.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : _deps/grpc-build/CMakeFiles/plugins.dir/depend
