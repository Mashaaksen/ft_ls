# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.9

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
CMAKE_COMMAND = /Applications/CLion.app/Contents/bin/cmake/bin/cmake

# The command to remove a file.
RM = /Applications/CLion.app/Contents/bin/cmake/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/maksenov/CLionProjects/ft_ls

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/maksenov/CLionProjects/ft_ls/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/ft_ls.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/ft_ls.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/ft_ls.dir/flags.make

CMakeFiles/ft_ls.dir/main.c.o: CMakeFiles/ft_ls.dir/flags.make
CMakeFiles/ft_ls.dir/main.c.o: ../main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/maksenov/CLionProjects/ft_ls/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/ft_ls.dir/main.c.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/ft_ls.dir/main.c.o   -c /Users/maksenov/CLionProjects/ft_ls/main.c

CMakeFiles/ft_ls.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/ft_ls.dir/main.c.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/maksenov/CLionProjects/ft_ls/main.c > CMakeFiles/ft_ls.dir/main.c.i

CMakeFiles/ft_ls.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/ft_ls.dir/main.c.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/maksenov/CLionProjects/ft_ls/main.c -o CMakeFiles/ft_ls.dir/main.c.s

CMakeFiles/ft_ls.dir/main.c.o.requires:

.PHONY : CMakeFiles/ft_ls.dir/main.c.o.requires

CMakeFiles/ft_ls.dir/main.c.o.provides: CMakeFiles/ft_ls.dir/main.c.o.requires
	$(MAKE) -f CMakeFiles/ft_ls.dir/build.make CMakeFiles/ft_ls.dir/main.c.o.provides.build
.PHONY : CMakeFiles/ft_ls.dir/main.c.o.provides

CMakeFiles/ft_ls.dir/main.c.o.provides.build: CMakeFiles/ft_ls.dir/main.c.o


CMakeFiles/ft_ls.dir/ft_initialization.c.o: CMakeFiles/ft_ls.dir/flags.make
CMakeFiles/ft_ls.dir/ft_initialization.c.o: ../ft_initialization.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/maksenov/CLionProjects/ft_ls/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/ft_ls.dir/ft_initialization.c.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/ft_ls.dir/ft_initialization.c.o   -c /Users/maksenov/CLionProjects/ft_ls/ft_initialization.c

CMakeFiles/ft_ls.dir/ft_initialization.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/ft_ls.dir/ft_initialization.c.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/maksenov/CLionProjects/ft_ls/ft_initialization.c > CMakeFiles/ft_ls.dir/ft_initialization.c.i

CMakeFiles/ft_ls.dir/ft_initialization.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/ft_ls.dir/ft_initialization.c.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/maksenov/CLionProjects/ft_ls/ft_initialization.c -o CMakeFiles/ft_ls.dir/ft_initialization.c.s

CMakeFiles/ft_ls.dir/ft_initialization.c.o.requires:

.PHONY : CMakeFiles/ft_ls.dir/ft_initialization.c.o.requires

CMakeFiles/ft_ls.dir/ft_initialization.c.o.provides: CMakeFiles/ft_ls.dir/ft_initialization.c.o.requires
	$(MAKE) -f CMakeFiles/ft_ls.dir/build.make CMakeFiles/ft_ls.dir/ft_initialization.c.o.provides.build
.PHONY : CMakeFiles/ft_ls.dir/ft_initialization.c.o.provides

CMakeFiles/ft_ls.dir/ft_initialization.c.o.provides.build: CMakeFiles/ft_ls.dir/ft_initialization.c.o


CMakeFiles/ft_ls.dir/ft_error.c.o: CMakeFiles/ft_ls.dir/flags.make
CMakeFiles/ft_ls.dir/ft_error.c.o: ../ft_error.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/maksenov/CLionProjects/ft_ls/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/ft_ls.dir/ft_error.c.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/ft_ls.dir/ft_error.c.o   -c /Users/maksenov/CLionProjects/ft_ls/ft_error.c

CMakeFiles/ft_ls.dir/ft_error.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/ft_ls.dir/ft_error.c.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/maksenov/CLionProjects/ft_ls/ft_error.c > CMakeFiles/ft_ls.dir/ft_error.c.i

CMakeFiles/ft_ls.dir/ft_error.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/ft_ls.dir/ft_error.c.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/maksenov/CLionProjects/ft_ls/ft_error.c -o CMakeFiles/ft_ls.dir/ft_error.c.s

CMakeFiles/ft_ls.dir/ft_error.c.o.requires:

.PHONY : CMakeFiles/ft_ls.dir/ft_error.c.o.requires

CMakeFiles/ft_ls.dir/ft_error.c.o.provides: CMakeFiles/ft_ls.dir/ft_error.c.o.requires
	$(MAKE) -f CMakeFiles/ft_ls.dir/build.make CMakeFiles/ft_ls.dir/ft_error.c.o.provides.build
.PHONY : CMakeFiles/ft_ls.dir/ft_error.c.o.provides

CMakeFiles/ft_ls.dir/ft_error.c.o.provides.build: CMakeFiles/ft_ls.dir/ft_error.c.o


CMakeFiles/ft_ls.dir/ft_verification_param.c.o: CMakeFiles/ft_ls.dir/flags.make
CMakeFiles/ft_ls.dir/ft_verification_param.c.o: ../ft_verification_param.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/maksenov/CLionProjects/ft_ls/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object CMakeFiles/ft_ls.dir/ft_verification_param.c.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/ft_ls.dir/ft_verification_param.c.o   -c /Users/maksenov/CLionProjects/ft_ls/ft_verification_param.c

CMakeFiles/ft_ls.dir/ft_verification_param.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/ft_ls.dir/ft_verification_param.c.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/maksenov/CLionProjects/ft_ls/ft_verification_param.c > CMakeFiles/ft_ls.dir/ft_verification_param.c.i

CMakeFiles/ft_ls.dir/ft_verification_param.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/ft_ls.dir/ft_verification_param.c.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/maksenov/CLionProjects/ft_ls/ft_verification_param.c -o CMakeFiles/ft_ls.dir/ft_verification_param.c.s

CMakeFiles/ft_ls.dir/ft_verification_param.c.o.requires:

.PHONY : CMakeFiles/ft_ls.dir/ft_verification_param.c.o.requires

CMakeFiles/ft_ls.dir/ft_verification_param.c.o.provides: CMakeFiles/ft_ls.dir/ft_verification_param.c.o.requires
	$(MAKE) -f CMakeFiles/ft_ls.dir/build.make CMakeFiles/ft_ls.dir/ft_verification_param.c.o.provides.build
.PHONY : CMakeFiles/ft_ls.dir/ft_verification_param.c.o.provides

CMakeFiles/ft_ls.dir/ft_verification_param.c.o.provides.build: CMakeFiles/ft_ls.dir/ft_verification_param.c.o


CMakeFiles/ft_ls.dir/ft_insert_files.c.o: CMakeFiles/ft_ls.dir/flags.make
CMakeFiles/ft_ls.dir/ft_insert_files.c.o: ../ft_insert_files.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/maksenov/CLionProjects/ft_ls/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building C object CMakeFiles/ft_ls.dir/ft_insert_files.c.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/ft_ls.dir/ft_insert_files.c.o   -c /Users/maksenov/CLionProjects/ft_ls/ft_insert_files.c

CMakeFiles/ft_ls.dir/ft_insert_files.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/ft_ls.dir/ft_insert_files.c.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/maksenov/CLionProjects/ft_ls/ft_insert_files.c > CMakeFiles/ft_ls.dir/ft_insert_files.c.i

CMakeFiles/ft_ls.dir/ft_insert_files.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/ft_ls.dir/ft_insert_files.c.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/maksenov/CLionProjects/ft_ls/ft_insert_files.c -o CMakeFiles/ft_ls.dir/ft_insert_files.c.s

CMakeFiles/ft_ls.dir/ft_insert_files.c.o.requires:

.PHONY : CMakeFiles/ft_ls.dir/ft_insert_files.c.o.requires

CMakeFiles/ft_ls.dir/ft_insert_files.c.o.provides: CMakeFiles/ft_ls.dir/ft_insert_files.c.o.requires
	$(MAKE) -f CMakeFiles/ft_ls.dir/build.make CMakeFiles/ft_ls.dir/ft_insert_files.c.o.provides.build
.PHONY : CMakeFiles/ft_ls.dir/ft_insert_files.c.o.provides

CMakeFiles/ft_ls.dir/ft_insert_files.c.o.provides.build: CMakeFiles/ft_ls.dir/ft_insert_files.c.o


CMakeFiles/ft_ls.dir/ft_opendir.c.o: CMakeFiles/ft_ls.dir/flags.make
CMakeFiles/ft_ls.dir/ft_opendir.c.o: ../ft_opendir.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/maksenov/CLionProjects/ft_ls/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building C object CMakeFiles/ft_ls.dir/ft_opendir.c.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/ft_ls.dir/ft_opendir.c.o   -c /Users/maksenov/CLionProjects/ft_ls/ft_opendir.c

CMakeFiles/ft_ls.dir/ft_opendir.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/ft_ls.dir/ft_opendir.c.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/maksenov/CLionProjects/ft_ls/ft_opendir.c > CMakeFiles/ft_ls.dir/ft_opendir.c.i

CMakeFiles/ft_ls.dir/ft_opendir.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/ft_ls.dir/ft_opendir.c.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/maksenov/CLionProjects/ft_ls/ft_opendir.c -o CMakeFiles/ft_ls.dir/ft_opendir.c.s

CMakeFiles/ft_ls.dir/ft_opendir.c.o.requires:

.PHONY : CMakeFiles/ft_ls.dir/ft_opendir.c.o.requires

CMakeFiles/ft_ls.dir/ft_opendir.c.o.provides: CMakeFiles/ft_ls.dir/ft_opendir.c.o.requires
	$(MAKE) -f CMakeFiles/ft_ls.dir/build.make CMakeFiles/ft_ls.dir/ft_opendir.c.o.provides.build
.PHONY : CMakeFiles/ft_ls.dir/ft_opendir.c.o.provides

CMakeFiles/ft_ls.dir/ft_opendir.c.o.provides.build: CMakeFiles/ft_ls.dir/ft_opendir.c.o


# Object files for target ft_ls
ft_ls_OBJECTS = \
"CMakeFiles/ft_ls.dir/main.c.o" \
"CMakeFiles/ft_ls.dir/ft_initialization.c.o" \
"CMakeFiles/ft_ls.dir/ft_error.c.o" \
"CMakeFiles/ft_ls.dir/ft_verification_param.c.o" \
"CMakeFiles/ft_ls.dir/ft_insert_files.c.o" \
"CMakeFiles/ft_ls.dir/ft_opendir.c.o"

# External object files for target ft_ls
ft_ls_EXTERNAL_OBJECTS =

ft_ls: CMakeFiles/ft_ls.dir/main.c.o
ft_ls: CMakeFiles/ft_ls.dir/ft_initialization.c.o
ft_ls: CMakeFiles/ft_ls.dir/ft_error.c.o
ft_ls: CMakeFiles/ft_ls.dir/ft_verification_param.c.o
ft_ls: CMakeFiles/ft_ls.dir/ft_insert_files.c.o
ft_ls: CMakeFiles/ft_ls.dir/ft_opendir.c.o
ft_ls: CMakeFiles/ft_ls.dir/build.make
ft_ls: CMakeFiles/ft_ls.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/maksenov/CLionProjects/ft_ls/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Linking C executable ft_ls"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/ft_ls.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/ft_ls.dir/build: ft_ls

.PHONY : CMakeFiles/ft_ls.dir/build

CMakeFiles/ft_ls.dir/requires: CMakeFiles/ft_ls.dir/main.c.o.requires
CMakeFiles/ft_ls.dir/requires: CMakeFiles/ft_ls.dir/ft_initialization.c.o.requires
CMakeFiles/ft_ls.dir/requires: CMakeFiles/ft_ls.dir/ft_error.c.o.requires
CMakeFiles/ft_ls.dir/requires: CMakeFiles/ft_ls.dir/ft_verification_param.c.o.requires
CMakeFiles/ft_ls.dir/requires: CMakeFiles/ft_ls.dir/ft_insert_files.c.o.requires
CMakeFiles/ft_ls.dir/requires: CMakeFiles/ft_ls.dir/ft_opendir.c.o.requires

.PHONY : CMakeFiles/ft_ls.dir/requires

CMakeFiles/ft_ls.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/ft_ls.dir/cmake_clean.cmake
.PHONY : CMakeFiles/ft_ls.dir/clean

CMakeFiles/ft_ls.dir/depend:
	cd /Users/maksenov/CLionProjects/ft_ls/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/maksenov/CLionProjects/ft_ls /Users/maksenov/CLionProjects/ft_ls /Users/maksenov/CLionProjects/ft_ls/cmake-build-debug /Users/maksenov/CLionProjects/ft_ls/cmake-build-debug /Users/maksenov/CLionProjects/ft_ls/cmake-build-debug/CMakeFiles/ft_ls.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/ft_ls.dir/depend

