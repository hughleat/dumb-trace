# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.21

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
CMAKE_COMMAND = /usr/local/Cellar/cmake/3.21.1/bin/cmake

# The command to remove a file.
RM = /usr/local/Cellar/cmake/3.21.1/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/hleather/Documents/code/dumb-trace

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/hleather/Documents/code/dumb-trace/build

# Include any dependencies generated for this target.
include CMakeFiles/dumb_instrument.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/dumb_instrument.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/dumb_instrument.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/dumb_instrument.dir/flags.make

CMakeFiles/dumb_instrument.dir/src/dumb_instrument.cpp.o: CMakeFiles/dumb_instrument.dir/flags.make
CMakeFiles/dumb_instrument.dir/src/dumb_instrument.cpp.o: ../src/dumb_instrument.cpp
CMakeFiles/dumb_instrument.dir/src/dumb_instrument.cpp.o: CMakeFiles/dumb_instrument.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/hleather/Documents/code/dumb-trace/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/dumb_instrument.dir/src/dumb_instrument.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/dumb_instrument.dir/src/dumb_instrument.cpp.o -MF CMakeFiles/dumb_instrument.dir/src/dumb_instrument.cpp.o.d -o CMakeFiles/dumb_instrument.dir/src/dumb_instrument.cpp.o -c /Users/hleather/Documents/code/dumb-trace/src/dumb_instrument.cpp

CMakeFiles/dumb_instrument.dir/src/dumb_instrument.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/dumb_instrument.dir/src/dumb_instrument.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/hleather/Documents/code/dumb-trace/src/dumb_instrument.cpp > CMakeFiles/dumb_instrument.dir/src/dumb_instrument.cpp.i

CMakeFiles/dumb_instrument.dir/src/dumb_instrument.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/dumb_instrument.dir/src/dumb_instrument.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/hleather/Documents/code/dumb-trace/src/dumb_instrument.cpp -o CMakeFiles/dumb_instrument.dir/src/dumb_instrument.cpp.s

# Object files for target dumb_instrument
dumb_instrument_OBJECTS = \
"CMakeFiles/dumb_instrument.dir/src/dumb_instrument.cpp.o"

# External object files for target dumb_instrument
dumb_instrument_EXTERNAL_OBJECTS =

dumb_instrument: CMakeFiles/dumb_instrument.dir/src/dumb_instrument.cpp.o
dumb_instrument: CMakeFiles/dumb_instrument.dir/build.make
dumb_instrument: /Users/hleather/opt/miniconda3/envs/gpt4code/lib/libLLVMSupport.a
dumb_instrument: /Users/hleather/opt/miniconda3/envs/gpt4code/lib/libLLVMCore.a
dumb_instrument: /Users/hleather/opt/miniconda3/envs/gpt4code/lib/libLLVMIRReader.a
dumb_instrument: /Users/hleather/opt/miniconda3/envs/gpt4code/lib/libLLVMAsmParser.a
dumb_instrument: /Users/hleather/opt/miniconda3/envs/gpt4code/lib/libLLVMBitReader.a
dumb_instrument: /Users/hleather/opt/miniconda3/envs/gpt4code/lib/libLLVMCore.a
dumb_instrument: /Users/hleather/opt/miniconda3/envs/gpt4code/lib/libLLVMBinaryFormat.a
dumb_instrument: /Users/hleather/opt/miniconda3/envs/gpt4code/lib/libLLVMRemarks.a
dumb_instrument: /Users/hleather/opt/miniconda3/envs/gpt4code/lib/libLLVMBitstreamReader.a
dumb_instrument: /Users/hleather/opt/miniconda3/envs/gpt4code/lib/libLLVMSupport.a
dumb_instrument: /Library/Developer/CommandLineTools/SDKs/MacOSX11.0.sdk/usr/lib/libz.tbd
dumb_instrument: /Users/hleather/opt/miniconda3/envs/gpt4code/lib/libLLVMDemangle.a
dumb_instrument: CMakeFiles/dumb_instrument.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/hleather/Documents/code/dumb-trace/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable dumb_instrument"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/dumb_instrument.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/dumb_instrument.dir/build: dumb_instrument
.PHONY : CMakeFiles/dumb_instrument.dir/build

CMakeFiles/dumb_instrument.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/dumb_instrument.dir/cmake_clean.cmake
.PHONY : CMakeFiles/dumb_instrument.dir/clean

CMakeFiles/dumb_instrument.dir/depend:
	cd /Users/hleather/Documents/code/dumb-trace/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/hleather/Documents/code/dumb-trace /Users/hleather/Documents/code/dumb-trace /Users/hleather/Documents/code/dumb-trace/build /Users/hleather/Documents/code/dumb-trace/build /Users/hleather/Documents/code/dumb-trace/build/CMakeFiles/dumb_instrument.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/dumb_instrument.dir/depend

