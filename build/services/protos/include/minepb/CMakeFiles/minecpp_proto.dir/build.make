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
include services/protos/include/minepb/CMakeFiles/minecpp_proto.dir/depend.make

# Include the progress variables for this target.
include services/protos/include/minepb/CMakeFiles/minecpp_proto.dir/progress.make

# Include the compile flags for this target's objects.
include services/protos/include/minepb/CMakeFiles/minecpp_proto.dir/flags.make

services/protos/include/minepb/CMakeFiles/minecpp_proto.dir/engine.grpc.pb.cc.o: services/protos/include/minepb/CMakeFiles/minecpp_proto.dir/flags.make
services/protos/include/minepb/CMakeFiles/minecpp_proto.dir/engine.grpc.pb.cc.o: ../services/protos/include/minepb/engine.grpc.pb.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ego/projects/minecpp/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object services/protos/include/minepb/CMakeFiles/minecpp_proto.dir/engine.grpc.pb.cc.o"
	cd /home/ego/projects/minecpp/build/services/protos/include/minepb && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/minecpp_proto.dir/engine.grpc.pb.cc.o -c /home/ego/projects/minecpp/services/protos/include/minepb/engine.grpc.pb.cc

services/protos/include/minepb/CMakeFiles/minecpp_proto.dir/engine.grpc.pb.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/minecpp_proto.dir/engine.grpc.pb.cc.i"
	cd /home/ego/projects/minecpp/build/services/protos/include/minepb && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ego/projects/minecpp/services/protos/include/minepb/engine.grpc.pb.cc > CMakeFiles/minecpp_proto.dir/engine.grpc.pb.cc.i

services/protos/include/minepb/CMakeFiles/minecpp_proto.dir/engine.grpc.pb.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/minecpp_proto.dir/engine.grpc.pb.cc.s"
	cd /home/ego/projects/minecpp/build/services/protos/include/minepb && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ego/projects/minecpp/services/protos/include/minepb/engine.grpc.pb.cc -o CMakeFiles/minecpp_proto.dir/engine.grpc.pb.cc.s

services/protos/include/minepb/CMakeFiles/minecpp_proto.dir/engine.pb.cc.o: services/protos/include/minepb/CMakeFiles/minecpp_proto.dir/flags.make
services/protos/include/minepb/CMakeFiles/minecpp_proto.dir/engine.pb.cc.o: ../services/protos/include/minepb/engine.pb.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ego/projects/minecpp/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object services/protos/include/minepb/CMakeFiles/minecpp_proto.dir/engine.pb.cc.o"
	cd /home/ego/projects/minecpp/build/services/protos/include/minepb && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/minecpp_proto.dir/engine.pb.cc.o -c /home/ego/projects/minecpp/services/protos/include/minepb/engine.pb.cc

services/protos/include/minepb/CMakeFiles/minecpp_proto.dir/engine.pb.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/minecpp_proto.dir/engine.pb.cc.i"
	cd /home/ego/projects/minecpp/build/services/protos/include/minepb && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ego/projects/minecpp/services/protos/include/minepb/engine.pb.cc > CMakeFiles/minecpp_proto.dir/engine.pb.cc.i

services/protos/include/minepb/CMakeFiles/minecpp_proto.dir/engine.pb.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/minecpp_proto.dir/engine.pb.cc.s"
	cd /home/ego/projects/minecpp/build/services/protos/include/minepb && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ego/projects/minecpp/services/protos/include/minepb/engine.pb.cc -o CMakeFiles/minecpp_proto.dir/engine.pb.cc.s

services/protos/include/minepb/CMakeFiles/minecpp_proto.dir/chunk.pb.cc.o: services/protos/include/minepb/CMakeFiles/minecpp_proto.dir/flags.make
services/protos/include/minepb/CMakeFiles/minecpp_proto.dir/chunk.pb.cc.o: ../services/protos/include/minepb/chunk.pb.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ego/projects/minecpp/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object services/protos/include/minepb/CMakeFiles/minecpp_proto.dir/chunk.pb.cc.o"
	cd /home/ego/projects/minecpp/build/services/protos/include/minepb && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/minecpp_proto.dir/chunk.pb.cc.o -c /home/ego/projects/minecpp/services/protos/include/minepb/chunk.pb.cc

services/protos/include/minepb/CMakeFiles/minecpp_proto.dir/chunk.pb.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/minecpp_proto.dir/chunk.pb.cc.i"
	cd /home/ego/projects/minecpp/build/services/protos/include/minepb && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ego/projects/minecpp/services/protos/include/minepb/chunk.pb.cc > CMakeFiles/minecpp_proto.dir/chunk.pb.cc.i

services/protos/include/minepb/CMakeFiles/minecpp_proto.dir/chunk.pb.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/minecpp_proto.dir/chunk.pb.cc.s"
	cd /home/ego/projects/minecpp/build/services/protos/include/minepb && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ego/projects/minecpp/services/protos/include/minepb/chunk.pb.cc -o CMakeFiles/minecpp_proto.dir/chunk.pb.cc.s

services/protos/include/minepb/CMakeFiles/minecpp_proto.dir/chunk_storage.grpc.pb.cc.o: services/protos/include/minepb/CMakeFiles/minecpp_proto.dir/flags.make
services/protos/include/minepb/CMakeFiles/minecpp_proto.dir/chunk_storage.grpc.pb.cc.o: ../services/protos/include/minepb/chunk_storage.grpc.pb.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ego/projects/minecpp/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object services/protos/include/minepb/CMakeFiles/minecpp_proto.dir/chunk_storage.grpc.pb.cc.o"
	cd /home/ego/projects/minecpp/build/services/protos/include/minepb && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/minecpp_proto.dir/chunk_storage.grpc.pb.cc.o -c /home/ego/projects/minecpp/services/protos/include/minepb/chunk_storage.grpc.pb.cc

services/protos/include/minepb/CMakeFiles/minecpp_proto.dir/chunk_storage.grpc.pb.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/minecpp_proto.dir/chunk_storage.grpc.pb.cc.i"
	cd /home/ego/projects/minecpp/build/services/protos/include/minepb && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ego/projects/minecpp/services/protos/include/minepb/chunk_storage.grpc.pb.cc > CMakeFiles/minecpp_proto.dir/chunk_storage.grpc.pb.cc.i

services/protos/include/minepb/CMakeFiles/minecpp_proto.dir/chunk_storage.grpc.pb.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/minecpp_proto.dir/chunk_storage.grpc.pb.cc.s"
	cd /home/ego/projects/minecpp/build/services/protos/include/minepb && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ego/projects/minecpp/services/protos/include/minepb/chunk_storage.grpc.pb.cc -o CMakeFiles/minecpp_proto.dir/chunk_storage.grpc.pb.cc.s

services/protos/include/minepb/CMakeFiles/minecpp_proto.dir/chunk_storage.pb.cc.o: services/protos/include/minepb/CMakeFiles/minecpp_proto.dir/flags.make
services/protos/include/minepb/CMakeFiles/minecpp_proto.dir/chunk_storage.pb.cc.o: ../services/protos/include/minepb/chunk_storage.pb.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ego/projects/minecpp/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object services/protos/include/minepb/CMakeFiles/minecpp_proto.dir/chunk_storage.pb.cc.o"
	cd /home/ego/projects/minecpp/build/services/protos/include/minepb && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/minecpp_proto.dir/chunk_storage.pb.cc.o -c /home/ego/projects/minecpp/services/protos/include/minepb/chunk_storage.pb.cc

services/protos/include/minepb/CMakeFiles/minecpp_proto.dir/chunk_storage.pb.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/minecpp_proto.dir/chunk_storage.pb.cc.i"
	cd /home/ego/projects/minecpp/build/services/protos/include/minepb && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ego/projects/minecpp/services/protos/include/minepb/chunk_storage.pb.cc > CMakeFiles/minecpp_proto.dir/chunk_storage.pb.cc.i

services/protos/include/minepb/CMakeFiles/minecpp_proto.dir/chunk_storage.pb.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/minecpp_proto.dir/chunk_storage.pb.cc.s"
	cd /home/ego/projects/minecpp/build/services/protos/include/minepb && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ego/projects/minecpp/services/protos/include/minepb/chunk_storage.pb.cc -o CMakeFiles/minecpp_proto.dir/chunk_storage.pb.cc.s

services/protos/include/minepb/CMakeFiles/minecpp_proto.dir/game.pb.cc.o: services/protos/include/minepb/CMakeFiles/minecpp_proto.dir/flags.make
services/protos/include/minepb/CMakeFiles/minecpp_proto.dir/game.pb.cc.o: ../services/protos/include/minepb/game.pb.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ego/projects/minecpp/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object services/protos/include/minepb/CMakeFiles/minecpp_proto.dir/game.pb.cc.o"
	cd /home/ego/projects/minecpp/build/services/protos/include/minepb && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/minecpp_proto.dir/game.pb.cc.o -c /home/ego/projects/minecpp/services/protos/include/minepb/game.pb.cc

services/protos/include/minepb/CMakeFiles/minecpp_proto.dir/game.pb.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/minecpp_proto.dir/game.pb.cc.i"
	cd /home/ego/projects/minecpp/build/services/protos/include/minepb && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ego/projects/minecpp/services/protos/include/minepb/game.pb.cc > CMakeFiles/minecpp_proto.dir/game.pb.cc.i

services/protos/include/minepb/CMakeFiles/minecpp_proto.dir/game.pb.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/minecpp_proto.dir/game.pb.cc.s"
	cd /home/ego/projects/minecpp/build/services/protos/include/minepb && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ego/projects/minecpp/services/protos/include/minepb/game.pb.cc -o CMakeFiles/minecpp_proto.dir/game.pb.cc.s

services/protos/include/minepb/CMakeFiles/minecpp_proto.dir/player.pb.cc.o: services/protos/include/minepb/CMakeFiles/minecpp_proto.dir/flags.make
services/protos/include/minepb/CMakeFiles/minecpp_proto.dir/player.pb.cc.o: ../services/protos/include/minepb/player.pb.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ego/projects/minecpp/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object services/protos/include/minepb/CMakeFiles/minecpp_proto.dir/player.pb.cc.o"
	cd /home/ego/projects/minecpp/build/services/protos/include/minepb && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/minecpp_proto.dir/player.pb.cc.o -c /home/ego/projects/minecpp/services/protos/include/minepb/player.pb.cc

services/protos/include/minepb/CMakeFiles/minecpp_proto.dir/player.pb.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/minecpp_proto.dir/player.pb.cc.i"
	cd /home/ego/projects/minecpp/build/services/protos/include/minepb && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ego/projects/minecpp/services/protos/include/minepb/player.pb.cc > CMakeFiles/minecpp_proto.dir/player.pb.cc.i

services/protos/include/minepb/CMakeFiles/minecpp_proto.dir/player.pb.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/minecpp_proto.dir/player.pb.cc.s"
	cd /home/ego/projects/minecpp/build/services/protos/include/minepb && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ego/projects/minecpp/services/protos/include/minepb/player.pb.cc -o CMakeFiles/minecpp_proto.dir/player.pb.cc.s

services/protos/include/minepb/CMakeFiles/minecpp_proto.dir/events.pb.cc.o: services/protos/include/minepb/CMakeFiles/minecpp_proto.dir/flags.make
services/protos/include/minepb/CMakeFiles/minecpp_proto.dir/events.pb.cc.o: ../services/protos/include/minepb/events.pb.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ego/projects/minecpp/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object services/protos/include/minepb/CMakeFiles/minecpp_proto.dir/events.pb.cc.o"
	cd /home/ego/projects/minecpp/build/services/protos/include/minepb && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/minecpp_proto.dir/events.pb.cc.o -c /home/ego/projects/minecpp/services/protos/include/minepb/events.pb.cc

services/protos/include/minepb/CMakeFiles/minecpp_proto.dir/events.pb.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/minecpp_proto.dir/events.pb.cc.i"
	cd /home/ego/projects/minecpp/build/services/protos/include/minepb && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ego/projects/minecpp/services/protos/include/minepb/events.pb.cc > CMakeFiles/minecpp_proto.dir/events.pb.cc.i

services/protos/include/minepb/CMakeFiles/minecpp_proto.dir/events.pb.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/minecpp_proto.dir/events.pb.cc.s"
	cd /home/ego/projects/minecpp/build/services/protos/include/minepb && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ego/projects/minecpp/services/protos/include/minepb/events.pb.cc -o CMakeFiles/minecpp_proto.dir/events.pb.cc.s

# Object files for target minecpp_proto
minecpp_proto_OBJECTS = \
"CMakeFiles/minecpp_proto.dir/engine.grpc.pb.cc.o" \
"CMakeFiles/minecpp_proto.dir/engine.pb.cc.o" \
"CMakeFiles/minecpp_proto.dir/chunk.pb.cc.o" \
"CMakeFiles/minecpp_proto.dir/chunk_storage.grpc.pb.cc.o" \
"CMakeFiles/minecpp_proto.dir/chunk_storage.pb.cc.o" \
"CMakeFiles/minecpp_proto.dir/game.pb.cc.o" \
"CMakeFiles/minecpp_proto.dir/player.pb.cc.o" \
"CMakeFiles/minecpp_proto.dir/events.pb.cc.o"

# External object files for target minecpp_proto
minecpp_proto_EXTERNAL_OBJECTS =

services/protos/include/minepb/libminecpp_proto.a: services/protos/include/minepb/CMakeFiles/minecpp_proto.dir/engine.grpc.pb.cc.o
services/protos/include/minepb/libminecpp_proto.a: services/protos/include/minepb/CMakeFiles/minecpp_proto.dir/engine.pb.cc.o
services/protos/include/minepb/libminecpp_proto.a: services/protos/include/minepb/CMakeFiles/minecpp_proto.dir/chunk.pb.cc.o
services/protos/include/minepb/libminecpp_proto.a: services/protos/include/minepb/CMakeFiles/minecpp_proto.dir/chunk_storage.grpc.pb.cc.o
services/protos/include/minepb/libminecpp_proto.a: services/protos/include/minepb/CMakeFiles/minecpp_proto.dir/chunk_storage.pb.cc.o
services/protos/include/minepb/libminecpp_proto.a: services/protos/include/minepb/CMakeFiles/minecpp_proto.dir/game.pb.cc.o
services/protos/include/minepb/libminecpp_proto.a: services/protos/include/minepb/CMakeFiles/minecpp_proto.dir/player.pb.cc.o
services/protos/include/minepb/libminecpp_proto.a: services/protos/include/minepb/CMakeFiles/minecpp_proto.dir/events.pb.cc.o
services/protos/include/minepb/libminecpp_proto.a: services/protos/include/minepb/CMakeFiles/minecpp_proto.dir/build.make
services/protos/include/minepb/libminecpp_proto.a: services/protos/include/minepb/CMakeFiles/minecpp_proto.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/ego/projects/minecpp/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Linking CXX static library libminecpp_proto.a"
	cd /home/ego/projects/minecpp/build/services/protos/include/minepb && $(CMAKE_COMMAND) -P CMakeFiles/minecpp_proto.dir/cmake_clean_target.cmake
	cd /home/ego/projects/minecpp/build/services/protos/include/minepb && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/minecpp_proto.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
services/protos/include/minepb/CMakeFiles/minecpp_proto.dir/build: services/protos/include/minepb/libminecpp_proto.a

.PHONY : services/protos/include/minepb/CMakeFiles/minecpp_proto.dir/build

services/protos/include/minepb/CMakeFiles/minecpp_proto.dir/clean:
	cd /home/ego/projects/minecpp/build/services/protos/include/minepb && $(CMAKE_COMMAND) -P CMakeFiles/minecpp_proto.dir/cmake_clean.cmake
.PHONY : services/protos/include/minepb/CMakeFiles/minecpp_proto.dir/clean

services/protos/include/minepb/CMakeFiles/minecpp_proto.dir/depend:
	cd /home/ego/projects/minecpp/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ego/projects/minecpp /home/ego/projects/minecpp/services/protos/include/minepb /home/ego/projects/minecpp/build /home/ego/projects/minecpp/build/services/protos/include/minepb /home/ego/projects/minecpp/build/services/protos/include/minepb/CMakeFiles/minecpp_proto.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : services/protos/include/minepb/CMakeFiles/minecpp_proto.dir/depend
