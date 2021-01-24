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
include _deps/grpc-build/CMakeFiles/grpcpp_channelz.dir/depend.make

# Include the progress variables for this target.
include _deps/grpc-build/CMakeFiles/grpcpp_channelz.dir/progress.make

# Include the compile flags for this target's objects.
include _deps/grpc-build/CMakeFiles/grpcpp_channelz.dir/flags.make

gens/src/proto/grpc/channelz/channelz.grpc.pb.cc: _deps/grpc-src/src/proto/grpc/channelz/channelz.proto
gens/src/proto/grpc/channelz/channelz.grpc.pb.cc: _deps/grpc-build/third_party/protobuf/protoc-3.14.0.0
gens/src/proto/grpc/channelz/channelz.grpc.pb.cc: _deps/grpc-build/grpc_cpp_plugin
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/ego/projects/minecpp/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Running gRPC C++ protocol buffer compiler on src/proto/grpc/channelz/channelz.proto"
	cd /home/ego/projects/minecpp/build/_deps/grpc-src && /home/ego/projects/minecpp/build/_deps/grpc-build/third_party/protobuf/protoc-3.14.0.0 --grpc_out=generate_mock_code=true:/home/ego/projects/minecpp/build/gens --cpp_out=/home/ego/projects/minecpp/build/gens --plugin=protoc-gen-grpc=/home/ego/projects/minecpp/build/_deps/grpc-build/grpc_cpp_plugin -I . -I /home/ego/projects/minecpp/build/_deps/grpc-src/third_party/protobuf/src src/proto/grpc/channelz/channelz.proto

gens/src/proto/grpc/channelz/channelz.grpc.pb.h: gens/src/proto/grpc/channelz/channelz.grpc.pb.cc
	@$(CMAKE_COMMAND) -E touch_nocreate gens/src/proto/grpc/channelz/channelz.grpc.pb.h

gens/src/proto/grpc/channelz/channelz_mock.grpc.pb.h: gens/src/proto/grpc/channelz/channelz.grpc.pb.cc
	@$(CMAKE_COMMAND) -E touch_nocreate gens/src/proto/grpc/channelz/channelz_mock.grpc.pb.h

gens/src/proto/grpc/channelz/channelz.pb.cc: gens/src/proto/grpc/channelz/channelz.grpc.pb.cc
	@$(CMAKE_COMMAND) -E touch_nocreate gens/src/proto/grpc/channelz/channelz.pb.cc

gens/src/proto/grpc/channelz/channelz.pb.h: gens/src/proto/grpc/channelz/channelz.grpc.pb.cc
	@$(CMAKE_COMMAND) -E touch_nocreate gens/src/proto/grpc/channelz/channelz.pb.h

_deps/grpc-build/CMakeFiles/grpcpp_channelz.dir/__/__/gens/src/proto/grpc/channelz/channelz.pb.cc.o: _deps/grpc-build/CMakeFiles/grpcpp_channelz.dir/flags.make
_deps/grpc-build/CMakeFiles/grpcpp_channelz.dir/__/__/gens/src/proto/grpc/channelz/channelz.pb.cc.o: gens/src/proto/grpc/channelz/channelz.pb.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ego/projects/minecpp/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object _deps/grpc-build/CMakeFiles/grpcpp_channelz.dir/__/__/gens/src/proto/grpc/channelz/channelz.pb.cc.o"
	cd /home/ego/projects/minecpp/build/_deps/grpc-build && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/grpcpp_channelz.dir/__/__/gens/src/proto/grpc/channelz/channelz.pb.cc.o -c /home/ego/projects/minecpp/build/gens/src/proto/grpc/channelz/channelz.pb.cc

_deps/grpc-build/CMakeFiles/grpcpp_channelz.dir/__/__/gens/src/proto/grpc/channelz/channelz.pb.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/grpcpp_channelz.dir/__/__/gens/src/proto/grpc/channelz/channelz.pb.cc.i"
	cd /home/ego/projects/minecpp/build/_deps/grpc-build && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ego/projects/minecpp/build/gens/src/proto/grpc/channelz/channelz.pb.cc > CMakeFiles/grpcpp_channelz.dir/__/__/gens/src/proto/grpc/channelz/channelz.pb.cc.i

_deps/grpc-build/CMakeFiles/grpcpp_channelz.dir/__/__/gens/src/proto/grpc/channelz/channelz.pb.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/grpcpp_channelz.dir/__/__/gens/src/proto/grpc/channelz/channelz.pb.cc.s"
	cd /home/ego/projects/minecpp/build/_deps/grpc-build && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ego/projects/minecpp/build/gens/src/proto/grpc/channelz/channelz.pb.cc -o CMakeFiles/grpcpp_channelz.dir/__/__/gens/src/proto/grpc/channelz/channelz.pb.cc.s

_deps/grpc-build/CMakeFiles/grpcpp_channelz.dir/__/__/gens/src/proto/grpc/channelz/channelz.grpc.pb.cc.o: _deps/grpc-build/CMakeFiles/grpcpp_channelz.dir/flags.make
_deps/grpc-build/CMakeFiles/grpcpp_channelz.dir/__/__/gens/src/proto/grpc/channelz/channelz.grpc.pb.cc.o: gens/src/proto/grpc/channelz/channelz.grpc.pb.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ego/projects/minecpp/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object _deps/grpc-build/CMakeFiles/grpcpp_channelz.dir/__/__/gens/src/proto/grpc/channelz/channelz.grpc.pb.cc.o"
	cd /home/ego/projects/minecpp/build/_deps/grpc-build && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/grpcpp_channelz.dir/__/__/gens/src/proto/grpc/channelz/channelz.grpc.pb.cc.o -c /home/ego/projects/minecpp/build/gens/src/proto/grpc/channelz/channelz.grpc.pb.cc

_deps/grpc-build/CMakeFiles/grpcpp_channelz.dir/__/__/gens/src/proto/grpc/channelz/channelz.grpc.pb.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/grpcpp_channelz.dir/__/__/gens/src/proto/grpc/channelz/channelz.grpc.pb.cc.i"
	cd /home/ego/projects/minecpp/build/_deps/grpc-build && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ego/projects/minecpp/build/gens/src/proto/grpc/channelz/channelz.grpc.pb.cc > CMakeFiles/grpcpp_channelz.dir/__/__/gens/src/proto/grpc/channelz/channelz.grpc.pb.cc.i

_deps/grpc-build/CMakeFiles/grpcpp_channelz.dir/__/__/gens/src/proto/grpc/channelz/channelz.grpc.pb.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/grpcpp_channelz.dir/__/__/gens/src/proto/grpc/channelz/channelz.grpc.pb.cc.s"
	cd /home/ego/projects/minecpp/build/_deps/grpc-build && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ego/projects/minecpp/build/gens/src/proto/grpc/channelz/channelz.grpc.pb.cc -o CMakeFiles/grpcpp_channelz.dir/__/__/gens/src/proto/grpc/channelz/channelz.grpc.pb.cc.s

_deps/grpc-build/CMakeFiles/grpcpp_channelz.dir/src/cpp/server/channelz/channelz_service.cc.o: _deps/grpc-build/CMakeFiles/grpcpp_channelz.dir/flags.make
_deps/grpc-build/CMakeFiles/grpcpp_channelz.dir/src/cpp/server/channelz/channelz_service.cc.o: _deps/grpc-src/src/cpp/server/channelz/channelz_service.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ego/projects/minecpp/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object _deps/grpc-build/CMakeFiles/grpcpp_channelz.dir/src/cpp/server/channelz/channelz_service.cc.o"
	cd /home/ego/projects/minecpp/build/_deps/grpc-build && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/grpcpp_channelz.dir/src/cpp/server/channelz/channelz_service.cc.o -c /home/ego/projects/minecpp/build/_deps/grpc-src/src/cpp/server/channelz/channelz_service.cc

_deps/grpc-build/CMakeFiles/grpcpp_channelz.dir/src/cpp/server/channelz/channelz_service.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/grpcpp_channelz.dir/src/cpp/server/channelz/channelz_service.cc.i"
	cd /home/ego/projects/minecpp/build/_deps/grpc-build && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ego/projects/minecpp/build/_deps/grpc-src/src/cpp/server/channelz/channelz_service.cc > CMakeFiles/grpcpp_channelz.dir/src/cpp/server/channelz/channelz_service.cc.i

_deps/grpc-build/CMakeFiles/grpcpp_channelz.dir/src/cpp/server/channelz/channelz_service.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/grpcpp_channelz.dir/src/cpp/server/channelz/channelz_service.cc.s"
	cd /home/ego/projects/minecpp/build/_deps/grpc-build && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ego/projects/minecpp/build/_deps/grpc-src/src/cpp/server/channelz/channelz_service.cc -o CMakeFiles/grpcpp_channelz.dir/src/cpp/server/channelz/channelz_service.cc.s

_deps/grpc-build/CMakeFiles/grpcpp_channelz.dir/src/cpp/server/channelz/channelz_service_plugin.cc.o: _deps/grpc-build/CMakeFiles/grpcpp_channelz.dir/flags.make
_deps/grpc-build/CMakeFiles/grpcpp_channelz.dir/src/cpp/server/channelz/channelz_service_plugin.cc.o: _deps/grpc-src/src/cpp/server/channelz/channelz_service_plugin.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ego/projects/minecpp/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object _deps/grpc-build/CMakeFiles/grpcpp_channelz.dir/src/cpp/server/channelz/channelz_service_plugin.cc.o"
	cd /home/ego/projects/minecpp/build/_deps/grpc-build && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/grpcpp_channelz.dir/src/cpp/server/channelz/channelz_service_plugin.cc.o -c /home/ego/projects/minecpp/build/_deps/grpc-src/src/cpp/server/channelz/channelz_service_plugin.cc

_deps/grpc-build/CMakeFiles/grpcpp_channelz.dir/src/cpp/server/channelz/channelz_service_plugin.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/grpcpp_channelz.dir/src/cpp/server/channelz/channelz_service_plugin.cc.i"
	cd /home/ego/projects/minecpp/build/_deps/grpc-build && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ego/projects/minecpp/build/_deps/grpc-src/src/cpp/server/channelz/channelz_service_plugin.cc > CMakeFiles/grpcpp_channelz.dir/src/cpp/server/channelz/channelz_service_plugin.cc.i

_deps/grpc-build/CMakeFiles/grpcpp_channelz.dir/src/cpp/server/channelz/channelz_service_plugin.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/grpcpp_channelz.dir/src/cpp/server/channelz/channelz_service_plugin.cc.s"
	cd /home/ego/projects/minecpp/build/_deps/grpc-build && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ego/projects/minecpp/build/_deps/grpc-src/src/cpp/server/channelz/channelz_service_plugin.cc -o CMakeFiles/grpcpp_channelz.dir/src/cpp/server/channelz/channelz_service_plugin.cc.s

# Object files for target grpcpp_channelz
grpcpp_channelz_OBJECTS = \
"CMakeFiles/grpcpp_channelz.dir/__/__/gens/src/proto/grpc/channelz/channelz.pb.cc.o" \
"CMakeFiles/grpcpp_channelz.dir/__/__/gens/src/proto/grpc/channelz/channelz.grpc.pb.cc.o" \
"CMakeFiles/grpcpp_channelz.dir/src/cpp/server/channelz/channelz_service.cc.o" \
"CMakeFiles/grpcpp_channelz.dir/src/cpp/server/channelz/channelz_service_plugin.cc.o"

# External object files for target grpcpp_channelz
grpcpp_channelz_EXTERNAL_OBJECTS =

_deps/grpc-build/libgrpcpp_channelz.a: _deps/grpc-build/CMakeFiles/grpcpp_channelz.dir/__/__/gens/src/proto/grpc/channelz/channelz.pb.cc.o
_deps/grpc-build/libgrpcpp_channelz.a: _deps/grpc-build/CMakeFiles/grpcpp_channelz.dir/__/__/gens/src/proto/grpc/channelz/channelz.grpc.pb.cc.o
_deps/grpc-build/libgrpcpp_channelz.a: _deps/grpc-build/CMakeFiles/grpcpp_channelz.dir/src/cpp/server/channelz/channelz_service.cc.o
_deps/grpc-build/libgrpcpp_channelz.a: _deps/grpc-build/CMakeFiles/grpcpp_channelz.dir/src/cpp/server/channelz/channelz_service_plugin.cc.o
_deps/grpc-build/libgrpcpp_channelz.a: _deps/grpc-build/CMakeFiles/grpcpp_channelz.dir/build.make
_deps/grpc-build/libgrpcpp_channelz.a: _deps/grpc-build/CMakeFiles/grpcpp_channelz.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/ego/projects/minecpp/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Linking CXX static library libgrpcpp_channelz.a"
	cd /home/ego/projects/minecpp/build/_deps/grpc-build && $(CMAKE_COMMAND) -P CMakeFiles/grpcpp_channelz.dir/cmake_clean_target.cmake
	cd /home/ego/projects/minecpp/build/_deps/grpc-build && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/grpcpp_channelz.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
_deps/grpc-build/CMakeFiles/grpcpp_channelz.dir/build: _deps/grpc-build/libgrpcpp_channelz.a

.PHONY : _deps/grpc-build/CMakeFiles/grpcpp_channelz.dir/build

_deps/grpc-build/CMakeFiles/grpcpp_channelz.dir/clean:
	cd /home/ego/projects/minecpp/build/_deps/grpc-build && $(CMAKE_COMMAND) -P CMakeFiles/grpcpp_channelz.dir/cmake_clean.cmake
.PHONY : _deps/grpc-build/CMakeFiles/grpcpp_channelz.dir/clean

_deps/grpc-build/CMakeFiles/grpcpp_channelz.dir/depend: gens/src/proto/grpc/channelz/channelz.grpc.pb.cc
_deps/grpc-build/CMakeFiles/grpcpp_channelz.dir/depend: gens/src/proto/grpc/channelz/channelz.grpc.pb.h
_deps/grpc-build/CMakeFiles/grpcpp_channelz.dir/depend: gens/src/proto/grpc/channelz/channelz.pb.cc
_deps/grpc-build/CMakeFiles/grpcpp_channelz.dir/depend: gens/src/proto/grpc/channelz/channelz.pb.h
_deps/grpc-build/CMakeFiles/grpcpp_channelz.dir/depend: gens/src/proto/grpc/channelz/channelz_mock.grpc.pb.h
	cd /home/ego/projects/minecpp/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ego/projects/minecpp /home/ego/projects/minecpp/build/_deps/grpc-src /home/ego/projects/minecpp/build /home/ego/projects/minecpp/build/_deps/grpc-build /home/ego/projects/minecpp/build/_deps/grpc-build/CMakeFiles/grpcpp_channelz.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : _deps/grpc-build/CMakeFiles/grpcpp_channelz.dir/depend
