cmake_minimum_required(VERSION 3.28)
project(laborator_2_4 C)

set(CMAKE_C_STANDARD 11)

add_executable(laborator_2_4 main.c
        domain.h
        domain.c
        repo.h
        repo.c
        service.h
        service.c)
