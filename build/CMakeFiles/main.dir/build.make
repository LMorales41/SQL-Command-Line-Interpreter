# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.27

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
CMAKE_COMMAND = /usr/local/Cellar/cmake/3.27.4/bin/cmake

# The command to remove a file.
RM = /usr/local/Cellar/cmake/3.27.4/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/lulu/Desktop/cs008/FINAL/99_99_final_project-lmorales-41

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/lulu/Desktop/cs008/FINAL/99_99_final_project-lmorales-41/build

# Include any dependencies generated for this target.
include CMakeFiles/main.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/main.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/main.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/main.dir/flags.make

CMakeFiles/main.dir/main.cpp.o: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/main.cpp.o: /Users/lulu/Desktop/cs008/FINAL/99_99_final_project-lmorales-41/main.cpp
CMakeFiles/main.dir/main.cpp.o: CMakeFiles/main.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/lulu/Desktop/cs008/FINAL/99_99_final_project-lmorales-41/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/main.dir/main.cpp.o"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/main.dir/main.cpp.o -MF CMakeFiles/main.dir/main.cpp.o.d -o CMakeFiles/main.dir/main.cpp.o -c /Users/lulu/Desktop/cs008/FINAL/99_99_final_project-lmorales-41/main.cpp

CMakeFiles/main.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/main.dir/main.cpp.i"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/lulu/Desktop/cs008/FINAL/99_99_final_project-lmorales-41/main.cpp > CMakeFiles/main.dir/main.cpp.i

CMakeFiles/main.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/main.dir/main.cpp.s"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/lulu/Desktop/cs008/FINAL/99_99_final_project-lmorales-41/main.cpp -o CMakeFiles/main.dir/main.cpp.s

CMakeFiles/main.dir/includes/binary_files/file_record.cpp.o: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/includes/binary_files/file_record.cpp.o: /Users/lulu/Desktop/cs008/FINAL/99_99_final_project-lmorales-41/includes/binary_files/file_record.cpp
CMakeFiles/main.dir/includes/binary_files/file_record.cpp.o: CMakeFiles/main.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/lulu/Desktop/cs008/FINAL/99_99_final_project-lmorales-41/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/main.dir/includes/binary_files/file_record.cpp.o"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/main.dir/includes/binary_files/file_record.cpp.o -MF CMakeFiles/main.dir/includes/binary_files/file_record.cpp.o.d -o CMakeFiles/main.dir/includes/binary_files/file_record.cpp.o -c /Users/lulu/Desktop/cs008/FINAL/99_99_final_project-lmorales-41/includes/binary_files/file_record.cpp

CMakeFiles/main.dir/includes/binary_files/file_record.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/main.dir/includes/binary_files/file_record.cpp.i"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/lulu/Desktop/cs008/FINAL/99_99_final_project-lmorales-41/includes/binary_files/file_record.cpp > CMakeFiles/main.dir/includes/binary_files/file_record.cpp.i

CMakeFiles/main.dir/includes/binary_files/file_record.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/main.dir/includes/binary_files/file_record.cpp.s"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/lulu/Desktop/cs008/FINAL/99_99_final_project-lmorales-41/includes/binary_files/file_record.cpp -o CMakeFiles/main.dir/includes/binary_files/file_record.cpp.s

CMakeFiles/main.dir/includes/binary_files/utilities.cpp.o: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/includes/binary_files/utilities.cpp.o: /Users/lulu/Desktop/cs008/FINAL/99_99_final_project-lmorales-41/includes/binary_files/utilities.cpp
CMakeFiles/main.dir/includes/binary_files/utilities.cpp.o: CMakeFiles/main.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/lulu/Desktop/cs008/FINAL/99_99_final_project-lmorales-41/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/main.dir/includes/binary_files/utilities.cpp.o"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/main.dir/includes/binary_files/utilities.cpp.o -MF CMakeFiles/main.dir/includes/binary_files/utilities.cpp.o.d -o CMakeFiles/main.dir/includes/binary_files/utilities.cpp.o -c /Users/lulu/Desktop/cs008/FINAL/99_99_final_project-lmorales-41/includes/binary_files/utilities.cpp

CMakeFiles/main.dir/includes/binary_files/utilities.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/main.dir/includes/binary_files/utilities.cpp.i"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/lulu/Desktop/cs008/FINAL/99_99_final_project-lmorales-41/includes/binary_files/utilities.cpp > CMakeFiles/main.dir/includes/binary_files/utilities.cpp.i

CMakeFiles/main.dir/includes/binary_files/utilities.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/main.dir/includes/binary_files/utilities.cpp.s"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/lulu/Desktop/cs008/FINAL/99_99_final_project-lmorales-41/includes/binary_files/utilities.cpp -o CMakeFiles/main.dir/includes/binary_files/utilities.cpp.s

CMakeFiles/main.dir/includes/parser/parser.cpp.o: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/includes/parser/parser.cpp.o: /Users/lulu/Desktop/cs008/FINAL/99_99_final_project-lmorales-41/includes/parser/parser.cpp
CMakeFiles/main.dir/includes/parser/parser.cpp.o: CMakeFiles/main.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/lulu/Desktop/cs008/FINAL/99_99_final_project-lmorales-41/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/main.dir/includes/parser/parser.cpp.o"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/main.dir/includes/parser/parser.cpp.o -MF CMakeFiles/main.dir/includes/parser/parser.cpp.o.d -o CMakeFiles/main.dir/includes/parser/parser.cpp.o -c /Users/lulu/Desktop/cs008/FINAL/99_99_final_project-lmorales-41/includes/parser/parser.cpp

CMakeFiles/main.dir/includes/parser/parser.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/main.dir/includes/parser/parser.cpp.i"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/lulu/Desktop/cs008/FINAL/99_99_final_project-lmorales-41/includes/parser/parser.cpp > CMakeFiles/main.dir/includes/parser/parser.cpp.i

CMakeFiles/main.dir/includes/parser/parser.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/main.dir/includes/parser/parser.cpp.s"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/lulu/Desktop/cs008/FINAL/99_99_final_project-lmorales-41/includes/parser/parser.cpp -o CMakeFiles/main.dir/includes/parser/parser.cpp.s

CMakeFiles/main.dir/includes/parser/sql_parser_functions.cpp.o: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/includes/parser/sql_parser_functions.cpp.o: /Users/lulu/Desktop/cs008/FINAL/99_99_final_project-lmorales-41/includes/parser/sql_parser_functions.cpp
CMakeFiles/main.dir/includes/parser/sql_parser_functions.cpp.o: CMakeFiles/main.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/lulu/Desktop/cs008/FINAL/99_99_final_project-lmorales-41/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/main.dir/includes/parser/sql_parser_functions.cpp.o"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/main.dir/includes/parser/sql_parser_functions.cpp.o -MF CMakeFiles/main.dir/includes/parser/sql_parser_functions.cpp.o.d -o CMakeFiles/main.dir/includes/parser/sql_parser_functions.cpp.o -c /Users/lulu/Desktop/cs008/FINAL/99_99_final_project-lmorales-41/includes/parser/sql_parser_functions.cpp

CMakeFiles/main.dir/includes/parser/sql_parser_functions.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/main.dir/includes/parser/sql_parser_functions.cpp.i"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/lulu/Desktop/cs008/FINAL/99_99_final_project-lmorales-41/includes/parser/sql_parser_functions.cpp > CMakeFiles/main.dir/includes/parser/sql_parser_functions.cpp.i

CMakeFiles/main.dir/includes/parser/sql_parser_functions.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/main.dir/includes/parser/sql_parser_functions.cpp.s"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/lulu/Desktop/cs008/FINAL/99_99_final_project-lmorales-41/includes/parser/sql_parser_functions.cpp -o CMakeFiles/main.dir/includes/parser/sql_parser_functions.cpp.s

CMakeFiles/main.dir/includes/shunting_yard/shunting_yard.cpp.o: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/includes/shunting_yard/shunting_yard.cpp.o: /Users/lulu/Desktop/cs008/FINAL/99_99_final_project-lmorales-41/includes/shunting_yard/shunting_yard.cpp
CMakeFiles/main.dir/includes/shunting_yard/shunting_yard.cpp.o: CMakeFiles/main.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/lulu/Desktop/cs008/FINAL/99_99_final_project-lmorales-41/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/main.dir/includes/shunting_yard/shunting_yard.cpp.o"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/main.dir/includes/shunting_yard/shunting_yard.cpp.o -MF CMakeFiles/main.dir/includes/shunting_yard/shunting_yard.cpp.o.d -o CMakeFiles/main.dir/includes/shunting_yard/shunting_yard.cpp.o -c /Users/lulu/Desktop/cs008/FINAL/99_99_final_project-lmorales-41/includes/shunting_yard/shunting_yard.cpp

CMakeFiles/main.dir/includes/shunting_yard/shunting_yard.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/main.dir/includes/shunting_yard/shunting_yard.cpp.i"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/lulu/Desktop/cs008/FINAL/99_99_final_project-lmorales-41/includes/shunting_yard/shunting_yard.cpp > CMakeFiles/main.dir/includes/shunting_yard/shunting_yard.cpp.i

CMakeFiles/main.dir/includes/shunting_yard/shunting_yard.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/main.dir/includes/shunting_yard/shunting_yard.cpp.s"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/lulu/Desktop/cs008/FINAL/99_99_final_project-lmorales-41/includes/shunting_yard/shunting_yard.cpp -o CMakeFiles/main.dir/includes/shunting_yard/shunting_yard.cpp.s

CMakeFiles/main.dir/includes/sql/sql.cpp.o: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/includes/sql/sql.cpp.o: /Users/lulu/Desktop/cs008/FINAL/99_99_final_project-lmorales-41/includes/sql/sql.cpp
CMakeFiles/main.dir/includes/sql/sql.cpp.o: CMakeFiles/main.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/lulu/Desktop/cs008/FINAL/99_99_final_project-lmorales-41/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/main.dir/includes/sql/sql.cpp.o"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/main.dir/includes/sql/sql.cpp.o -MF CMakeFiles/main.dir/includes/sql/sql.cpp.o.d -o CMakeFiles/main.dir/includes/sql/sql.cpp.o -c /Users/lulu/Desktop/cs008/FINAL/99_99_final_project-lmorales-41/includes/sql/sql.cpp

CMakeFiles/main.dir/includes/sql/sql.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/main.dir/includes/sql/sql.cpp.i"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/lulu/Desktop/cs008/FINAL/99_99_final_project-lmorales-41/includes/sql/sql.cpp > CMakeFiles/main.dir/includes/sql/sql.cpp.i

CMakeFiles/main.dir/includes/sql/sql.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/main.dir/includes/sql/sql.cpp.s"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/lulu/Desktop/cs008/FINAL/99_99_final_project-lmorales-41/includes/sql/sql.cpp -o CMakeFiles/main.dir/includes/sql/sql.cpp.s

CMakeFiles/main.dir/includes/stub/stub.cpp.o: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/includes/stub/stub.cpp.o: /Users/lulu/Desktop/cs008/FINAL/99_99_final_project-lmorales-41/includes/stub/stub.cpp
CMakeFiles/main.dir/includes/stub/stub.cpp.o: CMakeFiles/main.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/lulu/Desktop/cs008/FINAL/99_99_final_project-lmorales-41/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/main.dir/includes/stub/stub.cpp.o"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/main.dir/includes/stub/stub.cpp.o -MF CMakeFiles/main.dir/includes/stub/stub.cpp.o.d -o CMakeFiles/main.dir/includes/stub/stub.cpp.o -c /Users/lulu/Desktop/cs008/FINAL/99_99_final_project-lmorales-41/includes/stub/stub.cpp

CMakeFiles/main.dir/includes/stub/stub.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/main.dir/includes/stub/stub.cpp.i"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/lulu/Desktop/cs008/FINAL/99_99_final_project-lmorales-41/includes/stub/stub.cpp > CMakeFiles/main.dir/includes/stub/stub.cpp.i

CMakeFiles/main.dir/includes/stub/stub.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/main.dir/includes/stub/stub.cpp.s"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/lulu/Desktop/cs008/FINAL/99_99_final_project-lmorales-41/includes/stub/stub.cpp -o CMakeFiles/main.dir/includes/stub/stub.cpp.s

CMakeFiles/main.dir/includes/table/rpn.cpp.o: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/includes/table/rpn.cpp.o: /Users/lulu/Desktop/cs008/FINAL/99_99_final_project-lmorales-41/includes/table/rpn.cpp
CMakeFiles/main.dir/includes/table/rpn.cpp.o: CMakeFiles/main.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/lulu/Desktop/cs008/FINAL/99_99_final_project-lmorales-41/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object CMakeFiles/main.dir/includes/table/rpn.cpp.o"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/main.dir/includes/table/rpn.cpp.o -MF CMakeFiles/main.dir/includes/table/rpn.cpp.o.d -o CMakeFiles/main.dir/includes/table/rpn.cpp.o -c /Users/lulu/Desktop/cs008/FINAL/99_99_final_project-lmorales-41/includes/table/rpn.cpp

CMakeFiles/main.dir/includes/table/rpn.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/main.dir/includes/table/rpn.cpp.i"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/lulu/Desktop/cs008/FINAL/99_99_final_project-lmorales-41/includes/table/rpn.cpp > CMakeFiles/main.dir/includes/table/rpn.cpp.i

CMakeFiles/main.dir/includes/table/rpn.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/main.dir/includes/table/rpn.cpp.s"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/lulu/Desktop/cs008/FINAL/99_99_final_project-lmorales-41/includes/table/rpn.cpp -o CMakeFiles/main.dir/includes/table/rpn.cpp.s

CMakeFiles/main.dir/includes/table/table.cpp.o: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/includes/table/table.cpp.o: /Users/lulu/Desktop/cs008/FINAL/99_99_final_project-lmorales-41/includes/table/table.cpp
CMakeFiles/main.dir/includes/table/table.cpp.o: CMakeFiles/main.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/lulu/Desktop/cs008/FINAL/99_99_final_project-lmorales-41/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Building CXX object CMakeFiles/main.dir/includes/table/table.cpp.o"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/main.dir/includes/table/table.cpp.o -MF CMakeFiles/main.dir/includes/table/table.cpp.o.d -o CMakeFiles/main.dir/includes/table/table.cpp.o -c /Users/lulu/Desktop/cs008/FINAL/99_99_final_project-lmorales-41/includes/table/table.cpp

CMakeFiles/main.dir/includes/table/table.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/main.dir/includes/table/table.cpp.i"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/lulu/Desktop/cs008/FINAL/99_99_final_project-lmorales-41/includes/table/table.cpp > CMakeFiles/main.dir/includes/table/table.cpp.i

CMakeFiles/main.dir/includes/table/table.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/main.dir/includes/table/table.cpp.s"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/lulu/Desktop/cs008/FINAL/99_99_final_project-lmorales-41/includes/table/table.cpp -o CMakeFiles/main.dir/includes/table/table.cpp.s

CMakeFiles/main.dir/includes/tokenizer/ftokenize.cpp.o: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/includes/tokenizer/ftokenize.cpp.o: /Users/lulu/Desktop/cs008/FINAL/99_99_final_project-lmorales-41/includes/tokenizer/ftokenize.cpp
CMakeFiles/main.dir/includes/tokenizer/ftokenize.cpp.o: CMakeFiles/main.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/lulu/Desktop/cs008/FINAL/99_99_final_project-lmorales-41/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_11) "Building CXX object CMakeFiles/main.dir/includes/tokenizer/ftokenize.cpp.o"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/main.dir/includes/tokenizer/ftokenize.cpp.o -MF CMakeFiles/main.dir/includes/tokenizer/ftokenize.cpp.o.d -o CMakeFiles/main.dir/includes/tokenizer/ftokenize.cpp.o -c /Users/lulu/Desktop/cs008/FINAL/99_99_final_project-lmorales-41/includes/tokenizer/ftokenize.cpp

CMakeFiles/main.dir/includes/tokenizer/ftokenize.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/main.dir/includes/tokenizer/ftokenize.cpp.i"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/lulu/Desktop/cs008/FINAL/99_99_final_project-lmorales-41/includes/tokenizer/ftokenize.cpp > CMakeFiles/main.dir/includes/tokenizer/ftokenize.cpp.i

CMakeFiles/main.dir/includes/tokenizer/ftokenize.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/main.dir/includes/tokenizer/ftokenize.cpp.s"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/lulu/Desktop/cs008/FINAL/99_99_final_project-lmorales-41/includes/tokenizer/ftokenize.cpp -o CMakeFiles/main.dir/includes/tokenizer/ftokenize.cpp.s

CMakeFiles/main.dir/includes/tokenizer/state_machine_functions.cpp.o: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/includes/tokenizer/state_machine_functions.cpp.o: /Users/lulu/Desktop/cs008/FINAL/99_99_final_project-lmorales-41/includes/tokenizer/state_machine_functions.cpp
CMakeFiles/main.dir/includes/tokenizer/state_machine_functions.cpp.o: CMakeFiles/main.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/lulu/Desktop/cs008/FINAL/99_99_final_project-lmorales-41/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_12) "Building CXX object CMakeFiles/main.dir/includes/tokenizer/state_machine_functions.cpp.o"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/main.dir/includes/tokenizer/state_machine_functions.cpp.o -MF CMakeFiles/main.dir/includes/tokenizer/state_machine_functions.cpp.o.d -o CMakeFiles/main.dir/includes/tokenizer/state_machine_functions.cpp.o -c /Users/lulu/Desktop/cs008/FINAL/99_99_final_project-lmorales-41/includes/tokenizer/state_machine_functions.cpp

CMakeFiles/main.dir/includes/tokenizer/state_machine_functions.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/main.dir/includes/tokenizer/state_machine_functions.cpp.i"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/lulu/Desktop/cs008/FINAL/99_99_final_project-lmorales-41/includes/tokenizer/state_machine_functions.cpp > CMakeFiles/main.dir/includes/tokenizer/state_machine_functions.cpp.i

CMakeFiles/main.dir/includes/tokenizer/state_machine_functions.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/main.dir/includes/tokenizer/state_machine_functions.cpp.s"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/lulu/Desktop/cs008/FINAL/99_99_final_project-lmorales-41/includes/tokenizer/state_machine_functions.cpp -o CMakeFiles/main.dir/includes/tokenizer/state_machine_functions.cpp.s

CMakeFiles/main.dir/includes/tokenizer/stokenize.cpp.o: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/includes/tokenizer/stokenize.cpp.o: /Users/lulu/Desktop/cs008/FINAL/99_99_final_project-lmorales-41/includes/tokenizer/stokenize.cpp
CMakeFiles/main.dir/includes/tokenizer/stokenize.cpp.o: CMakeFiles/main.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/lulu/Desktop/cs008/FINAL/99_99_final_project-lmorales-41/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_13) "Building CXX object CMakeFiles/main.dir/includes/tokenizer/stokenize.cpp.o"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/main.dir/includes/tokenizer/stokenize.cpp.o -MF CMakeFiles/main.dir/includes/tokenizer/stokenize.cpp.o.d -o CMakeFiles/main.dir/includes/tokenizer/stokenize.cpp.o -c /Users/lulu/Desktop/cs008/FINAL/99_99_final_project-lmorales-41/includes/tokenizer/stokenize.cpp

CMakeFiles/main.dir/includes/tokenizer/stokenize.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/main.dir/includes/tokenizer/stokenize.cpp.i"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/lulu/Desktop/cs008/FINAL/99_99_final_project-lmorales-41/includes/tokenizer/stokenize.cpp > CMakeFiles/main.dir/includes/tokenizer/stokenize.cpp.i

CMakeFiles/main.dir/includes/tokenizer/stokenize.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/main.dir/includes/tokenizer/stokenize.cpp.s"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/lulu/Desktop/cs008/FINAL/99_99_final_project-lmorales-41/includes/tokenizer/stokenize.cpp -o CMakeFiles/main.dir/includes/tokenizer/stokenize.cpp.s

# Object files for target main
main_OBJECTS = \
"CMakeFiles/main.dir/main.cpp.o" \
"CMakeFiles/main.dir/includes/binary_files/file_record.cpp.o" \
"CMakeFiles/main.dir/includes/binary_files/utilities.cpp.o" \
"CMakeFiles/main.dir/includes/parser/parser.cpp.o" \
"CMakeFiles/main.dir/includes/parser/sql_parser_functions.cpp.o" \
"CMakeFiles/main.dir/includes/shunting_yard/shunting_yard.cpp.o" \
"CMakeFiles/main.dir/includes/sql/sql.cpp.o" \
"CMakeFiles/main.dir/includes/stub/stub.cpp.o" \
"CMakeFiles/main.dir/includes/table/rpn.cpp.o" \
"CMakeFiles/main.dir/includes/table/table.cpp.o" \
"CMakeFiles/main.dir/includes/tokenizer/ftokenize.cpp.o" \
"CMakeFiles/main.dir/includes/tokenizer/state_machine_functions.cpp.o" \
"CMakeFiles/main.dir/includes/tokenizer/stokenize.cpp.o"

# External object files for target main
main_EXTERNAL_OBJECTS =

bin/main: CMakeFiles/main.dir/main.cpp.o
bin/main: CMakeFiles/main.dir/includes/binary_files/file_record.cpp.o
bin/main: CMakeFiles/main.dir/includes/binary_files/utilities.cpp.o
bin/main: CMakeFiles/main.dir/includes/parser/parser.cpp.o
bin/main: CMakeFiles/main.dir/includes/parser/sql_parser_functions.cpp.o
bin/main: CMakeFiles/main.dir/includes/shunting_yard/shunting_yard.cpp.o
bin/main: CMakeFiles/main.dir/includes/sql/sql.cpp.o
bin/main: CMakeFiles/main.dir/includes/stub/stub.cpp.o
bin/main: CMakeFiles/main.dir/includes/table/rpn.cpp.o
bin/main: CMakeFiles/main.dir/includes/table/table.cpp.o
bin/main: CMakeFiles/main.dir/includes/tokenizer/ftokenize.cpp.o
bin/main: CMakeFiles/main.dir/includes/tokenizer/state_machine_functions.cpp.o
bin/main: CMakeFiles/main.dir/includes/tokenizer/stokenize.cpp.o
bin/main: CMakeFiles/main.dir/build.make
bin/main: CMakeFiles/main.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/Users/lulu/Desktop/cs008/FINAL/99_99_final_project-lmorales-41/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_14) "Linking CXX executable bin/main"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/main.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/main.dir/build: bin/main
.PHONY : CMakeFiles/main.dir/build

CMakeFiles/main.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/main.dir/cmake_clean.cmake
.PHONY : CMakeFiles/main.dir/clean

CMakeFiles/main.dir/depend:
	cd /Users/lulu/Desktop/cs008/FINAL/99_99_final_project-lmorales-41/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/lulu/Desktop/cs008/FINAL/99_99_final_project-lmorales-41 /Users/lulu/Desktop/cs008/FINAL/99_99_final_project-lmorales-41 /Users/lulu/Desktop/cs008/FINAL/99_99_final_project-lmorales-41/build /Users/lulu/Desktop/cs008/FINAL/99_99_final_project-lmorales-41/build /Users/lulu/Desktop/cs008/FINAL/99_99_final_project-lmorales-41/build/CMakeFiles/main.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/main.dir/depend
