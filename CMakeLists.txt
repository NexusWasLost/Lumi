cmake_minimum_required(VERSION 4.0)
project(lumi)

add_library(lumi STATIC
    ./src/cpu.c
    ./src/display.c
    ./src/gpu.c
    ./src/hostname.c
    ./src/locale.c
    ./src/memory.c
    ./src/OS.c
    ./src/uptime.c
    ./src/username.c
    ./src/network.c
)

target_include_directories(lumi PRIVATE ./headers/)

# FLAGS: -ldxgi -ldxguid -lole32 -liphlpapi
# These flags will be needed while building any executable using lumi
