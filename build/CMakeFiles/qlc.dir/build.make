# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

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

# Produce verbose output by default.
VERBOSE = 1

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
CMAKE_SOURCE_DIR = /home/qlc/muduo

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/qlc/muduo/build

# Include any dependencies generated for this target.
include CMakeFiles/qlc.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/qlc.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/qlc.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/qlc.dir/flags.make

CMakeFiles/qlc.dir/src/DefaultPoller.o: CMakeFiles/qlc.dir/flags.make
CMakeFiles/qlc.dir/src/DefaultPoller.o: ../src/DefaultPoller.cpp
CMakeFiles/qlc.dir/src/DefaultPoller.o: CMakeFiles/qlc.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/qlc/muduo/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/qlc.dir/src/DefaultPoller.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/qlc.dir/src/DefaultPoller.o -MF CMakeFiles/qlc.dir/src/DefaultPoller.o.d -o CMakeFiles/qlc.dir/src/DefaultPoller.o -c /home/qlc/muduo/src/DefaultPoller.cpp

CMakeFiles/qlc.dir/src/DefaultPoller.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/qlc.dir/src/DefaultPoller.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/qlc/muduo/src/DefaultPoller.cpp > CMakeFiles/qlc.dir/src/DefaultPoller.i

CMakeFiles/qlc.dir/src/DefaultPoller.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/qlc.dir/src/DefaultPoller.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/qlc/muduo/src/DefaultPoller.cpp -o CMakeFiles/qlc.dir/src/DefaultPoller.s

CMakeFiles/qlc.dir/src/EpollPoller.o: CMakeFiles/qlc.dir/flags.make
CMakeFiles/qlc.dir/src/EpollPoller.o: ../src/EpollPoller.cpp
CMakeFiles/qlc.dir/src/EpollPoller.o: CMakeFiles/qlc.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/qlc/muduo/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/qlc.dir/src/EpollPoller.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/qlc.dir/src/EpollPoller.o -MF CMakeFiles/qlc.dir/src/EpollPoller.o.d -o CMakeFiles/qlc.dir/src/EpollPoller.o -c /home/qlc/muduo/src/EpollPoller.cpp

CMakeFiles/qlc.dir/src/EpollPoller.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/qlc.dir/src/EpollPoller.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/qlc/muduo/src/EpollPoller.cpp > CMakeFiles/qlc.dir/src/EpollPoller.i

CMakeFiles/qlc.dir/src/EpollPoller.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/qlc.dir/src/EpollPoller.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/qlc/muduo/src/EpollPoller.cpp -o CMakeFiles/qlc.dir/src/EpollPoller.s

CMakeFiles/qlc.dir/src/EventLoop.o: CMakeFiles/qlc.dir/flags.make
CMakeFiles/qlc.dir/src/EventLoop.o: ../src/EventLoop.cpp
CMakeFiles/qlc.dir/src/EventLoop.o: CMakeFiles/qlc.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/qlc/muduo/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/qlc.dir/src/EventLoop.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/qlc.dir/src/EventLoop.o -MF CMakeFiles/qlc.dir/src/EventLoop.o.d -o CMakeFiles/qlc.dir/src/EventLoop.o -c /home/qlc/muduo/src/EventLoop.cpp

CMakeFiles/qlc.dir/src/EventLoop.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/qlc.dir/src/EventLoop.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/qlc/muduo/src/EventLoop.cpp > CMakeFiles/qlc.dir/src/EventLoop.i

CMakeFiles/qlc.dir/src/EventLoop.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/qlc.dir/src/EventLoop.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/qlc/muduo/src/EventLoop.cpp -o CMakeFiles/qlc.dir/src/EventLoop.s

CMakeFiles/qlc.dir/src/EventLoopThread.o: CMakeFiles/qlc.dir/flags.make
CMakeFiles/qlc.dir/src/EventLoopThread.o: ../src/EventLoopThread.cpp
CMakeFiles/qlc.dir/src/EventLoopThread.o: CMakeFiles/qlc.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/qlc/muduo/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/qlc.dir/src/EventLoopThread.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/qlc.dir/src/EventLoopThread.o -MF CMakeFiles/qlc.dir/src/EventLoopThread.o.d -o CMakeFiles/qlc.dir/src/EventLoopThread.o -c /home/qlc/muduo/src/EventLoopThread.cpp

CMakeFiles/qlc.dir/src/EventLoopThread.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/qlc.dir/src/EventLoopThread.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/qlc/muduo/src/EventLoopThread.cpp > CMakeFiles/qlc.dir/src/EventLoopThread.i

CMakeFiles/qlc.dir/src/EventLoopThread.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/qlc.dir/src/EventLoopThread.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/qlc/muduo/src/EventLoopThread.cpp -o CMakeFiles/qlc.dir/src/EventLoopThread.s

CMakeFiles/qlc.dir/src/InetAddress.o: CMakeFiles/qlc.dir/flags.make
CMakeFiles/qlc.dir/src/InetAddress.o: ../src/InetAddress.cpp
CMakeFiles/qlc.dir/src/InetAddress.o: CMakeFiles/qlc.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/qlc/muduo/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/qlc.dir/src/InetAddress.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/qlc.dir/src/InetAddress.o -MF CMakeFiles/qlc.dir/src/InetAddress.o.d -o CMakeFiles/qlc.dir/src/InetAddress.o -c /home/qlc/muduo/src/InetAddress.cpp

CMakeFiles/qlc.dir/src/InetAddress.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/qlc.dir/src/InetAddress.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/qlc/muduo/src/InetAddress.cpp > CMakeFiles/qlc.dir/src/InetAddress.i

CMakeFiles/qlc.dir/src/InetAddress.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/qlc.dir/src/InetAddress.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/qlc/muduo/src/InetAddress.cpp -o CMakeFiles/qlc.dir/src/InetAddress.s

CMakeFiles/qlc.dir/src/Poller.o: CMakeFiles/qlc.dir/flags.make
CMakeFiles/qlc.dir/src/Poller.o: ../src/Poller.cpp
CMakeFiles/qlc.dir/src/Poller.o: CMakeFiles/qlc.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/qlc/muduo/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/qlc.dir/src/Poller.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/qlc.dir/src/Poller.o -MF CMakeFiles/qlc.dir/src/Poller.o.d -o CMakeFiles/qlc.dir/src/Poller.o -c /home/qlc/muduo/src/Poller.cpp

CMakeFiles/qlc.dir/src/Poller.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/qlc.dir/src/Poller.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/qlc/muduo/src/Poller.cpp > CMakeFiles/qlc.dir/src/Poller.i

CMakeFiles/qlc.dir/src/Poller.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/qlc.dir/src/Poller.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/qlc/muduo/src/Poller.cpp -o CMakeFiles/qlc.dir/src/Poller.s

CMakeFiles/qlc.dir/src/TcpServer.o: CMakeFiles/qlc.dir/flags.make
CMakeFiles/qlc.dir/src/TcpServer.o: ../src/TcpServer.cpp
CMakeFiles/qlc.dir/src/TcpServer.o: CMakeFiles/qlc.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/qlc/muduo/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/qlc.dir/src/TcpServer.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/qlc.dir/src/TcpServer.o -MF CMakeFiles/qlc.dir/src/TcpServer.o.d -o CMakeFiles/qlc.dir/src/TcpServer.o -c /home/qlc/muduo/src/TcpServer.cpp

CMakeFiles/qlc.dir/src/TcpServer.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/qlc.dir/src/TcpServer.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/qlc/muduo/src/TcpServer.cpp > CMakeFiles/qlc.dir/src/TcpServer.i

CMakeFiles/qlc.dir/src/TcpServer.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/qlc.dir/src/TcpServer.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/qlc/muduo/src/TcpServer.cpp -o CMakeFiles/qlc.dir/src/TcpServer.s

CMakeFiles/qlc.dir/src/ThreadC11.o: CMakeFiles/qlc.dir/flags.make
CMakeFiles/qlc.dir/src/ThreadC11.o: ../src/ThreadC11.cpp
CMakeFiles/qlc.dir/src/ThreadC11.o: CMakeFiles/qlc.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/qlc/muduo/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/qlc.dir/src/ThreadC11.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/qlc.dir/src/ThreadC11.o -MF CMakeFiles/qlc.dir/src/ThreadC11.o.d -o CMakeFiles/qlc.dir/src/ThreadC11.o -c /home/qlc/muduo/src/ThreadC11.cpp

CMakeFiles/qlc.dir/src/ThreadC11.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/qlc.dir/src/ThreadC11.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/qlc/muduo/src/ThreadC11.cpp > CMakeFiles/qlc.dir/src/ThreadC11.i

CMakeFiles/qlc.dir/src/ThreadC11.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/qlc.dir/src/ThreadC11.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/qlc/muduo/src/ThreadC11.cpp -o CMakeFiles/qlc.dir/src/ThreadC11.s

CMakeFiles/qlc.dir/src/Timestamp.o: CMakeFiles/qlc.dir/flags.make
CMakeFiles/qlc.dir/src/Timestamp.o: ../src/Timestamp.cpp
CMakeFiles/qlc.dir/src/Timestamp.o: CMakeFiles/qlc.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/qlc/muduo/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object CMakeFiles/qlc.dir/src/Timestamp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/qlc.dir/src/Timestamp.o -MF CMakeFiles/qlc.dir/src/Timestamp.o.d -o CMakeFiles/qlc.dir/src/Timestamp.o -c /home/qlc/muduo/src/Timestamp.cpp

CMakeFiles/qlc.dir/src/Timestamp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/qlc.dir/src/Timestamp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/qlc/muduo/src/Timestamp.cpp > CMakeFiles/qlc.dir/src/Timestamp.i

CMakeFiles/qlc.dir/src/Timestamp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/qlc.dir/src/Timestamp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/qlc/muduo/src/Timestamp.cpp -o CMakeFiles/qlc.dir/src/Timestamp.s

CMakeFiles/qlc.dir/src/channel.o: CMakeFiles/qlc.dir/flags.make
CMakeFiles/qlc.dir/src/channel.o: ../src/channel.cpp
CMakeFiles/qlc.dir/src/channel.o: CMakeFiles/qlc.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/qlc/muduo/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Building CXX object CMakeFiles/qlc.dir/src/channel.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/qlc.dir/src/channel.o -MF CMakeFiles/qlc.dir/src/channel.o.d -o CMakeFiles/qlc.dir/src/channel.o -c /home/qlc/muduo/src/channel.cpp

CMakeFiles/qlc.dir/src/channel.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/qlc.dir/src/channel.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/qlc/muduo/src/channel.cpp > CMakeFiles/qlc.dir/src/channel.i

CMakeFiles/qlc.dir/src/channel.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/qlc.dir/src/channel.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/qlc/muduo/src/channel.cpp -o CMakeFiles/qlc.dir/src/channel.s

CMakeFiles/qlc.dir/src/config.o: CMakeFiles/qlc.dir/flags.make
CMakeFiles/qlc.dir/src/config.o: ../src/config.cpp
CMakeFiles/qlc.dir/src/config.o: CMakeFiles/qlc.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/qlc/muduo/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_11) "Building CXX object CMakeFiles/qlc.dir/src/config.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/qlc.dir/src/config.o -MF CMakeFiles/qlc.dir/src/config.o.d -o CMakeFiles/qlc.dir/src/config.o -c /home/qlc/muduo/src/config.cpp

CMakeFiles/qlc.dir/src/config.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/qlc.dir/src/config.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/qlc/muduo/src/config.cpp > CMakeFiles/qlc.dir/src/config.i

CMakeFiles/qlc.dir/src/config.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/qlc.dir/src/config.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/qlc/muduo/src/config.cpp -o CMakeFiles/qlc.dir/src/config.s

CMakeFiles/qlc.dir/src/mutex.o: CMakeFiles/qlc.dir/flags.make
CMakeFiles/qlc.dir/src/mutex.o: ../src/mutex.cpp
CMakeFiles/qlc.dir/src/mutex.o: CMakeFiles/qlc.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/qlc/muduo/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_12) "Building CXX object CMakeFiles/qlc.dir/src/mutex.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/qlc.dir/src/mutex.o -MF CMakeFiles/qlc.dir/src/mutex.o.d -o CMakeFiles/qlc.dir/src/mutex.o -c /home/qlc/muduo/src/mutex.cpp

CMakeFiles/qlc.dir/src/mutex.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/qlc.dir/src/mutex.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/qlc/muduo/src/mutex.cpp > CMakeFiles/qlc.dir/src/mutex.i

CMakeFiles/qlc.dir/src/mutex.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/qlc.dir/src/mutex.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/qlc/muduo/src/mutex.cpp -o CMakeFiles/qlc.dir/src/mutex.s

CMakeFiles/qlc.dir/src/qlc_log.o: CMakeFiles/qlc.dir/flags.make
CMakeFiles/qlc.dir/src/qlc_log.o: ../src/qlc_log.cpp
CMakeFiles/qlc.dir/src/qlc_log.o: CMakeFiles/qlc.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/qlc/muduo/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_13) "Building CXX object CMakeFiles/qlc.dir/src/qlc_log.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/qlc.dir/src/qlc_log.o -MF CMakeFiles/qlc.dir/src/qlc_log.o.d -o CMakeFiles/qlc.dir/src/qlc_log.o -c /home/qlc/muduo/src/qlc_log.cpp

CMakeFiles/qlc.dir/src/qlc_log.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/qlc.dir/src/qlc_log.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/qlc/muduo/src/qlc_log.cpp > CMakeFiles/qlc.dir/src/qlc_log.i

CMakeFiles/qlc.dir/src/qlc_log.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/qlc.dir/src/qlc_log.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/qlc/muduo/src/qlc_log.cpp -o CMakeFiles/qlc.dir/src/qlc_log.s

CMakeFiles/qlc.dir/src/thread.o: CMakeFiles/qlc.dir/flags.make
CMakeFiles/qlc.dir/src/thread.o: ../src/thread.cpp
CMakeFiles/qlc.dir/src/thread.o: CMakeFiles/qlc.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/qlc/muduo/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_14) "Building CXX object CMakeFiles/qlc.dir/src/thread.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/qlc.dir/src/thread.o -MF CMakeFiles/qlc.dir/src/thread.o.d -o CMakeFiles/qlc.dir/src/thread.o -c /home/qlc/muduo/src/thread.cpp

CMakeFiles/qlc.dir/src/thread.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/qlc.dir/src/thread.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/qlc/muduo/src/thread.cpp > CMakeFiles/qlc.dir/src/thread.i

CMakeFiles/qlc.dir/src/thread.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/qlc.dir/src/thread.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/qlc/muduo/src/thread.cpp -o CMakeFiles/qlc.dir/src/thread.s

CMakeFiles/qlc.dir/src/util.o: CMakeFiles/qlc.dir/flags.make
CMakeFiles/qlc.dir/src/util.o: ../src/util.cpp
CMakeFiles/qlc.dir/src/util.o: CMakeFiles/qlc.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/qlc/muduo/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_15) "Building CXX object CMakeFiles/qlc.dir/src/util.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/qlc.dir/src/util.o -MF CMakeFiles/qlc.dir/src/util.o.d -o CMakeFiles/qlc.dir/src/util.o -c /home/qlc/muduo/src/util.cpp

CMakeFiles/qlc.dir/src/util.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/qlc.dir/src/util.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/qlc/muduo/src/util.cpp > CMakeFiles/qlc.dir/src/util.i

CMakeFiles/qlc.dir/src/util.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/qlc.dir/src/util.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/qlc/muduo/src/util.cpp -o CMakeFiles/qlc.dir/src/util.s

# Object files for target qlc
qlc_OBJECTS = \
"CMakeFiles/qlc.dir/src/DefaultPoller.o" \
"CMakeFiles/qlc.dir/src/EpollPoller.o" \
"CMakeFiles/qlc.dir/src/EventLoop.o" \
"CMakeFiles/qlc.dir/src/EventLoopThread.o" \
"CMakeFiles/qlc.dir/src/InetAddress.o" \
"CMakeFiles/qlc.dir/src/Poller.o" \
"CMakeFiles/qlc.dir/src/TcpServer.o" \
"CMakeFiles/qlc.dir/src/ThreadC11.o" \
"CMakeFiles/qlc.dir/src/Timestamp.o" \
"CMakeFiles/qlc.dir/src/channel.o" \
"CMakeFiles/qlc.dir/src/config.o" \
"CMakeFiles/qlc.dir/src/mutex.o" \
"CMakeFiles/qlc.dir/src/qlc_log.o" \
"CMakeFiles/qlc.dir/src/thread.o" \
"CMakeFiles/qlc.dir/src/util.o"

# External object files for target qlc
qlc_EXTERNAL_OBJECTS =

../lib/libqlc.so: CMakeFiles/qlc.dir/src/DefaultPoller.o
../lib/libqlc.so: CMakeFiles/qlc.dir/src/EpollPoller.o
../lib/libqlc.so: CMakeFiles/qlc.dir/src/EventLoop.o
../lib/libqlc.so: CMakeFiles/qlc.dir/src/EventLoopThread.o
../lib/libqlc.so: CMakeFiles/qlc.dir/src/InetAddress.o
../lib/libqlc.so: CMakeFiles/qlc.dir/src/Poller.o
../lib/libqlc.so: CMakeFiles/qlc.dir/src/TcpServer.o
../lib/libqlc.so: CMakeFiles/qlc.dir/src/ThreadC11.o
../lib/libqlc.so: CMakeFiles/qlc.dir/src/Timestamp.o
../lib/libqlc.so: CMakeFiles/qlc.dir/src/channel.o
../lib/libqlc.so: CMakeFiles/qlc.dir/src/config.o
../lib/libqlc.so: CMakeFiles/qlc.dir/src/mutex.o
../lib/libqlc.so: CMakeFiles/qlc.dir/src/qlc_log.o
../lib/libqlc.so: CMakeFiles/qlc.dir/src/thread.o
../lib/libqlc.so: CMakeFiles/qlc.dir/src/util.o
../lib/libqlc.so: CMakeFiles/qlc.dir/build.make
../lib/libqlc.so: CMakeFiles/qlc.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/qlc/muduo/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_16) "Linking CXX shared library ../lib/libqlc.so"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/qlc.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/qlc.dir/build: ../lib/libqlc.so
.PHONY : CMakeFiles/qlc.dir/build

CMakeFiles/qlc.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/qlc.dir/cmake_clean.cmake
.PHONY : CMakeFiles/qlc.dir/clean

CMakeFiles/qlc.dir/depend:
	cd /home/qlc/muduo/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/qlc/muduo /home/qlc/muduo /home/qlc/muduo/build /home/qlc/muduo/build /home/qlc/muduo/build/CMakeFiles/qlc.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/qlc.dir/depend

