cmake_minimum_required(VERSION 2.6)
project(LD36)

# load & include alligator
add_subdirectory(module/alligator/)
include_directories(module/alligator/src)

add_subdirectory(module/astarcpp)

# common flags
list(APPEND CMAKE_CXX_FLAGS "-std=c++11 -g -ftest-coverage -fprofile-arcs")

# core sources
file(GLOB_RECURSE CORE_CPP src/core/*.cpp)
file(GLOB_RECURSE CORE_HEADERS src/core/*.h)
set(CORE_SOURCES ${CORE_CPP} ${CORE_HEADERS})


# SO dependant
if(WIN32)
	list(APPEND CMAKE_EXE_LINKER_FLAGS "-static-libstdc++ -static-libgcc")
	set(EXECUTABLE_OUTPUT_PATH ${CMAKE_HOME_DIRECTORY}/bin/win32)
elseif(UNIX)
	set(EXECUTABLE_OUTPUT_PATH ${CMAKE_HOME_DIRECTORY}/bin/linux)
endif()

# add a new target with allegro, alligator and core sources. uses monolith for win32
function(add_alleg_target EXEC-NAME SRCS)
	add_executable(${EXEC-NAME} ${CORE_SOURCES} ${ASTAR_SOURCES} ${SRCS})
	include_directories(${EXEC-NAME} module/astarcpp/src)
	target_link_libraries(${EXEC-NAME} alligator)
	if(WIN32)
		target_link_libraries(${EXEC-NAME} allegro_monolith)
	elseif(UNIX)
		target_link_libraries(${EXEC-NAME} allegro)
		target_link_libraries(${EXEC-NAME} allegro_image)
		target_link_libraries(${EXEC-NAME} allegro_primitives)
		target_link_libraries(${EXEC-NAME} allegro_font)
		target_link_libraries(${EXEC-NAME} allegro_ttf)
		target_link_libraries(${EXEC-NAME} allegro_audio)
		target_link_libraries(${EXEC-NAME} allegro_acodec)
	else()
		message(SEND_FATAL "Unknown platform")
	endif()
endfunction(add_alleg_target)

add_alleg_target(ld36 src/game/game.cpp)
add_alleg_target(editor src/editor/editor.cpp)


