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
include services/front/CMakeFiles/minecpp_front.dir/depend.make

# Include the progress variables for this target.
include services/front/CMakeFiles/minecpp_front.dir/progress.make

# Include the compile flags for this target's objects.
include services/front/CMakeFiles/minecpp_front.dir/flags.make

services/front/CMakeFiles/minecpp_front.dir/main.cpp.o: services/front/CMakeFiles/minecpp_front.dir/flags.make
services/front/CMakeFiles/minecpp_front.dir/main.cpp.o: ../services/front/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ego/projects/minecpp/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object services/front/CMakeFiles/minecpp_front.dir/main.cpp.o"
	cd /home/ego/projects/minecpp/build/services/front && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/minecpp_front.dir/main.cpp.o -c /home/ego/projects/minecpp/services/front/main.cpp

services/front/CMakeFiles/minecpp_front.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/minecpp_front.dir/main.cpp.i"
	cd /home/ego/projects/minecpp/build/services/front && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ego/projects/minecpp/services/front/main.cpp > CMakeFiles/minecpp_front.dir/main.cpp.i

services/front/CMakeFiles/minecpp_front.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/minecpp_front.dir/main.cpp.s"
	cd /home/ego/projects/minecpp/build/services/front && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ego/projects/minecpp/services/front/main.cpp -o CMakeFiles/minecpp_front.dir/main.cpp.s

services/front/CMakeFiles/minecpp_front.dir/connection.cpp.o: services/front/CMakeFiles/minecpp_front.dir/flags.make
services/front/CMakeFiles/minecpp_front.dir/connection.cpp.o: ../services/front/connection.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ego/projects/minecpp/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object services/front/CMakeFiles/minecpp_front.dir/connection.cpp.o"
	cd /home/ego/projects/minecpp/build/services/front && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/minecpp_front.dir/connection.cpp.o -c /home/ego/projects/minecpp/services/front/connection.cpp

services/front/CMakeFiles/minecpp_front.dir/connection.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/minecpp_front.dir/connection.cpp.i"
	cd /home/ego/projects/minecpp/build/services/front && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ego/projects/minecpp/services/front/connection.cpp > CMakeFiles/minecpp_front.dir/connection.cpp.i

services/front/CMakeFiles/minecpp_front.dir/connection.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/minecpp_front.dir/connection.cpp.s"
	cd /home/ego/projects/minecpp/build/services/front && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ego/projects/minecpp/services/front/connection.cpp -o CMakeFiles/minecpp_front.dir/connection.cpp.s

services/front/CMakeFiles/minecpp_front.dir/server.cpp.o: services/front/CMakeFiles/minecpp_front.dir/flags.make
services/front/CMakeFiles/minecpp_front.dir/server.cpp.o: ../services/front/server.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ego/projects/minecpp/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object services/front/CMakeFiles/minecpp_front.dir/server.cpp.o"
	cd /home/ego/projects/minecpp/build/services/front && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/minecpp_front.dir/server.cpp.o -c /home/ego/projects/minecpp/services/front/server.cpp

services/front/CMakeFiles/minecpp_front.dir/server.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/minecpp_front.dir/server.cpp.i"
	cd /home/ego/projects/minecpp/build/services/front && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ego/projects/minecpp/services/front/server.cpp > CMakeFiles/minecpp_front.dir/server.cpp.i

services/front/CMakeFiles/minecpp_front.dir/server.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/minecpp_front.dir/server.cpp.s"
	cd /home/ego/projects/minecpp/build/services/front && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ego/projects/minecpp/services/front/server.cpp -o CMakeFiles/minecpp_front.dir/server.cpp.s

services/front/CMakeFiles/minecpp_front.dir/protocol/protocol.cpp.o: services/front/CMakeFiles/minecpp_front.dir/flags.make
services/front/CMakeFiles/minecpp_front.dir/protocol/protocol.cpp.o: ../services/front/protocol/protocol.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ego/projects/minecpp/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object services/front/CMakeFiles/minecpp_front.dir/protocol/protocol.cpp.o"
	cd /home/ego/projects/minecpp/build/services/front && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/minecpp_front.dir/protocol/protocol.cpp.o -c /home/ego/projects/minecpp/services/front/protocol/protocol.cpp

services/front/CMakeFiles/minecpp_front.dir/protocol/protocol.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/minecpp_front.dir/protocol/protocol.cpp.i"
	cd /home/ego/projects/minecpp/build/services/front && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ego/projects/minecpp/services/front/protocol/protocol.cpp > CMakeFiles/minecpp_front.dir/protocol/protocol.cpp.i

services/front/CMakeFiles/minecpp_front.dir/protocol/protocol.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/minecpp_front.dir/protocol/protocol.cpp.s"
	cd /home/ego/projects/minecpp/build/services/front && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ego/projects/minecpp/services/front/protocol/protocol.cpp -o CMakeFiles/minecpp_front.dir/protocol/protocol.cpp.s

services/front/CMakeFiles/minecpp_front.dir/protocol/status_handler.cpp.o: services/front/CMakeFiles/minecpp_front.dir/flags.make
services/front/CMakeFiles/minecpp_front.dir/protocol/status_handler.cpp.o: ../services/front/protocol/status_handler.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ego/projects/minecpp/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object services/front/CMakeFiles/minecpp_front.dir/protocol/status_handler.cpp.o"
	cd /home/ego/projects/minecpp/build/services/front && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/minecpp_front.dir/protocol/status_handler.cpp.o -c /home/ego/projects/minecpp/services/front/protocol/status_handler.cpp

services/front/CMakeFiles/minecpp_front.dir/protocol/status_handler.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/minecpp_front.dir/protocol/status_handler.cpp.i"
	cd /home/ego/projects/minecpp/build/services/front && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ego/projects/minecpp/services/front/protocol/status_handler.cpp > CMakeFiles/minecpp_front.dir/protocol/status_handler.cpp.i

services/front/CMakeFiles/minecpp_front.dir/protocol/status_handler.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/minecpp_front.dir/protocol/status_handler.cpp.s"
	cd /home/ego/projects/minecpp/build/services/front && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ego/projects/minecpp/services/front/protocol/status_handler.cpp -o CMakeFiles/minecpp_front.dir/protocol/status_handler.cpp.s

services/front/CMakeFiles/minecpp_front.dir/protocol/login_handler.cpp.o: services/front/CMakeFiles/minecpp_front.dir/flags.make
services/front/CMakeFiles/minecpp_front.dir/protocol/login_handler.cpp.o: ../services/front/protocol/login_handler.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ego/projects/minecpp/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object services/front/CMakeFiles/minecpp_front.dir/protocol/login_handler.cpp.o"
	cd /home/ego/projects/minecpp/build/services/front && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/minecpp_front.dir/protocol/login_handler.cpp.o -c /home/ego/projects/minecpp/services/front/protocol/login_handler.cpp

services/front/CMakeFiles/minecpp_front.dir/protocol/login_handler.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/minecpp_front.dir/protocol/login_handler.cpp.i"
	cd /home/ego/projects/minecpp/build/services/front && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ego/projects/minecpp/services/front/protocol/login_handler.cpp > CMakeFiles/minecpp_front.dir/protocol/login_handler.cpp.i

services/front/CMakeFiles/minecpp_front.dir/protocol/login_handler.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/minecpp_front.dir/protocol/login_handler.cpp.s"
	cd /home/ego/projects/minecpp/build/services/front && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ego/projects/minecpp/services/front/protocol/login_handler.cpp -o CMakeFiles/minecpp_front.dir/protocol/login_handler.cpp.s

services/front/CMakeFiles/minecpp_front.dir/protocol/play_handler.cpp.o: services/front/CMakeFiles/minecpp_front.dir/flags.make
services/front/CMakeFiles/minecpp_front.dir/protocol/play_handler.cpp.o: ../services/front/protocol/play_handler.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ego/projects/minecpp/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object services/front/CMakeFiles/minecpp_front.dir/protocol/play_handler.cpp.o"
	cd /home/ego/projects/minecpp/build/services/front && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/minecpp_front.dir/protocol/play_handler.cpp.o -c /home/ego/projects/minecpp/services/front/protocol/play_handler.cpp

services/front/CMakeFiles/minecpp_front.dir/protocol/play_handler.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/minecpp_front.dir/protocol/play_handler.cpp.i"
	cd /home/ego/projects/minecpp/build/services/front && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ego/projects/minecpp/services/front/protocol/play_handler.cpp > CMakeFiles/minecpp_front.dir/protocol/play_handler.cpp.i

services/front/CMakeFiles/minecpp_front.dir/protocol/play_handler.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/minecpp_front.dir/protocol/play_handler.cpp.s"
	cd /home/ego/projects/minecpp/build/services/front && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ego/projects/minecpp/services/front/protocol/play_handler.cpp -o CMakeFiles/minecpp_front.dir/protocol/play_handler.cpp.s

services/front/CMakeFiles/minecpp_front.dir/service.cpp.o: services/front/CMakeFiles/minecpp_front.dir/flags.make
services/front/CMakeFiles/minecpp_front.dir/service.cpp.o: ../services/front/service.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ego/projects/minecpp/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object services/front/CMakeFiles/minecpp_front.dir/service.cpp.o"
	cd /home/ego/projects/minecpp/build/services/front && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/minecpp_front.dir/service.cpp.o -c /home/ego/projects/minecpp/services/front/service.cpp

services/front/CMakeFiles/minecpp_front.dir/service.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/minecpp_front.dir/service.cpp.i"
	cd /home/ego/projects/minecpp/build/services/front && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ego/projects/minecpp/services/front/service.cpp > CMakeFiles/minecpp_front.dir/service.cpp.i

services/front/CMakeFiles/minecpp_front.dir/service.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/minecpp_front.dir/service.cpp.s"
	cd /home/ego/projects/minecpp/build/services/front && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ego/projects/minecpp/services/front/service.cpp -o CMakeFiles/minecpp_front.dir/service.cpp.s

services/front/CMakeFiles/minecpp_front.dir/config.cpp.o: services/front/CMakeFiles/minecpp_front.dir/flags.make
services/front/CMakeFiles/minecpp_front.dir/config.cpp.o: ../services/front/config.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ego/projects/minecpp/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object services/front/CMakeFiles/minecpp_front.dir/config.cpp.o"
	cd /home/ego/projects/minecpp/build/services/front && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/minecpp_front.dir/config.cpp.o -c /home/ego/projects/minecpp/services/front/config.cpp

services/front/CMakeFiles/minecpp_front.dir/config.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/minecpp_front.dir/config.cpp.i"
	cd /home/ego/projects/minecpp/build/services/front && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ego/projects/minecpp/services/front/config.cpp > CMakeFiles/minecpp_front.dir/config.cpp.i

services/front/CMakeFiles/minecpp_front.dir/config.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/minecpp_front.dir/config.cpp.s"
	cd /home/ego/projects/minecpp/build/services/front && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ego/projects/minecpp/services/front/config.cpp -o CMakeFiles/minecpp_front.dir/config.cpp.s

services/front/CMakeFiles/minecpp_front.dir/event_handler.cpp.o: services/front/CMakeFiles/minecpp_front.dir/flags.make
services/front/CMakeFiles/minecpp_front.dir/event_handler.cpp.o: ../services/front/event_handler.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ego/projects/minecpp/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Building CXX object services/front/CMakeFiles/minecpp_front.dir/event_handler.cpp.o"
	cd /home/ego/projects/minecpp/build/services/front && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/minecpp_front.dir/event_handler.cpp.o -c /home/ego/projects/minecpp/services/front/event_handler.cpp

services/front/CMakeFiles/minecpp_front.dir/event_handler.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/minecpp_front.dir/event_handler.cpp.i"
	cd /home/ego/projects/minecpp/build/services/front && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ego/projects/minecpp/services/front/event_handler.cpp > CMakeFiles/minecpp_front.dir/event_handler.cpp.i

services/front/CMakeFiles/minecpp_front.dir/event_handler.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/minecpp_front.dir/event_handler.cpp.s"
	cd /home/ego/projects/minecpp/build/services/front && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ego/projects/minecpp/services/front/event_handler.cpp -o CMakeFiles/minecpp_front.dir/event_handler.cpp.s

services/front/CMakeFiles/minecpp_front.dir/ticks.cpp.o: services/front/CMakeFiles/minecpp_front.dir/flags.make
services/front/CMakeFiles/minecpp_front.dir/ticks.cpp.o: ../services/front/ticks.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ego/projects/minecpp/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_11) "Building CXX object services/front/CMakeFiles/minecpp_front.dir/ticks.cpp.o"
	cd /home/ego/projects/minecpp/build/services/front && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/minecpp_front.dir/ticks.cpp.o -c /home/ego/projects/minecpp/services/front/ticks.cpp

services/front/CMakeFiles/minecpp_front.dir/ticks.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/minecpp_front.dir/ticks.cpp.i"
	cd /home/ego/projects/minecpp/build/services/front && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ego/projects/minecpp/services/front/ticks.cpp > CMakeFiles/minecpp_front.dir/ticks.cpp.i

services/front/CMakeFiles/minecpp_front.dir/ticks.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/minecpp_front.dir/ticks.cpp.s"
	cd /home/ego/projects/minecpp/build/services/front && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ego/projects/minecpp/services/front/ticks.cpp -o CMakeFiles/minecpp_front.dir/ticks.cpp.s

services/front/CMakeFiles/minecpp_front.dir/__/engine/client/provider.cpp.o: services/front/CMakeFiles/minecpp_front.dir/flags.make
services/front/CMakeFiles/minecpp_front.dir/__/engine/client/provider.cpp.o: ../services/engine/client/provider.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ego/projects/minecpp/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_12) "Building CXX object services/front/CMakeFiles/minecpp_front.dir/__/engine/client/provider.cpp.o"
	cd /home/ego/projects/minecpp/build/services/front && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/minecpp_front.dir/__/engine/client/provider.cpp.o -c /home/ego/projects/minecpp/services/engine/client/provider.cpp

services/front/CMakeFiles/minecpp_front.dir/__/engine/client/provider.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/minecpp_front.dir/__/engine/client/provider.cpp.i"
	cd /home/ego/projects/minecpp/build/services/front && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ego/projects/minecpp/services/engine/client/provider.cpp > CMakeFiles/minecpp_front.dir/__/engine/client/provider.cpp.i

services/front/CMakeFiles/minecpp_front.dir/__/engine/client/provider.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/minecpp_front.dir/__/engine/client/provider.cpp.s"
	cd /home/ego/projects/minecpp/build/services/front && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ego/projects/minecpp/services/engine/client/provider.cpp -o CMakeFiles/minecpp_front.dir/__/engine/client/provider.cpp.s

# Object files for target minecpp_front
minecpp_front_OBJECTS = \
"CMakeFiles/minecpp_front.dir/main.cpp.o" \
"CMakeFiles/minecpp_front.dir/connection.cpp.o" \
"CMakeFiles/minecpp_front.dir/server.cpp.o" \
"CMakeFiles/minecpp_front.dir/protocol/protocol.cpp.o" \
"CMakeFiles/minecpp_front.dir/protocol/status_handler.cpp.o" \
"CMakeFiles/minecpp_front.dir/protocol/login_handler.cpp.o" \
"CMakeFiles/minecpp_front.dir/protocol/play_handler.cpp.o" \
"CMakeFiles/minecpp_front.dir/service.cpp.o" \
"CMakeFiles/minecpp_front.dir/config.cpp.o" \
"CMakeFiles/minecpp_front.dir/event_handler.cpp.o" \
"CMakeFiles/minecpp_front.dir/ticks.cpp.o" \
"CMakeFiles/minecpp_front.dir/__/engine/client/provider.cpp.o"

# External object files for target minecpp_front
minecpp_front_EXTERNAL_OBJECTS =

services/front/minecpp_front: services/front/CMakeFiles/minecpp_front.dir/main.cpp.o
services/front/minecpp_front: services/front/CMakeFiles/minecpp_front.dir/connection.cpp.o
services/front/minecpp_front: services/front/CMakeFiles/minecpp_front.dir/server.cpp.o
services/front/minecpp_front: services/front/CMakeFiles/minecpp_front.dir/protocol/protocol.cpp.o
services/front/minecpp_front: services/front/CMakeFiles/minecpp_front.dir/protocol/status_handler.cpp.o
services/front/minecpp_front: services/front/CMakeFiles/minecpp_front.dir/protocol/login_handler.cpp.o
services/front/minecpp_front: services/front/CMakeFiles/minecpp_front.dir/protocol/play_handler.cpp.o
services/front/minecpp_front: services/front/CMakeFiles/minecpp_front.dir/service.cpp.o
services/front/minecpp_front: services/front/CMakeFiles/minecpp_front.dir/config.cpp.o
services/front/minecpp_front: services/front/CMakeFiles/minecpp_front.dir/event_handler.cpp.o
services/front/minecpp_front: services/front/CMakeFiles/minecpp_front.dir/ticks.cpp.o
services/front/minecpp_front: services/front/CMakeFiles/minecpp_front.dir/__/engine/client/provider.cpp.o
services/front/minecpp_front: services/front/CMakeFiles/minecpp_front.dir/build.make
services/front/minecpp_front: lib/mineutils/libminecpp_utils.a
services/front/minecpp_front: services/protos/include/minepb/libminecpp_proto.a
services/front/minecpp_front: lib/minenet/libminecpp_net.a
services/front/minecpp_front: _deps/yaml-build/libyaml-cpp.a
services/front/minecpp_front: _deps/grpc-build/libgrpc++.a
services/front/minecpp_front: _deps/spdlog-build/libspdlog.a
services/front/minecpp_front: lib/game/libminecpp_game.a
services/front/minecpp_front: _deps/spdlog-build/libspdlog.a
services/front/minecpp_front: lib/nbt/libminecpp_nbt.a
services/front/minecpp_front: lib/error/libminecpp_error.a
services/front/minecpp_front: lib/squeeze/libminecpp_squeeze.a
services/front/minecpp_front: lib/mineutils/libminecpp_utils.a
services/front/minecpp_front: _deps/fmt-build/libfmt.a
services/front/minecpp_front: _deps/grpc-build/third_party/protobuf/libprotobuf.a
services/front/minecpp_front: _deps/grpc-build/libgrpc.a
services/front/minecpp_front: _deps/grpc-build/third_party/boringssl-with-bazel/libssl.a
services/front/minecpp_front: _deps/grpc-build/third_party/boringssl-with-bazel/libcrypto.a
services/front/minecpp_front: _deps/grpc-build/third_party/zlib/libz.a
services/front/minecpp_front: _deps/grpc-build/third_party/cares/cares/lib/libcares.a
services/front/minecpp_front: _deps/grpc-build/third_party/re2/libre2.a
services/front/minecpp_front: _deps/grpc-build/third_party/abseil-cpp/absl/status/libabsl_statusor.a
services/front/minecpp_front: _deps/grpc-build/third_party/abseil-cpp/absl/hash/libabsl_hash.a
services/front/minecpp_front: _deps/grpc-build/third_party/abseil-cpp/absl/types/libabsl_bad_variant_access.a
services/front/minecpp_front: _deps/grpc-build/third_party/abseil-cpp/absl/hash/libabsl_city.a
services/front/minecpp_front: _deps/grpc-build/third_party/abseil-cpp/absl/container/libabsl_raw_hash_set.a
services/front/minecpp_front: _deps/grpc-build/third_party/abseil-cpp/absl/container/libabsl_hashtablez_sampler.a
services/front/minecpp_front: _deps/grpc-build/third_party/abseil-cpp/absl/base/libabsl_exponential_biased.a
services/front/minecpp_front: _deps/grpc-build/libgpr.a
services/front/minecpp_front: _deps/grpc-build/third_party/abseil-cpp/absl/status/libabsl_status.a
services/front/minecpp_front: _deps/grpc-build/third_party/abseil-cpp/absl/strings/libabsl_cord.a
services/front/minecpp_front: _deps/grpc-build/third_party/abseil-cpp/absl/types/libabsl_bad_optional_access.a
services/front/minecpp_front: _deps/grpc-build/third_party/abseil-cpp/absl/synchronization/libabsl_synchronization.a
services/front/minecpp_front: _deps/grpc-build/third_party/abseil-cpp/absl/debugging/libabsl_stacktrace.a
services/front/minecpp_front: _deps/grpc-build/third_party/abseil-cpp/absl/debugging/libabsl_symbolize.a
services/front/minecpp_front: _deps/grpc-build/third_party/abseil-cpp/absl/debugging/libabsl_debugging_internal.a
services/front/minecpp_front: _deps/grpc-build/third_party/abseil-cpp/absl/debugging/libabsl_demangle_internal.a
services/front/minecpp_front: _deps/grpc-build/third_party/abseil-cpp/absl/synchronization/libabsl_graphcycles_internal.a
services/front/minecpp_front: _deps/grpc-build/third_party/abseil-cpp/absl/time/libabsl_time.a
services/front/minecpp_front: _deps/grpc-build/third_party/abseil-cpp/absl/time/libabsl_civil_time.a
services/front/minecpp_front: _deps/grpc-build/third_party/abseil-cpp/absl/time/libabsl_time_zone.a
services/front/minecpp_front: _deps/grpc-build/third_party/abseil-cpp/absl/base/libabsl_malloc_internal.a
services/front/minecpp_front: _deps/grpc-build/third_party/abseil-cpp/absl/strings/libabsl_str_format_internal.a
services/front/minecpp_front: _deps/grpc-build/third_party/abseil-cpp/absl/strings/libabsl_strings.a
services/front/minecpp_front: _deps/grpc-build/third_party/abseil-cpp/absl/strings/libabsl_strings_internal.a
services/front/minecpp_front: _deps/grpc-build/third_party/abseil-cpp/absl/numeric/libabsl_int128.a
services/front/minecpp_front: _deps/grpc-build/third_party/abseil-cpp/absl/base/libabsl_throw_delegate.a
services/front/minecpp_front: _deps/grpc-build/third_party/abseil-cpp/absl/base/libabsl_base.a
services/front/minecpp_front: _deps/grpc-build/third_party/abseil-cpp/absl/base/libabsl_raw_logging_internal.a
services/front/minecpp_front: _deps/grpc-build/third_party/abseil-cpp/absl/base/libabsl_log_severity.a
services/front/minecpp_front: _deps/grpc-build/third_party/abseil-cpp/absl/base/libabsl_spinlock_wait.a
services/front/minecpp_front: _deps/grpc-build/libaddress_sorting.a
services/front/minecpp_front: _deps/grpc-build/libupb.a
services/front/minecpp_front: services/front/CMakeFiles/minecpp_front.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/ego/projects/minecpp/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_13) "Linking CXX executable minecpp_front"
	cd /home/ego/projects/minecpp/build/services/front && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/minecpp_front.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
services/front/CMakeFiles/minecpp_front.dir/build: services/front/minecpp_front

.PHONY : services/front/CMakeFiles/minecpp_front.dir/build

services/front/CMakeFiles/minecpp_front.dir/clean:
	cd /home/ego/projects/minecpp/build/services/front && $(CMAKE_COMMAND) -P CMakeFiles/minecpp_front.dir/cmake_clean.cmake
.PHONY : services/front/CMakeFiles/minecpp_front.dir/clean

services/front/CMakeFiles/minecpp_front.dir/depend:
	cd /home/ego/projects/minecpp/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ego/projects/minecpp /home/ego/projects/minecpp/services/front /home/ego/projects/minecpp/build /home/ego/projects/minecpp/build/services/front /home/ego/projects/minecpp/build/services/front/CMakeFiles/minecpp_front.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : services/front/CMakeFiles/minecpp_front.dir/depend

