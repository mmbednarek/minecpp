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
include services/chunk_storage/CMakeFiles/minecpp_chunk_storage.dir/depend.make

# Include the progress variables for this target.
include services/chunk_storage/CMakeFiles/minecpp_chunk_storage.dir/progress.make

# Include the compile flags for this target's objects.
include services/chunk_storage/CMakeFiles/minecpp_chunk_storage.dir/flags.make

services/chunk_storage/CMakeFiles/minecpp_chunk_storage.dir/service.cpp.o: services/chunk_storage/CMakeFiles/minecpp_chunk_storage.dir/flags.make
services/chunk_storage/CMakeFiles/minecpp_chunk_storage.dir/service.cpp.o: ../services/chunk_storage/service.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ego/projects/minecpp/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object services/chunk_storage/CMakeFiles/minecpp_chunk_storage.dir/service.cpp.o"
	cd /home/ego/projects/minecpp/build/services/chunk_storage && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/minecpp_chunk_storage.dir/service.cpp.o -c /home/ego/projects/minecpp/services/chunk_storage/service.cpp

services/chunk_storage/CMakeFiles/minecpp_chunk_storage.dir/service.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/minecpp_chunk_storage.dir/service.cpp.i"
	cd /home/ego/projects/minecpp/build/services/chunk_storage && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ego/projects/minecpp/services/chunk_storage/service.cpp > CMakeFiles/minecpp_chunk_storage.dir/service.cpp.i

services/chunk_storage/CMakeFiles/minecpp_chunk_storage.dir/service.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/minecpp_chunk_storage.dir/service.cpp.s"
	cd /home/ego/projects/minecpp/build/services/chunk_storage && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ego/projects/minecpp/services/chunk_storage/service.cpp -o CMakeFiles/minecpp_chunk_storage.dir/service.cpp.s

services/chunk_storage/CMakeFiles/minecpp_chunk_storage.dir/main.cpp.o: services/chunk_storage/CMakeFiles/minecpp_chunk_storage.dir/flags.make
services/chunk_storage/CMakeFiles/minecpp_chunk_storage.dir/main.cpp.o: ../services/chunk_storage/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ego/projects/minecpp/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object services/chunk_storage/CMakeFiles/minecpp_chunk_storage.dir/main.cpp.o"
	cd /home/ego/projects/minecpp/build/services/chunk_storage && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/minecpp_chunk_storage.dir/main.cpp.o -c /home/ego/projects/minecpp/services/chunk_storage/main.cpp

services/chunk_storage/CMakeFiles/minecpp_chunk_storage.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/minecpp_chunk_storage.dir/main.cpp.i"
	cd /home/ego/projects/minecpp/build/services/chunk_storage && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ego/projects/minecpp/services/chunk_storage/main.cpp > CMakeFiles/minecpp_chunk_storage.dir/main.cpp.i

services/chunk_storage/CMakeFiles/minecpp_chunk_storage.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/minecpp_chunk_storage.dir/main.cpp.s"
	cd /home/ego/projects/minecpp/build/services/chunk_storage && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ego/projects/minecpp/services/chunk_storage/main.cpp -o CMakeFiles/minecpp_chunk_storage.dir/main.cpp.s

services/chunk_storage/CMakeFiles/minecpp_chunk_storage.dir/regions.cpp.o: services/chunk_storage/CMakeFiles/minecpp_chunk_storage.dir/flags.make
services/chunk_storage/CMakeFiles/minecpp_chunk_storage.dir/regions.cpp.o: ../services/chunk_storage/regions.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ego/projects/minecpp/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object services/chunk_storage/CMakeFiles/minecpp_chunk_storage.dir/regions.cpp.o"
	cd /home/ego/projects/minecpp/build/services/chunk_storage && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/minecpp_chunk_storage.dir/regions.cpp.o -c /home/ego/projects/minecpp/services/chunk_storage/regions.cpp

services/chunk_storage/CMakeFiles/minecpp_chunk_storage.dir/regions.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/minecpp_chunk_storage.dir/regions.cpp.i"
	cd /home/ego/projects/minecpp/build/services/chunk_storage && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ego/projects/minecpp/services/chunk_storage/regions.cpp > CMakeFiles/minecpp_chunk_storage.dir/regions.cpp.i

services/chunk_storage/CMakeFiles/minecpp_chunk_storage.dir/regions.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/minecpp_chunk_storage.dir/regions.cpp.s"
	cd /home/ego/projects/minecpp/build/services/chunk_storage && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ego/projects/minecpp/services/chunk_storage/regions.cpp -o CMakeFiles/minecpp_chunk_storage.dir/regions.cpp.s

services/chunk_storage/CMakeFiles/minecpp_chunk_storage.dir/chunks.cpp.o: services/chunk_storage/CMakeFiles/minecpp_chunk_storage.dir/flags.make
services/chunk_storage/CMakeFiles/minecpp_chunk_storage.dir/chunks.cpp.o: ../services/chunk_storage/chunks.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ego/projects/minecpp/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object services/chunk_storage/CMakeFiles/minecpp_chunk_storage.dir/chunks.cpp.o"
	cd /home/ego/projects/minecpp/build/services/chunk_storage && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/minecpp_chunk_storage.dir/chunks.cpp.o -c /home/ego/projects/minecpp/services/chunk_storage/chunks.cpp

services/chunk_storage/CMakeFiles/minecpp_chunk_storage.dir/chunks.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/minecpp_chunk_storage.dir/chunks.cpp.i"
	cd /home/ego/projects/minecpp/build/services/chunk_storage && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ego/projects/minecpp/services/chunk_storage/chunks.cpp > CMakeFiles/minecpp_chunk_storage.dir/chunks.cpp.i

services/chunk_storage/CMakeFiles/minecpp_chunk_storage.dir/chunks.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/minecpp_chunk_storage.dir/chunks.cpp.s"
	cd /home/ego/projects/minecpp/build/services/chunk_storage && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ego/projects/minecpp/services/chunk_storage/chunks.cpp -o CMakeFiles/minecpp_chunk_storage.dir/chunks.cpp.s

# Object files for target minecpp_chunk_storage
minecpp_chunk_storage_OBJECTS = \
"CMakeFiles/minecpp_chunk_storage.dir/service.cpp.o" \
"CMakeFiles/minecpp_chunk_storage.dir/main.cpp.o" \
"CMakeFiles/minecpp_chunk_storage.dir/regions.cpp.o" \
"CMakeFiles/minecpp_chunk_storage.dir/chunks.cpp.o"

# External object files for target minecpp_chunk_storage
minecpp_chunk_storage_EXTERNAL_OBJECTS =

services/chunk_storage/minecpp_chunk_storage: services/chunk_storage/CMakeFiles/minecpp_chunk_storage.dir/service.cpp.o
services/chunk_storage/minecpp_chunk_storage: services/chunk_storage/CMakeFiles/minecpp_chunk_storage.dir/main.cpp.o
services/chunk_storage/minecpp_chunk_storage: services/chunk_storage/CMakeFiles/minecpp_chunk_storage.dir/regions.cpp.o
services/chunk_storage/minecpp_chunk_storage: services/chunk_storage/CMakeFiles/minecpp_chunk_storage.dir/chunks.cpp.o
services/chunk_storage/minecpp_chunk_storage: services/chunk_storage/CMakeFiles/minecpp_chunk_storage.dir/build.make
services/chunk_storage/minecpp_chunk_storage: lib/mineutils/libminecpp_utils.a
services/chunk_storage/minecpp_chunk_storage: lib/game/libminecpp_game.a
services/chunk_storage/minecpp_chunk_storage: lib/minenet/libminecpp_net.a
services/chunk_storage/minecpp_chunk_storage: lib/region/libminecpp_region.a
services/chunk_storage/minecpp_chunk_storage: services/protos/include/minepb/libminecpp_proto.a
services/chunk_storage/minecpp_chunk_storage: lib/error/libminecpp_error.a
services/chunk_storage/minecpp_chunk_storage: lib/minerandom/libminecpp_rand.a
services/chunk_storage/minecpp_chunk_storage: _deps/grpc-build/libgrpc++.a
services/chunk_storage/minecpp_chunk_storage: _deps/spdlog-build/libspdlog.a
services/chunk_storage/minecpp_chunk_storage: lib/game/libminecpp_game.a
services/chunk_storage/minecpp_chunk_storage: lib/error/libminecpp_error.a
services/chunk_storage/minecpp_chunk_storage: _deps/spdlog-build/libspdlog.a
services/chunk_storage/minecpp_chunk_storage: lib/squeeze/libminecpp_squeeze.a
services/chunk_storage/minecpp_chunk_storage: lib/nbt/libminecpp_nbt.a
services/chunk_storage/minecpp_chunk_storage: lib/mineutils/libminecpp_utils.a
services/chunk_storage/minecpp_chunk_storage: _deps/fmt-build/libfmt.a
services/chunk_storage/minecpp_chunk_storage: _deps/grpc-build/third_party/protobuf/libprotobuf.a
services/chunk_storage/minecpp_chunk_storage: _deps/grpc-build/libgrpc.a
services/chunk_storage/minecpp_chunk_storage: _deps/grpc-build/third_party/boringssl-with-bazel/libssl.a
services/chunk_storage/minecpp_chunk_storage: _deps/grpc-build/third_party/boringssl-with-bazel/libcrypto.a
services/chunk_storage/minecpp_chunk_storage: _deps/grpc-build/third_party/zlib/libz.a
services/chunk_storage/minecpp_chunk_storage: _deps/grpc-build/third_party/cares/cares/lib/libcares.a
services/chunk_storage/minecpp_chunk_storage: _deps/grpc-build/third_party/re2/libre2.a
services/chunk_storage/minecpp_chunk_storage: _deps/grpc-build/third_party/abseil-cpp/absl/status/libabsl_statusor.a
services/chunk_storage/minecpp_chunk_storage: _deps/grpc-build/third_party/abseil-cpp/absl/hash/libabsl_hash.a
services/chunk_storage/minecpp_chunk_storage: _deps/grpc-build/third_party/abseil-cpp/absl/types/libabsl_bad_variant_access.a
services/chunk_storage/minecpp_chunk_storage: _deps/grpc-build/third_party/abseil-cpp/absl/hash/libabsl_city.a
services/chunk_storage/minecpp_chunk_storage: _deps/grpc-build/third_party/abseil-cpp/absl/container/libabsl_raw_hash_set.a
services/chunk_storage/minecpp_chunk_storage: _deps/grpc-build/third_party/abseil-cpp/absl/container/libabsl_hashtablez_sampler.a
services/chunk_storage/minecpp_chunk_storage: _deps/grpc-build/third_party/abseil-cpp/absl/base/libabsl_exponential_biased.a
services/chunk_storage/minecpp_chunk_storage: _deps/grpc-build/libgpr.a
services/chunk_storage/minecpp_chunk_storage: _deps/grpc-build/third_party/abseil-cpp/absl/status/libabsl_status.a
services/chunk_storage/minecpp_chunk_storage: _deps/grpc-build/third_party/abseil-cpp/absl/strings/libabsl_cord.a
services/chunk_storage/minecpp_chunk_storage: _deps/grpc-build/third_party/abseil-cpp/absl/types/libabsl_bad_optional_access.a
services/chunk_storage/minecpp_chunk_storage: _deps/grpc-build/third_party/abseil-cpp/absl/synchronization/libabsl_synchronization.a
services/chunk_storage/minecpp_chunk_storage: _deps/grpc-build/third_party/abseil-cpp/absl/debugging/libabsl_stacktrace.a
services/chunk_storage/minecpp_chunk_storage: _deps/grpc-build/third_party/abseil-cpp/absl/debugging/libabsl_symbolize.a
services/chunk_storage/minecpp_chunk_storage: _deps/grpc-build/third_party/abseil-cpp/absl/debugging/libabsl_debugging_internal.a
services/chunk_storage/minecpp_chunk_storage: _deps/grpc-build/third_party/abseil-cpp/absl/debugging/libabsl_demangle_internal.a
services/chunk_storage/minecpp_chunk_storage: _deps/grpc-build/third_party/abseil-cpp/absl/synchronization/libabsl_graphcycles_internal.a
services/chunk_storage/minecpp_chunk_storage: _deps/grpc-build/third_party/abseil-cpp/absl/time/libabsl_time.a
services/chunk_storage/minecpp_chunk_storage: _deps/grpc-build/third_party/abseil-cpp/absl/time/libabsl_civil_time.a
services/chunk_storage/minecpp_chunk_storage: _deps/grpc-build/third_party/abseil-cpp/absl/time/libabsl_time_zone.a
services/chunk_storage/minecpp_chunk_storage: _deps/grpc-build/third_party/abseil-cpp/absl/base/libabsl_malloc_internal.a
services/chunk_storage/minecpp_chunk_storage: _deps/grpc-build/third_party/abseil-cpp/absl/strings/libabsl_str_format_internal.a
services/chunk_storage/minecpp_chunk_storage: _deps/grpc-build/third_party/abseil-cpp/absl/strings/libabsl_strings.a
services/chunk_storage/minecpp_chunk_storage: _deps/grpc-build/third_party/abseil-cpp/absl/strings/libabsl_strings_internal.a
services/chunk_storage/minecpp_chunk_storage: _deps/grpc-build/third_party/abseil-cpp/absl/numeric/libabsl_int128.a
services/chunk_storage/minecpp_chunk_storage: _deps/grpc-build/third_party/abseil-cpp/absl/base/libabsl_throw_delegate.a
services/chunk_storage/minecpp_chunk_storage: _deps/grpc-build/third_party/abseil-cpp/absl/base/libabsl_base.a
services/chunk_storage/minecpp_chunk_storage: _deps/grpc-build/third_party/abseil-cpp/absl/base/libabsl_raw_logging_internal.a
services/chunk_storage/minecpp_chunk_storage: _deps/grpc-build/third_party/abseil-cpp/absl/base/libabsl_log_severity.a
services/chunk_storage/minecpp_chunk_storage: _deps/grpc-build/third_party/abseil-cpp/absl/base/libabsl_spinlock_wait.a
services/chunk_storage/minecpp_chunk_storage: _deps/grpc-build/libaddress_sorting.a
services/chunk_storage/minecpp_chunk_storage: _deps/grpc-build/libupb.a
services/chunk_storage/minecpp_chunk_storage: services/chunk_storage/CMakeFiles/minecpp_chunk_storage.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/ego/projects/minecpp/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Linking CXX executable minecpp_chunk_storage"
	cd /home/ego/projects/minecpp/build/services/chunk_storage && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/minecpp_chunk_storage.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
services/chunk_storage/CMakeFiles/minecpp_chunk_storage.dir/build: services/chunk_storage/minecpp_chunk_storage

.PHONY : services/chunk_storage/CMakeFiles/minecpp_chunk_storage.dir/build

services/chunk_storage/CMakeFiles/minecpp_chunk_storage.dir/clean:
	cd /home/ego/projects/minecpp/build/services/chunk_storage && $(CMAKE_COMMAND) -P CMakeFiles/minecpp_chunk_storage.dir/cmake_clean.cmake
.PHONY : services/chunk_storage/CMakeFiles/minecpp_chunk_storage.dir/clean

services/chunk_storage/CMakeFiles/minecpp_chunk_storage.dir/depend:
	cd /home/ego/projects/minecpp/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ego/projects/minecpp /home/ego/projects/minecpp/services/chunk_storage /home/ego/projects/minecpp/build /home/ego/projects/minecpp/build/services/chunk_storage /home/ego/projects/minecpp/build/services/chunk_storage/CMakeFiles/minecpp_chunk_storage.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : services/chunk_storage/CMakeFiles/minecpp_chunk_storage.dir/depend

