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
CMAKE_SOURCE_DIR = /home/harry/workspaces/cuda-workspace/GPGPU2-Assignment/inputfilemanager/writer

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/harry/workspaces/cuda-workspace/GPGPU2-Assignment/inputfilemanager/writer-build

# Include any dependencies generated for this target.
include CMakeFiles/inputFileWriter.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/inputFileWriter.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/inputFileWriter.dir/flags.make

CMakeFiles/inputFileWriter.dir/inputfilewriter.cpp.o: CMakeFiles/inputFileWriter.dir/flags.make
CMakeFiles/inputFileWriter.dir/inputfilewriter.cpp.o: /home/harry/workspaces/cuda-workspace/GPGPU2-Assignment/inputfilemanager/writer/inputfilewriter.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/harry/workspaces/cuda-workspace/GPGPU2-Assignment/inputfilemanager/writer-build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/inputFileWriter.dir/inputfilewriter.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/inputFileWriter.dir/inputfilewriter.cpp.o -c /home/harry/workspaces/cuda-workspace/GPGPU2-Assignment/inputfilemanager/writer/inputfilewriter.cpp

CMakeFiles/inputFileWriter.dir/inputfilewriter.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/inputFileWriter.dir/inputfilewriter.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/harry/workspaces/cuda-workspace/GPGPU2-Assignment/inputfilemanager/writer/inputfilewriter.cpp > CMakeFiles/inputFileWriter.dir/inputfilewriter.cpp.i

CMakeFiles/inputFileWriter.dir/inputfilewriter.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/inputFileWriter.dir/inputfilewriter.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/harry/workspaces/cuda-workspace/GPGPU2-Assignment/inputfilemanager/writer/inputfilewriter.cpp -o CMakeFiles/inputFileWriter.dir/inputfilewriter.cpp.s

CMakeFiles/inputFileWriter.dir/inputfilewriter.cpp.o.requires:
.PHONY : CMakeFiles/inputFileWriter.dir/inputfilewriter.cpp.o.requires

CMakeFiles/inputFileWriter.dir/inputfilewriter.cpp.o.provides: CMakeFiles/inputFileWriter.dir/inputfilewriter.cpp.o.requires
	$(MAKE) -f CMakeFiles/inputFileWriter.dir/build.make CMakeFiles/inputFileWriter.dir/inputfilewriter.cpp.o.provides.build
.PHONY : CMakeFiles/inputFileWriter.dir/inputfilewriter.cpp.o.provides

CMakeFiles/inputFileWriter.dir/inputfilewriter.cpp.o.provides.build: CMakeFiles/inputFileWriter.dir/inputfilewriter.cpp.o

CMakeFiles/inputFileWriter.dir/home/harry/workspaces/cuda-workspace/GPGPU2-Assignment/inputfilemanager/inputfilemanager.cpp.o: CMakeFiles/inputFileWriter.dir/flags.make
CMakeFiles/inputFileWriter.dir/home/harry/workspaces/cuda-workspace/GPGPU2-Assignment/inputfilemanager/inputfilemanager.cpp.o: /home/harry/workspaces/cuda-workspace/GPGPU2-Assignment/inputfilemanager/inputfilemanager.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/harry/workspaces/cuda-workspace/GPGPU2-Assignment/inputfilemanager/writer-build/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/inputFileWriter.dir/home/harry/workspaces/cuda-workspace/GPGPU2-Assignment/inputfilemanager/inputfilemanager.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/inputFileWriter.dir/home/harry/workspaces/cuda-workspace/GPGPU2-Assignment/inputfilemanager/inputfilemanager.cpp.o -c /home/harry/workspaces/cuda-workspace/GPGPU2-Assignment/inputfilemanager/inputfilemanager.cpp

CMakeFiles/inputFileWriter.dir/home/harry/workspaces/cuda-workspace/GPGPU2-Assignment/inputfilemanager/inputfilemanager.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/inputFileWriter.dir/home/harry/workspaces/cuda-workspace/GPGPU2-Assignment/inputfilemanager/inputfilemanager.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/harry/workspaces/cuda-workspace/GPGPU2-Assignment/inputfilemanager/inputfilemanager.cpp > CMakeFiles/inputFileWriter.dir/home/harry/workspaces/cuda-workspace/GPGPU2-Assignment/inputfilemanager/inputfilemanager.cpp.i

CMakeFiles/inputFileWriter.dir/home/harry/workspaces/cuda-workspace/GPGPU2-Assignment/inputfilemanager/inputfilemanager.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/inputFileWriter.dir/home/harry/workspaces/cuda-workspace/GPGPU2-Assignment/inputfilemanager/inputfilemanager.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/harry/workspaces/cuda-workspace/GPGPU2-Assignment/inputfilemanager/inputfilemanager.cpp -o CMakeFiles/inputFileWriter.dir/home/harry/workspaces/cuda-workspace/GPGPU2-Assignment/inputfilemanager/inputfilemanager.cpp.s

CMakeFiles/inputFileWriter.dir/home/harry/workspaces/cuda-workspace/GPGPU2-Assignment/inputfilemanager/inputfilemanager.cpp.o.requires:
.PHONY : CMakeFiles/inputFileWriter.dir/home/harry/workspaces/cuda-workspace/GPGPU2-Assignment/inputfilemanager/inputfilemanager.cpp.o.requires

CMakeFiles/inputFileWriter.dir/home/harry/workspaces/cuda-workspace/GPGPU2-Assignment/inputfilemanager/inputfilemanager.cpp.o.provides: CMakeFiles/inputFileWriter.dir/home/harry/workspaces/cuda-workspace/GPGPU2-Assignment/inputfilemanager/inputfilemanager.cpp.o.requires
	$(MAKE) -f CMakeFiles/inputFileWriter.dir/build.make CMakeFiles/inputFileWriter.dir/home/harry/workspaces/cuda-workspace/GPGPU2-Assignment/inputfilemanager/inputfilemanager.cpp.o.provides.build
.PHONY : CMakeFiles/inputFileWriter.dir/home/harry/workspaces/cuda-workspace/GPGPU2-Assignment/inputfilemanager/inputfilemanager.cpp.o.provides

CMakeFiles/inputFileWriter.dir/home/harry/workspaces/cuda-workspace/GPGPU2-Assignment/inputfilemanager/inputfilemanager.cpp.o.provides.build: CMakeFiles/inputFileWriter.dir/home/harry/workspaces/cuda-workspace/GPGPU2-Assignment/inputfilemanager/inputfilemanager.cpp.o

# Object files for target inputFileWriter
inputFileWriter_OBJECTS = \
"CMakeFiles/inputFileWriter.dir/inputfilewriter.cpp.o" \
"CMakeFiles/inputFileWriter.dir/home/harry/workspaces/cuda-workspace/GPGPU2-Assignment/inputfilemanager/inputfilemanager.cpp.o"

# External object files for target inputFileWriter
inputFileWriter_EXTERNAL_OBJECTS =

inputFileWriter: CMakeFiles/inputFileWriter.dir/inputfilewriter.cpp.o
inputFileWriter: CMakeFiles/inputFileWriter.dir/home/harry/workspaces/cuda-workspace/GPGPU2-Assignment/inputfilemanager/inputfilemanager.cpp.o
inputFileWriter: CMakeFiles/inputFileWriter.dir/build.make
inputFileWriter: CMakeFiles/inputFileWriter.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable inputFileWriter"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/inputFileWriter.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/inputFileWriter.dir/build: inputFileWriter
.PHONY : CMakeFiles/inputFileWriter.dir/build

CMakeFiles/inputFileWriter.dir/requires: CMakeFiles/inputFileWriter.dir/inputfilewriter.cpp.o.requires
CMakeFiles/inputFileWriter.dir/requires: CMakeFiles/inputFileWriter.dir/home/harry/workspaces/cuda-workspace/GPGPU2-Assignment/inputfilemanager/inputfilemanager.cpp.o.requires
.PHONY : CMakeFiles/inputFileWriter.dir/requires

CMakeFiles/inputFileWriter.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/inputFileWriter.dir/cmake_clean.cmake
.PHONY : CMakeFiles/inputFileWriter.dir/clean

CMakeFiles/inputFileWriter.dir/depend:
	cd /home/harry/workspaces/cuda-workspace/GPGPU2-Assignment/inputfilemanager/writer-build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/harry/workspaces/cuda-workspace/GPGPU2-Assignment/inputfilemanager/writer /home/harry/workspaces/cuda-workspace/GPGPU2-Assignment/inputfilemanager/writer /home/harry/workspaces/cuda-workspace/GPGPU2-Assignment/inputfilemanager/writer-build /home/harry/workspaces/cuda-workspace/GPGPU2-Assignment/inputfilemanager/writer-build /home/harry/workspaces/cuda-workspace/GPGPU2-Assignment/inputfilemanager/writer-build/CMakeFiles/inputFileWriter.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/inputFileWriter.dir/depend

