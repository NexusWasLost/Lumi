#pragma once
#ifndef LUMI_H
#define LUMI_H

#define LUMI_VERSION_MAJOR 4
#define LUMI_VERSION_MINOR 0
#define LUMI_VERSION_PATCH 0
#define LUMI_VERSION_STRING "4.0.0"

#define OS_PRODUCT_NAME_SIZE 64
#define OS_BUILD_NUMBER_SIZE 32
#define OS_VERSION_SIZE 8
#define MAX_DISPLAY_COUNT 6
#define MAX_GPU_COUNT 4
#define GPU_NAME_SIZE 128
#define MAX_NETWORK_ADAPTER_COUNT 32
#define NETWORK_ADAPTER_NAME_SIZE 128
#define NETWORK_ADAPTER_DESC_SIZE 256
#define MAX_DISK_COUNT 32
#define DISK_FS_NAME_SIZE 16

#include <wchar.h>
#include <windows.h>

typedef struct Display_Monitors{

    int width;
    int height;
    int refreshRate;

} Display;

typedef struct Graphics_Adapters{

    wchar_t GPU_Name[GPU_NAME_SIZE];
    unsigned long long totalVRAM;

} GPU;

typedef struct Network_Adapters{

    wchar_t networkAdapterName[NETWORK_ADAPTER_NAME_SIZE];
    wchar_t networkAdapterDesc[NETWORK_ADAPTER_DESC_SIZE];

} NetworkAdapter;

typedef struct Disks{

    wchar_t volumeLabel[MAX_PATH + 1];
    wchar_t fileSystemName[DISK_FS_NAME_SIZE];
    wchar_t diskLetter;
    double freeSpace;
    double usedSpace;
    double totalSpace;

} Disk;

typedef struct Lumi_Windows_System_Information{

    char CPU[49];
    char CPU_Architecture[8];
    char OS_ProductName[OS_PRODUCT_NAME_SIZE];
    char OS_Version[OS_VERSION_SIZE];
    char OS_BuildNumber[OS_BUILD_NUMBER_SIZE];
    char host[16];
    wchar_t locale[16];
    char currentUserName[32];

    unsigned long long totalMemory;
    unsigned long long availableMemory;
    unsigned long long usedMemory;
    unsigned long long memoryLoad;
    unsigned long long uptime;

    GPU gpu[MAX_GPU_COUNT];
    size_t gpuCount;

    Display monitors[MAX_DISPLAY_COUNT];
    size_t displayCount;

    NetworkAdapter net_Adapters[MAX_NETWORK_ADAPTER_COUNT];
    size_t networkAdapterCount;

    Disk disks[MAX_DISK_COUNT];
    size_t diskCount;

} LUMI;

#endif
