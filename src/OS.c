#include <stdio.h>
#include <windows.h>
#include <string.h>
#include "lumi.h"
#include "lumi_functions.h"

void setOSProductName(int majorBuildNumber, LUMI* lumi, char* productName){
    if(majorBuildNumber >= 22000){
        //The string "Windows 11" is total 10 chars + 1 char ('\0') and we store it in an array.
        //Copy the 11 bytes and the last one 10th index is '\0'.
        //The 10th index in the productName array is the space after major windows number and we overwrite previous null terminator and continue to append from the space.
        char win11[11] = "Windows 11";
        strncpy(lumi->OS_ProductName, win11, 11);
        strncpy(lumi->OS_ProductName + 10, productName + 10, OS_PRODUCT_NAME_SIZE - 10);
    }
    else{
        strncpy(lumi->OS_ProductName, productName, OS_PRODUCT_NAME_SIZE);
    }
}

void setOSVersion(LUMI* lumi, char* versionNumber){
    strncpy(lumi->OS_Version, versionNumber, OS_VERSION_SIZE);
}

void setOSBuildNumber(LUMI* lumi, char* buildNumber){
    strncpy(lumi->OS_BuildNumber, buildNumber, OS_BUILD_NUMBER_SIZE);
}

void getOS(LUMI* lumi){
    HKEY hkey;
    char productName[64];
    char buildNumber[32];
    char versionNumber[8];

    DWORD productSize = sizeof(productName);
    DWORD buildSize = sizeof(buildNumber);
    DWORD versionSize = sizeof(versionNumber);

    //open registry key
    LONG stat = RegOpenKeyExA(
        HKEY_LOCAL_MACHINE,
        "SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion",
        0,
        KEY_READ,
        &hkey
    );

    if(stat != ERROR_SUCCESS){
        printf("Error Getting OS Info...");
        return;
    }

    //query product name
    stat = RegQueryValueExA(
        hkey,
        "ProductName",
        NULL,
        NULL,
        (LPBYTE)productName,
        &productSize
    );

    if(stat != ERROR_SUCCESS){
        printf("Error Getting Product Name...");
        RegCloseKey(hkey);
        return;
    }

    //query version number
    stat = RegQueryValueExA(
        hkey,
        "DisplayVersion",
        NULL,
        NULL,
        (LPBYTE)versionNumber,
        &versionSize
    );

    if(stat != ERROR_SUCCESS){
        //query using an older value for older windows
        LONG nested_stat = RegQueryValueExA(
            hkey,
            "ReleaseId",
            NULL,
            NULL,
            (LPBYTE)versionNumber,
            &versionSize
        );

        if (nested_stat != ERROR_SUCCESS) {
            printf("Error Getting OS version...");
            RegCloseKey(hkey);
            return;
        }

    }

    //query build number
    stat = RegQueryValueExA(
        hkey,
        "CurrentBuild",
        NULL,
        NULL,
        (LPBYTE)buildNumber,
        &buildSize
    );

    if(stat != ERROR_SUCCESS){
        printf("Error Getting Product Name...");
        RegCloseKey(hkey);
        return;
    }

    //check major build for windows 11
    int major = atoi(buildNumber);
    setOSProductName(major, lumi, productName);
    setOSVersion(lumi, versionNumber);
    setOSBuildNumber(lumi, buildNumber);

    lumi->OS_ProductName[63] = '\0';
    lumi->OS_BuildNumber[31] = '\0';
    lumi->OS_Version[7] = '\0';

    RegCloseKey(hkey);
}
