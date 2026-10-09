#pragma once
#ifndef LUMI_H
#define LUMI_H

#define __LUMI_VERSION "3.3"

#define OS_PRODUCT_NAME_SIZE 64
#define OS_BUILD_NUMBER_SIZE 32
#define OS_VERSION_SIZE 8
#define MAX_DISPLAY_COUNT 4
#define MAX_GPU_COUNT 4
#define GPU_NAME_SIZE 128
#define MAX_NETWORK_ADAPTER_COUNT 32
#define NETWORK_ADAPTER_NAME_SIZE 128
#define NETWORK_ADAPTER_DESC_SIZE 256

#include <wchar.h>

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

} networkAdapter;

typedef struct Windows_System_Information{

    char CPU[49];
    char CPU_Architecture[8];
    char OS_ProductName[OS_PRODUCT_NAME_SIZE];
    char OS_version[OS_VERSION_SIZE];
    char OS_buildNumber[OS_BUILD_NUMBER_SIZE];
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

    networkAdapter net_adapters[MAX_NETWORK_ADAPTER_COUNT];
    size_t networkAdapterCount;

} LUMI;

#endif
