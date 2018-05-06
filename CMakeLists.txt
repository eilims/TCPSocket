cmake_minimum_required(VERSION 3.10)
project(TCPSocket C)

set(CMAKE_C_STANDARD 99)

add_executable(TCPSocket main.c Server.c Server.h headerFiles.h Client.c Client.h)