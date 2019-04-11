cmake_minimum_required(VERSION 3.13)
project(SpaceInvadersServer C)

set(CMAKE_C_STANDARD 11)

add_executable(SpaceInvadersServer main.c Socket.c Socket.h Server.c Server.h)