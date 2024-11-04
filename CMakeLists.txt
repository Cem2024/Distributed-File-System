cmake_minimum_required(VERSION 3.29)
project(Distributed_File_System C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(Distributed_File_System
        Metadata_Server.c
        "Client.c")

