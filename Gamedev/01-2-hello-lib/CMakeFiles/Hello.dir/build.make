# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.13

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


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
CMAKE_COMMAND = /usr/local/bin/cmake

# The command to remove a file.
RM = /usr/local/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/yura/snap/Gamedev/01-2-hello-lib

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/yura/snap/Gamedev/01-2-hello-lib

# Include any dependencies generated for this target.
include CMakeFiles/Hello.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Hello.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Hello.dir/flags.make

CMakeFiles/Hello.dir/src/hello.cpp.o: CMakeFiles/Hello.dir/flags.make
CMakeFiles/Hello.dir/src/hello.cpp.o: src/hello.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/yura/snap/Gamedev/01-2-hello-lib/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Hello.dir/src/hello.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Hello.dir/src/hello.cpp.o -c /home/yura/snap/Gamedev/01-2-hello-lib/src/hello.cpp

CMakeFiles/Hello.dir/src/hello.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Hello.dir/src/hello.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/yura/snap/Gamedev/01-2-hello-lib/src/hello.cpp > CMakeFiles/Hello.dir/src/hello.cpp.i

CMakeFiles/Hello.dir/src/hello.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Hello.dir/src/hello.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/yura/snap/Gamedev/01-2-hello-lib/src/hello.cpp -o CMakeFiles/Hello.dir/src/hello.cpp.s

# Object files for target Hello
Hello_OBJECTS = \
"CMakeFiles/Hello.dir/src/hello.cpp.o"

# External object files for target Hello
Hello_EXTERNAL_OBJECTS =

libHello.a: CMakeFiles/Hello.dir/src/hello.cpp.o
libHello.a: CMakeFiles/Hello.dir/build.make
libHello.a: CMakeFiles/Hello.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/yura/snap/Gamedev/01-2-hello-lib/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libHello.a"
	$(CMAKE_COMMAND) -P CMakeFiles/Hello.dir/cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Hello.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Hello.dir/build: libHello.a

.PHONY : CMakeFiles/Hello.dir/build

CMakeFiles/Hello.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Hello.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Hello.dir/clean

CMakeFiles/Hello.dir/depend:
	cd /home/yura/snap/Gamedev/01-2-hello-lib && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/yura/snap/Gamedev/01-2-hello-lib /home/yura/snap/Gamedev/01-2-hello-lib /home/yura/snap/Gamedev/01-2-hello-lib /home/yura/snap/Gamedev/01-2-hello-lib /home/yura/snap/Gamedev/01-2-hello-lib/CMakeFiles/Hello.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Hello.dir/depend

