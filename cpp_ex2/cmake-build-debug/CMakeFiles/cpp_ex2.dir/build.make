# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.12

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
CMAKE_COMMAND = /usr/local/APP/jetbrains/clion/2018.2.1/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /usr/local/APP/jetbrains/clion/2018.2.1/bin/cmake/linux/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /cs/usr/roeyby/CLionProjects/cpp_ex2

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /cs/usr/roeyby/CLionProjects/cpp_ex2/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/cpp_ex2.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/cpp_ex2.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/cpp_ex2.dir/flags.make

CMakeFiles/cpp_ex2.dir/Fractal.cpp.o: CMakeFiles/cpp_ex2.dir/flags.make
CMakeFiles/cpp_ex2.dir/Fractal.cpp.o: ../Fractal.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/cs/usr/roeyby/CLionProjects/cpp_ex2/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/cpp_ex2.dir/Fractal.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/cpp_ex2.dir/Fractal.cpp.o -c /cs/usr/roeyby/CLionProjects/cpp_ex2/Fractal.cpp

CMakeFiles/cpp_ex2.dir/Fractal.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/cpp_ex2.dir/Fractal.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /cs/usr/roeyby/CLionProjects/cpp_ex2/Fractal.cpp > CMakeFiles/cpp_ex2.dir/Fractal.cpp.i

CMakeFiles/cpp_ex2.dir/Fractal.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/cpp_ex2.dir/Fractal.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /cs/usr/roeyby/CLionProjects/cpp_ex2/Fractal.cpp -o CMakeFiles/cpp_ex2.dir/Fractal.cpp.s

CMakeFiles/cpp_ex2.dir/FractalDrawer.cpp.o: CMakeFiles/cpp_ex2.dir/flags.make
CMakeFiles/cpp_ex2.dir/FractalDrawer.cpp.o: ../FractalDrawer.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/cs/usr/roeyby/CLionProjects/cpp_ex2/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/cpp_ex2.dir/FractalDrawer.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/cpp_ex2.dir/FractalDrawer.cpp.o -c /cs/usr/roeyby/CLionProjects/cpp_ex2/FractalDrawer.cpp

CMakeFiles/cpp_ex2.dir/FractalDrawer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/cpp_ex2.dir/FractalDrawer.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /cs/usr/roeyby/CLionProjects/cpp_ex2/FractalDrawer.cpp > CMakeFiles/cpp_ex2.dir/FractalDrawer.cpp.i

CMakeFiles/cpp_ex2.dir/FractalDrawer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/cpp_ex2.dir/FractalDrawer.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /cs/usr/roeyby/CLionProjects/cpp_ex2/FractalDrawer.cpp -o CMakeFiles/cpp_ex2.dir/FractalDrawer.cpp.s

# Object files for target cpp_ex2
cpp_ex2_OBJECTS = \
"CMakeFiles/cpp_ex2.dir/Fractal.cpp.o" \
"CMakeFiles/cpp_ex2.dir/FractalDrawer.cpp.o"

# External object files for target cpp_ex2
cpp_ex2_EXTERNAL_OBJECTS =

cpp_ex2: CMakeFiles/cpp_ex2.dir/Fractal.cpp.o
cpp_ex2: CMakeFiles/cpp_ex2.dir/FractalDrawer.cpp.o
cpp_ex2: CMakeFiles/cpp_ex2.dir/build.make
cpp_ex2: CMakeFiles/cpp_ex2.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/cs/usr/roeyby/CLionProjects/cpp_ex2/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable cpp_ex2"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/cpp_ex2.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/cpp_ex2.dir/build: cpp_ex2

.PHONY : CMakeFiles/cpp_ex2.dir/build

CMakeFiles/cpp_ex2.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/cpp_ex2.dir/cmake_clean.cmake
.PHONY : CMakeFiles/cpp_ex2.dir/clean

CMakeFiles/cpp_ex2.dir/depend:
	cd /cs/usr/roeyby/CLionProjects/cpp_ex2/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /cs/usr/roeyby/CLionProjects/cpp_ex2 /cs/usr/roeyby/CLionProjects/cpp_ex2 /cs/usr/roeyby/CLionProjects/cpp_ex2/cmake-build-debug /cs/usr/roeyby/CLionProjects/cpp_ex2/cmake-build-debug /cs/usr/roeyby/CLionProjects/cpp_ex2/cmake-build-debug/CMakeFiles/cpp_ex2.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/cpp_ex2.dir/depend

