# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.18

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
CMAKE_SOURCE_DIR = /home/hongdayu/single_source

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/hongdayu/single_source/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/5g_ssrc.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/5g_ssrc.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/5g_ssrc.dir/flags.make

CMakeFiles/5g_ssrc.dir/main.cpp.o: CMakeFiles/5g_ssrc.dir/flags.make
CMakeFiles/5g_ssrc.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/hongdayu/single_source/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/5g_ssrc.dir/main.cpp.o"
	/usr/bin/arm-linux-gnueabi-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/5g_ssrc.dir/main.cpp.o -c /home/hongdayu/single_source/main.cpp

CMakeFiles/5g_ssrc.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/5g_ssrc.dir/main.cpp.i"
	/usr/bin/arm-linux-gnueabi-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/hongdayu/single_source/main.cpp > CMakeFiles/5g_ssrc.dir/main.cpp.i

CMakeFiles/5g_ssrc.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/5g_ssrc.dir/main.cpp.s"
	/usr/bin/arm-linux-gnueabi-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/hongdayu/single_source/main.cpp -o CMakeFiles/5g_ssrc.dir/main.cpp.s

CMakeFiles/5g_ssrc.dir/libftp/ftplib.cpp.o: CMakeFiles/5g_ssrc.dir/flags.make
CMakeFiles/5g_ssrc.dir/libftp/ftplib.cpp.o: ../libftp/ftplib.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/hongdayu/single_source/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/5g_ssrc.dir/libftp/ftplib.cpp.o"
	/usr/bin/arm-linux-gnueabi-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/5g_ssrc.dir/libftp/ftplib.cpp.o -c /home/hongdayu/single_source/libftp/ftplib.cpp

CMakeFiles/5g_ssrc.dir/libftp/ftplib.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/5g_ssrc.dir/libftp/ftplib.cpp.i"
	/usr/bin/arm-linux-gnueabi-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/hongdayu/single_source/libftp/ftplib.cpp > CMakeFiles/5g_ssrc.dir/libftp/ftplib.cpp.i

CMakeFiles/5g_ssrc.dir/libftp/ftplib.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/5g_ssrc.dir/libftp/ftplib.cpp.s"
	/usr/bin/arm-linux-gnueabi-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/hongdayu/single_source/libftp/ftplib.cpp -o CMakeFiles/5g_ssrc.dir/libftp/ftplib.cpp.s

CMakeFiles/5g_ssrc.dir/zynq7035.cpp.o: CMakeFiles/5g_ssrc.dir/flags.make
CMakeFiles/5g_ssrc.dir/zynq7035.cpp.o: ../zynq7035.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/hongdayu/single_source/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/5g_ssrc.dir/zynq7035.cpp.o"
	/usr/bin/arm-linux-gnueabi-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/5g_ssrc.dir/zynq7035.cpp.o -c /home/hongdayu/single_source/zynq7035.cpp

CMakeFiles/5g_ssrc.dir/zynq7035.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/5g_ssrc.dir/zynq7035.cpp.i"
	/usr/bin/arm-linux-gnueabi-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/hongdayu/single_source/zynq7035.cpp > CMakeFiles/5g_ssrc.dir/zynq7035.cpp.i

CMakeFiles/5g_ssrc.dir/zynq7035.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/5g_ssrc.dir/zynq7035.cpp.s"
	/usr/bin/arm-linux-gnueabi-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/hongdayu/single_source/zynq7035.cpp -o CMakeFiles/5g_ssrc.dir/zynq7035.cpp.s

CMakeFiles/5g_ssrc.dir/ftp.cpp.o: CMakeFiles/5g_ssrc.dir/flags.make
CMakeFiles/5g_ssrc.dir/ftp.cpp.o: ../ftp.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/hongdayu/single_source/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/5g_ssrc.dir/ftp.cpp.o"
	/usr/bin/arm-linux-gnueabi-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/5g_ssrc.dir/ftp.cpp.o -c /home/hongdayu/single_source/ftp.cpp

CMakeFiles/5g_ssrc.dir/ftp.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/5g_ssrc.dir/ftp.cpp.i"
	/usr/bin/arm-linux-gnueabi-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/hongdayu/single_source/ftp.cpp > CMakeFiles/5g_ssrc.dir/ftp.cpp.i

CMakeFiles/5g_ssrc.dir/ftp.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/5g_ssrc.dir/ftp.cpp.s"
	/usr/bin/arm-linux-gnueabi-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/hongdayu/single_source/ftp.cpp -o CMakeFiles/5g_ssrc.dir/ftp.cpp.s

# Object files for target 5g_ssrc
5g_ssrc_OBJECTS = \
"CMakeFiles/5g_ssrc.dir/main.cpp.o" \
"CMakeFiles/5g_ssrc.dir/libftp/ftplib.cpp.o" \
"CMakeFiles/5g_ssrc.dir/zynq7035.cpp.o" \
"CMakeFiles/5g_ssrc.dir/ftp.cpp.o"

# External object files for target 5g_ssrc
5g_ssrc_EXTERNAL_OBJECTS =

5g_ssrc: CMakeFiles/5g_ssrc.dir/main.cpp.o
5g_ssrc: CMakeFiles/5g_ssrc.dir/libftp/ftplib.cpp.o
5g_ssrc: CMakeFiles/5g_ssrc.dir/zynq7035.cpp.o
5g_ssrc: CMakeFiles/5g_ssrc.dir/ftp.cpp.o
5g_ssrc: CMakeFiles/5g_ssrc.dir/build.make
5g_ssrc: CMakeFiles/5g_ssrc.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/hongdayu/single_source/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Linking CXX executable 5g_ssrc"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/5g_ssrc.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/5g_ssrc.dir/build: 5g_ssrc

.PHONY : CMakeFiles/5g_ssrc.dir/build

CMakeFiles/5g_ssrc.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/5g_ssrc.dir/cmake_clean.cmake
.PHONY : CMakeFiles/5g_ssrc.dir/clean

CMakeFiles/5g_ssrc.dir/depend:
	cd /home/hongdayu/single_source/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/hongdayu/single_source /home/hongdayu/single_source /home/hongdayu/single_source/cmake-build-debug /home/hongdayu/single_source/cmake-build-debug /home/hongdayu/single_source/cmake-build-debug/CMakeFiles/5g_ssrc.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/5g_ssrc.dir/depend

