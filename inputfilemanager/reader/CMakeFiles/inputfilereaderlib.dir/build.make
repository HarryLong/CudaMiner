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
CMAKE_SOURCE_DIR = /home/harry/cuda-workspace/GPGPU2-Assignment/inputfilemanager/reader

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/harry/cuda-workspace/GPGPU2-Assignment/inputfilemanager/reader

# Include any dependencies generated for this target.
include CMakeFiles/inputfilereaderlib.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/inputfilereaderlib.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/inputfilereaderlib.dir/flags.make

CMakeFiles/inputfilereaderlib.dir/home/harry/cuda-workspace/GPGPU2-Assignment/inputfilemanager/inputfilemanager.cpp.o: CMakeFiles/inputfilereaderlib.dir/flags.make
CMakeFiles/inputfilereaderlib.dir/home/harry/cuda-workspace/GPGPU2-Assignment/inputfilemanager/inputfilemanager.cpp.o: /home/harry/cuda-workspace/GPGPU2-Assignment/inputfilemanager/inputfilemanager.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/harry/cuda-workspace/GPGPU2-Assignment/inputfilemanager/reader/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/inputfilereaderlib.dir/home/harry/cuda-workspace/GPGPU2-Assignment/inputfilemanager/inputfilemanager.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/inputfilereaderlib.dir/home/harry/cuda-workspace/GPGPU2-Assignment/inputfilemanager/inputfilemanager.cpp.o -c /home/harry/cuda-workspace/GPGPU2-Assignment/inputfilemanager/inputfilemanager.cpp

CMakeFiles/inputfilereaderlib.dir/home/harry/cuda-workspace/GPGPU2-Assignment/inputfilemanager/inputfilemanager.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/inputfilereaderlib.dir/home/harry/cuda-workspace/GPGPU2-Assignment/inputfilemanager/inputfilemanager.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/harry/cuda-workspace/GPGPU2-Assignment/inputfilemanager/inputfilemanager.cpp > CMakeFiles/inputfilereaderlib.dir/home/harry/cuda-workspace/GPGPU2-Assignment/inputfilemanager/inputfilemanager.cpp.i

CMakeFiles/inputfilereaderlib.dir/home/harry/cuda-workspace/GPGPU2-Assignment/inputfilemanager/inputfilemanager.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/inputfilereaderlib.dir/home/harry/cuda-workspace/GPGPU2-Assignment/inputfilemanager/inputfilemanager.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/harry/cuda-workspace/GPGPU2-Assignment/inputfilemanager/inputfilemanager.cpp -o CMakeFiles/inputfilereaderlib.dir/home/harry/cuda-workspace/GPGPU2-Assignment/inputfilemanager/inputfilemanager.cpp.s

CMakeFiles/inputfilereaderlib.dir/home/harry/cuda-workspace/GPGPU2-Assignment/inputfilemanager/inputfilemanager.cpp.o.requires:
.PHONY : CMakeFiles/inputfilereaderlib.dir/home/harry/cuda-workspace/GPGPU2-Assignment/inputfilemanager/inputfilemanager.cpp.o.requires

CMakeFiles/inputfilereaderlib.dir/home/harry/cuda-workspace/GPGPU2-Assignment/inputfilemanager/inputfilemanager.cpp.o.provides: CMakeFiles/inputfilereaderlib.dir/home/harry/cuda-workspace/GPGPU2-Assignment/inputfilemanager/inputfilemanager.cpp.o.requires
	$(MAKE) -f CMakeFiles/inputfilereaderlib.dir/build.make CMakeFiles/inputfilereaderlib.dir/home/harry/cuda-workspace/GPGPU2-Assignment/inputfilemanager/inputfilemanager.cpp.o.provides.build
.PHONY : CMakeFiles/inputfilereaderlib.dir/home/harry/cuda-workspace/GPGPU2-Assignment/inputfilemanager/inputfilemanager.cpp.o.provides

CMakeFiles/inputfilereaderlib.dir/home/harry/cuda-workspace/GPGPU2-Assignment/inputfilemanager/inputfilemanager.cpp.o.provides.build: CMakeFiles/inputfilereaderlib.dir/home/harry/cuda-workspace/GPGPU2-Assignment/inputfilemanager/inputfilemanager.cpp.o

# Object files for target inputfilereaderlib
inputfilereaderlib_OBJECTS = \
"CMakeFiles/inputfilereaderlib.dir/home/harry/cuda-workspace/GPGPU2-Assignment/inputfilemanager/inputfilemanager.cpp.o"

# External object files for target inputfilereaderlib
inputfilereaderlib_EXTERNAL_OBJECTS =

libinputfilereaderlib.a: CMakeFiles/inputfilereaderlib.dir/home/harry/cuda-workspace/GPGPU2-Assignment/inputfilemanager/inputfilemanager.cpp.o
libinputfilereaderlib.a: CMakeFiles/inputfilereaderlib.dir/build.make
libinputfilereaderlib.a: CMakeFiles/inputfilereaderlib.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX static library libinputfilereaderlib.a"
	$(CMAKE_COMMAND) -P CMakeFiles/inputfilereaderlib.dir/cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/inputfilereaderlib.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/inputfilereaderlib.dir/build: libinputfilereaderlib.a
.PHONY : CMakeFiles/inputfilereaderlib.dir/build

CMakeFiles/inputfilereaderlib.dir/requires: CMakeFiles/inputfilereaderlib.dir/home/harry/cuda-workspace/GPGPU2-Assignment/inputfilemanager/inputfilemanager.cpp.o.requires
.PHONY : CMakeFiles/inputfilereaderlib.dir/requires

CMakeFiles/inputfilereaderlib.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/inputfilereaderlib.dir/cmake_clean.cmake
.PHONY : CMakeFiles/inputfilereaderlib.dir/clean

CMakeFiles/inputfilereaderlib.dir/depend:
	cd /home/harry/cuda-workspace/GPGPU2-Assignment/inputfilemanager/reader && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/harry/cuda-workspace/GPGPU2-Assignment/inputfilemanager/reader /home/harry/cuda-workspace/GPGPU2-Assignment/inputfilemanager/reader /home/harry/cuda-workspace/GPGPU2-Assignment/inputfilemanager/reader /home/harry/cuda-workspace/GPGPU2-Assignment/inputfilemanager/reader /home/harry/cuda-workspace/GPGPU2-Assignment/inputfilemanager/reader/CMakeFiles/inputfilereaderlib.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/inputfilereaderlib.dir/depend

