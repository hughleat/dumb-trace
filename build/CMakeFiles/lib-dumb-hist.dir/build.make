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
include CMakeFiles/lib-dumb-hist.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/lib-dumb-hist.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/lib-dumb-hist.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/lib-dumb-hist.dir/flags.make

CMakeFiles/lib-dumb-hist.dir/src/lib-dumb-hist.cpp.o: CMakeFiles/lib-dumb-hist.dir/flags.make
CMakeFiles/lib-dumb-hist.dir/src/lib-dumb-hist.cpp.o: ../src/lib-dumb-hist.cpp
CMakeFiles/lib-dumb-hist.dir/src/lib-dumb-hist.cpp.o: CMakeFiles/lib-dumb-hist.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/hleather/Documents/code/dumb-trace/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/lib-dumb-hist.dir/src/lib-dumb-hist.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/lib-dumb-hist.dir/src/lib-dumb-hist.cpp.o -MF CMakeFiles/lib-dumb-hist.dir/src/lib-dumb-hist.cpp.o.d -o CMakeFiles/lib-dumb-hist.dir/src/lib-dumb-hist.cpp.o -c /Users/hleather/Documents/code/dumb-trace/src/lib-dumb-hist.cpp

CMakeFiles/lib-dumb-hist.dir/src/lib-dumb-hist.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/lib-dumb-hist.dir/src/lib-dumb-hist.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/hleather/Documents/code/dumb-trace/src/lib-dumb-hist.cpp > CMakeFiles/lib-dumb-hist.dir/src/lib-dumb-hist.cpp.i

CMakeFiles/lib-dumb-hist.dir/src/lib-dumb-hist.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/lib-dumb-hist.dir/src/lib-dumb-hist.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/hleather/Documents/code/dumb-trace/src/lib-dumb-hist.cpp -o CMakeFiles/lib-dumb-hist.dir/src/lib-dumb-hist.cpp.s

# Object files for target lib-dumb-hist
lib__dumb__hist_OBJECTS = \
"CMakeFiles/lib-dumb-hist.dir/src/lib-dumb-hist.cpp.o"

# External object files for target lib-dumb-hist
lib__dumb__hist_EXTERNAL_OBJECTS =

liblib-dumb-hist.a: CMakeFiles/lib-dumb-hist.dir/src/lib-dumb-hist.cpp.o
liblib-dumb-hist.a: CMakeFiles/lib-dumb-hist.dir/build.make
liblib-dumb-hist.a: CMakeFiles/lib-dumb-hist.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/hleather/Documents/code/dumb-trace/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library liblib-dumb-hist.a"
	$(CMAKE_COMMAND) -P CMakeFiles/lib-dumb-hist.dir/cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/lib-dumb-hist.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/lib-dumb-hist.dir/build: liblib-dumb-hist.a
.PHONY : CMakeFiles/lib-dumb-hist.dir/build

CMakeFiles/lib-dumb-hist.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/lib-dumb-hist.dir/cmake_clean.cmake
.PHONY : CMakeFiles/lib-dumb-hist.dir/clean

CMakeFiles/lib-dumb-hist.dir/depend:
	cd /Users/hleather/Documents/code/dumb-trace/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/hleather/Documents/code/dumb-trace /Users/hleather/Documents/code/dumb-trace /Users/hleather/Documents/code/dumb-trace/build /Users/hleather/Documents/code/dumb-trace/build /Users/hleather/Documents/code/dumb-trace/build/CMakeFiles/lib-dumb-hist.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/lib-dumb-hist.dir/depend
