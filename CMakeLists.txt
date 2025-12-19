cmake_minimum_required(VERSION 4.0)
project(untitled C)

set(CMAKE_C_STANDARD 99)

add_executable(psop main.c
        vehicle_menu.c
        vehicle_menu.h
        vehicle.h
        vehicle.c
        parking.h
        parking.c
        input_utils.h
        input_utils.c)
