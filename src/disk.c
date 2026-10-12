#include <windows.h>
#include <stdio.h>
#include <math.h>
#include "lumi.h"
#include "lumi_functions.h"

BOOL getDriveInfo(
    LPCWSTR currentVolumePath,
    LPWSTR volumeName,
    DWORD volumeNameSize,
    LPWSTR fileSystemName,
    DWORD fileSystemNameSize,
    PULARGE_INTEGER freeBytes,
    PULARGE_INTEGER totalBytes
){

    if(!GetVolumeInformationW(
        currentVolumePath,
        volumeName,
        volumeNameSize,
        NULL, NULL, NULL,
        fileSystemName,
        fileSystemNameSize
    )) return 0;

    if(!GetDiskFreeSpaceExW(
        currentVolumePath,
        NULL, totalBytes, freeBytes
    )) return 0;

    return 1;
}

void storeSpaces(LUMI* lumi, PULARGE_INTEGER freeBytes, PULARGE_INTEGER totalBytes){
    // Calculate used space in bytes first
    unsigned long long usedBytes = totalBytes->QuadPart - freeBytes->QuadPart;

    // Convert to Megabytes (MB) using binary divisor (1024 * 1024)
    double freeMB = (double)(freeBytes->QuadPart) / (1024.0 * 1024.0);
    double totalMB = (double)(totalBytes->QuadPart) / (1024.0 * 1024.0);
    double usedMB = (double)(usedBytes) / (1024.0 * 1024.0);

    lumi->disks[lumi->diskCount].freeSpace = round(freeMB * 100) / 100;
    lumi->disks[lumi->diskCount].usedSpace = round(usedMB * 100) / 100;
    lumi->disks[lumi->diskCount].totalSpace = round(totalMB * 100) / 100;
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
    wchar_t fileSystemName[16]; //buffer for storing the file system name for each volume
    wchar_t currentVolumePath[16]; //buffer for storing the current drive label

    int index = 0;
    ULARGE_INTEGER freeBytes, totalBytes;

    while(*bufPtr != L'\0'){
        //reset all variables and buffers
        index = 0;
        freeBytes.QuadPart = 0;
        totalBytes.QuadPart = 0;
        wmemset(volumeName, L'\0', MAX_PATH + 1);
        wmemset(fileSystemName, L'\0', 32);
        wmemset(currentVolumePath, L'\0', 16);

        while(*bufPtr != L'\0'){
            currentVolumePath[index] = *bufPtr; //store each character of the drive label
            bufPtr++; //increment the pointer to access the next character
            index++;
        }

        //get Drive Info and Drive Space info
        if(!getDriveInfo(
            currentVolumePath,
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

        if(volumeName[0] == L'\0'){
            //Drives like C:\ have no label so copy wstring "No Label" to volumeName buffer
            wcscpy_s(volumeName, MAX_PATH + 1, L"No Label");
        }

        lumi->disks[lumi->diskCount].driveLetter = currentVolumePath[0];
        //store the volume name
        swprintf(
            lumi->disks[lumi->diskCount].volumeLabel,
            MAX_PATH + 1, L"%ls",
            volumeName
        );
        //store the file system name
        swprintf(
            lumi->disks[lumi->diskCount].fileSystemName,
            DISK_FS_NAME_SIZE, L"%ls",
            fileSystemName
        );
        //store spaces
        storeSpaces(lumi, &freeBytes, &totalBytes);
        lumi->diskCount++;
    }
}
