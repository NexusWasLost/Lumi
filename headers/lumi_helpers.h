#pragma once
#ifndef LUMI_HELPERS_H
#define LUMI_HELPERS_H

#include "lumi.h"

#ifdef __cplusplus
extern "C" {
#endif

/*
Convert MB to GB
*/
static double convertMBtoGB(double megabytes){
    return megabytes / 1024.0;
}

/*
Convert wide string (UTF16) to normal strings (UTF8)
*/
static size_t UTF16toUTF8(const wchar_t* wideString, char* buffer, size_t bufferlen){
    if(!wideString){
        printf("Failed to convert UTF16 string to UTF8 string: Wide String must be provided for conversion.\n");
        return 0;
    }

    //Passing 0 as the writing buffer size returns the size required
    int requiredBytes = WideCharToMultiByte(CP_UTF8, 0, wideString, -1, NULL, 0, NULL, NULL);

    if(requiredBytes == 0) return 0;
    if(!buffer){
        return (size_t)requiredBytes;
    }

    if(bufferlen == 0 || bufferlen > INT_MAX){
        printf("Failed to convert UTF16 string to UTF8 string: The buffer length is too large.\n");
        return 0;
    }

    //2nd pass
    int bytesWritten = WideCharToMultiByte(CP_UTF8, 0, wideString, -1, buffer, (int)bufferlen, NULL, NULL);
    if(bytesWritten == 0) return 0;

    return (size_t)bytesWritten;
}

#ifdef __cplusplus
}
#endif

#endif
