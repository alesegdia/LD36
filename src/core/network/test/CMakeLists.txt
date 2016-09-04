cmake_minimum_required(VERSION 2.6)
project(network-tests)

add_subdirectory(module/enet)

# common flags
list(APPEND CMAKE_CXX_FLAGS "-std=c++11 -g -ftest-coverage -fprofile-arcs")

# SO dependant
if(WIN32)
	list(APPEND CMAKE_EXE_LINKER_FLAGS "-static-libstdc++ -static-libgcc")
	set(EXECUTABLE_OUTPUT_PATH ${CMAKE_HOME_DIRECTORY}/bin/win32)
elseif(UNIX)
	set(EXECUTABLE_OUTPUT_PATH ${CMAKE_HOME_DIRECTORY}/bin/linux)
endif()

set(COMMON_SOURCES
	src/common.h
	src/common.cpp)

# add a new target with allegro, alligator and core sources. uses monolith for win32
function(add_test EXEC-NAME SRCS)
	add_executable(${EXEC-NAME} ${COMMON_SOURCES} ${SRCS})
	include_directories(${EXEC-NAME} module/enet/include)
	target_link_libraries(${EXEC-NAME} enet)
endfunction(add_test)

set(NONBLOCK_SERVER_SOURCES
	src/nonblock/server.cpp)

set(NONBLOCK_CLIENT_SOURCES
	src/nonblock/client.cpp)

add_test(server ${NONBLOCK_SERVER_SOURCES})
add_test(client ${NONBLOCK_CLIENT_SOURCES})


