#include <windows.h>
#include <stdio.h>
#include "lumi.h"
#include "lumi_functions.h"

BOOL getDriveInfo(
    LPCWSTR currentDriveLabel,
    LPWSTR volumeName,
    DWORD volumeNameSize,
    LPWSTR fileSystemName,
    DWORD fileSystemNameSize,
    PULARGE_INTEGER freeBytes,
    PULARGE_INTEGER totalBytes
){

    if(!GetVolumeInformationW(
        currentDriveLabel,
        volumeName,
        volumeNameSize,
        NULL, NULL, NULL,
        fileSystemName,
        fileSystemNameSize
    )) return 0;

    if(!GetDiskFreeSpaceExW(
        currentDriveLabel,
        NULL, totalBytes, freeBytes
    )) return 0;

    return 1;
}

void printDriveSpace(unsigned long long freeBytes, unsigned long long totalBytes) {
    double freeGB = (double)freeBytes / (1024.0 * 1024.0 * 1024.0);
    double totalGB = (double)totalBytes / (1024.0 * 1024.0 * 1024.0);

    printf("%.2f GB Free / %.2f GB Total\n", freeGB, totalGB);
}

void getDisk(LUMI* lumi){
    lumi->diskCount = 0;
    wchar_t volumeList[MAX_PATH + 1];

    if(!GetLogicalDriveStringsW(
        sizeof(volumeList) / sizeof(volumeList[0]), volumeList
    )){
        printf("Failed to get disk count..");
        return;
    }

    /*
    Filled buffer looks something like this (each char is 2 bytes)
    ['C', ':', '\', '\0', 'D', ':', '\', '\0', '\0']
    */

    wchar_t* bufPtr = &volumeList[0]; //pointer pointing to the start of the list
    wchar_t volumeName[MAX_PATH + 1]; //buffer for storing each volume name
    wchar_t fileSystemName[32]; //buffer for storing the file system name for each volume
    wchar_t currentDriveLabel[16]; //buffer for storing the current drive label

    int index = 0;
    ULARGE_INTEGER freeBytes, totalBytes;

    while(*bufPtr != L'\0'){
        //reset all variables and buffers
        index = 0;
        freeBytes.QuadPart = 0;
        totalBytes.QuadPart = 0;
        wmemset(volumeName, L'\0', MAX_PATH + 1);
        wmemset(fileSystemName, L'\0', 32);
        wmemset(currentDriveLabel, L'\0', 16);

        while(*bufPtr != L'\0'){
            currentDriveLabel[index] = *bufPtr; //store each character of the drive label
            bufPtr++; //increment the pointer to access the next character
            index++;
        }

        //get Drive Info and Drive Space info
        if(!getDriveInfo(
            currentDriveLabel,
            volumeName,
            sizeof(volumeName) / sizeof(volumeName[0]),
            fileSystemName,
            sizeof(fileSystemName) / sizeof(fileSystemName[0]),
            &freeBytes, &totalBytes
        )){
            printf("Failed to retrieve file system info...\n");
            bufPtr++; //increment buffer again if it lands on \0 means end of buffer
            continue;
        }
        bufPtr++;
        lumi->diskCount++;

        printf("Drive Name: %ls\n", currentDriveLabel);
        printf("FileSystem: %ls\n", fileSystemName);
        printf("Space on Disk %ls: ", currentDriveLabel);
        printDriveSpace(freeBytes.QuadPart, totalBytes.QuadPart);
    }
}
