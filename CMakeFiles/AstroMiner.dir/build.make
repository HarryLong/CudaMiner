# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/harry/cuda-workspace/GPGPU2-Assignment

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/harry/cuda-workspace/GPGPU2-Assignment

# Include any dependencies generated for this target.
include CMakeFiles/AstroMiner.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/AstroMiner.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/AstroMiner.dir/flags.make

CMakeFiles/AstroMiner.dir/AstroMiner.cpp.o: CMakeFiles/AstroMiner.dir/flags.make
CMakeFiles/AstroMiner.dir/AstroMiner.cpp.o: AstroMiner.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/harry/cuda-workspace/GPGPU2-Assignment/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/AstroMiner.dir/AstroMiner.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/AstroMiner.dir/AstroMiner.cpp.o -c /home/harry/cuda-workspace/GPGPU2-Assignment/AstroMiner.cpp

CMakeFiles/AstroMiner.dir/AstroMiner.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/AstroMiner.dir/AstroMiner.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/harry/cuda-workspace/GPGPU2-Assignment/AstroMiner.cpp > CMakeFiles/AstroMiner.dir/AstroMiner.cpp.i

CMakeFiles/AstroMiner.dir/AstroMiner.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/AstroMiner.dir/AstroMiner.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/harry/cuda-workspace/GPGPU2-Assignment/AstroMiner.cpp -o CMakeFiles/AstroMiner.dir/AstroMiner.cpp.s

CMakeFiles/AstroMiner.dir/AstroMiner.cpp.o.requires:
.PHONY : CMakeFiles/AstroMiner.dir/AstroMiner.cpp.o.requires

CMakeFiles/AstroMiner.dir/AstroMiner.cpp.o.provides: CMakeFiles/AstroMiner.dir/AstroMiner.cpp.o.requires
	$(MAKE) -f CMakeFiles/AstroMiner.dir/build.make CMakeFiles/AstroMiner.dir/AstroMiner.cpp.o.provides.build
.PHONY : CMakeFiles/AstroMiner.dir/AstroMiner.cpp.o.provides

CMakeFiles/AstroMiner.dir/AstroMiner.cpp.o.provides.build: CMakeFiles/AstroMiner.dir/AstroMiner.cpp.o

# Object files for target AstroMiner
AstroMiner_OBJECTS = \
"CMakeFiles/AstroMiner.dir/AstroMiner.cpp.o"

# External object files for target AstroMiner
AstroMiner_EXTERNAL_OBJECTS =

AstroMiner: CMakeFiles/AstroMiner.dir/AstroMiner.cpp.o
AstroMiner: CMakeFiles/AstroMiner.dir/build.make
AstroMiner: /usr/lib/x86_64-linux-gnu/libcudart.so
AstroMiner: cuda/libAstroCuda.a
AstroMiner: /usr/lib/x86_64-linux-gnu/libcudart.so
AstroMiner: CMakeFiles/AstroMiner.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable AstroMiner"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/AstroMiner.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/AstroMiner.dir/build: AstroMiner
.PHONY : CMakeFiles/AstroMiner.dir/build

CMakeFiles/AstroMiner.dir/requires: CMakeFiles/AstroMiner.dir/AstroMiner.cpp.o.requires
.PHONY : CMakeFiles/AstroMiner.dir/requires

CMakeFiles/AstroMiner.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/AstroMiner.dir/cmake_clean.cmake
.PHONY : CMakeFiles/AstroMiner.dir/clean

CMakeFiles/AstroMiner.dir/depend:
	cd /home/harry/cuda-workspace/GPGPU2-Assignment && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/harry/cuda-workspace/GPGPU2-Assignment /home/harry/cuda-workspace/GPGPU2-Assignment /home/harry/cuda-workspace/GPGPU2-Assignment /home/harry/cuda-workspace/GPGPU2-Assignment /home/harry/cuda-workspace/GPGPU2-Assignment/CMakeFiles/AstroMiner.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/AstroMiner.dir/depend
