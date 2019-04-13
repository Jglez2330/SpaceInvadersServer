cmake_minimum_required(VERSION 3.13)
project(SpaceInvadersServer C)

set(CMAKE_C_STANDARD 11)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/CMAKE")

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake")


find_package(SDL2 REQUIRED)

add_executable(SpaceInvadersServer main.c Socket.c Socket.h Server.c Server.h invader.c invader.h linkedList.c linkedList.h Proyectiles.c Proyectiles.h ObjetosJuego.c ObjetosJuego.h Barreras.c Barreras.h Clientes.h JSON/cJSON.c JSON/cJSON.h JSON/JsonHandler.c JSON/JsonHandler.h Logica/Jugadores.c Logica/Jugadores.h)

include_directories(${SDL2_INCLUDE_DIR} ${SDL2TTF_INCLUDE_DIR} ${SDL2_IMAGE_INCLUDE_DIR} ${SDL2Mixer_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARY} ${SDL2TTF_LIBRARY} ${SDL2_IMAGE_LIBRARY} ${SDL2Mixer_LIBRARY})


