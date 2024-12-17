cmake_minimum_required(VERSION 3.30)
project(Dungeonns C)

set(CMAKE_C_STANDARD 11)

add_executable(Dungeonns main.c
        game.h
        file_io.h
        file_io.c
        game.c)
