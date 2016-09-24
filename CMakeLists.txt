cmake_minimum_required(VERSION 2.6)
project(LD36)


# SO DEPENDANT #############################################################
if(WIN32)
	list(APPEND CMAKE_EXE_LINKER_FLAGS "-static-libstdc++ -static-libgcc")
	set(EXECUTABLE_OUTPUT_PATH ${CMAKE_HOME_DIRECTORY}/bin/win32)
elseif(UNIX)
	set(EXECUTABLE_OUTPUT_PATH ${CMAKE_HOME_DIRECTORY}/bin/linux)
endif()


# LOAD SUBMODULES ##########################################################
add_subdirectory(module/alligator)
add_subdirectory(module/astarcpp)
add_subdirectory(module/enet)


# ALLEG EXECUTABLES ########################################################
set(CORE_SCENE_SRC
	src/core/scene/actor.cpp
	src/core/scene/actor.h
	src/core/scene/entity.cpp
	src/core/scene/entity.h
	src/core/scene/isometrictranslator.cpp
	src/core/scene/isometrictranslator.h
	src/core/scene/renderer.cpp
	src/core/scene/renderer.h
	src/core/scene/scene.cpp
	src/core/scene/scene.h
	src/core/scene/spawner.cpp
	src/core/scene/spawner.h
	src/core/scene/tilemap.cpp
	src/core/scene/tilemap.h
	)

set(CORE_SCREEN_SRC
	src/core/screen/mapscreen.cpp
	src/core/screen/mapscreen.h
	src/core/screen/menuscreen.cpp
	src/core/screen/menuscreen.h
	src/core/screen/lobbyscreen.cpp
	src/core/screen/lobbyscreen.h
	)

set(CORE_NETWORK_SRC
	src/core/network/client.cpp
	src/core/network/client.h
	src/core/network/protocol.cpp
	src/core/network/protocol.h
	src/core/network/packetbuilder.cpp
	src/core/network/packetbuilder.h
	src/core/network/buffer.cpp
	src/core/network/buffer.h
	src/core/network/utils.cpp
	src/core/network/utils.h
	)

set(CORE_COMMAND_SRC
	src/core/command/commandprocessor.cpp
	src/core/command/commandprocessor.h
	src/core/command/aicommands.cpp
	src/core/command/aicommands.h
	src/core/command/astartilemapmodel.cpp
	src/core/command/astartilemapmodel.h
	src/core/command/command.cpp
	src/core/command/command.h
	src/core/command/spawncommands.cpp
	src/core/command/spawncommands.h
	)

set(CORE_CARD_SRC
	src/core/card/card.cpp
	src/core/card/card.h
	)

set(CORE_SRC
	src/core/assets.cpp
	src/core/assets.h
	src/core/gameconfig.h
	src/core/ld36game.cpp
	src/core/ld36game.h
	src/core/textinputprocessor.cpp
	src/core/textinputprocessor.h
	)

set(CORE_SOURCES
	${CORE_SCENE_SRC}
	${CORE_SCREEN_SRC}
	${CORE_NETWORK_SRC}
	${CORE_COMMAND_SRC}
	${CORE_CARD_SRC}
	${CORE_SRC}
	)

# add a new target with allegro, alligator and core sources. uses monolith for win32
function(add_alleg_target EXEC-NAME SRCS)
	add_executable(${EXEC-NAME} ${CORE_SOURCES} ${ASTAR_SOURCES} ${SRCS})
	target_link_libraries(${EXEC-NAME} alligator)
	target_link_libraries(${EXEC-NAME} enet)
	target_include_directories(${EXEC-NAME} PUBLIC module/astarcpp/src)
	target_include_directories(${EXEC-NAME} PUBLIC module/enet/include)
	target_include_directories(${EXEC-NAME} PUBLIC module/alligator/src)
	set_target_properties(${EXEC-NAME} PROPERTIES
		COMPILE_FLAGS "-std=c++11"
		LINK_FLAGS "-g -ftest-coverage -fprofile-arcs"
		)
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

add_alleg_target(game
	src/game/game.cpp)

add_alleg_target(editor
	src/editor/editor.cpp)

add_alleg_target(server
	src/server/server.cpp
	src/server/server.h)




