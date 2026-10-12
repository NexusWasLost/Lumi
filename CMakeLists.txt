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
    ./src/disk.c
)

target_include_directories(lumi PRIVATE ./headers/)
target_link_libraries(lumi PRIVATE iphlpapi)

if(MSVC)
    target_compile_options(lumi PRIVATE \W4)
else()
    target_compile_options(lumi PRIVATE -Wall -Wextra)
endif()

# FLAGS: -ldxgi -ldxguid -lole32 -liphlpapi
# These flags will be needed while building any executable using lumi
