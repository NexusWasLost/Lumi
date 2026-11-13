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
static void UTF16toUTF8(const wchar_t* wideString, char* buffer, size_t bufferlen){
    if(!wideString || !buffer){
        printf("Failed to convert UTF16 string to UTF8 string: Wide String and character buffer must be provided for conversion.\n");
        return;
    }

    if(bufferlen == 0 || bufferlen > INT_MAX){
        printf("Failed to convert UTF16 string to UTF8 string: The buffer length is too large.\n");
    }

    int bytesWritten = WideCharToMultiByte(CP_UTF8, 0, wideString, -1, buffer, (int)bufferlen, NULL, NULL);
    if(bytesWritten == 0){
        DWORD err = GetLastError();
        switch(err){
            case ERROR_INSUFFICIENT_BUFFER:
                printf("Failed to convert UTF16 string to UTF8 string: Insufficient buffer size.\n");
                break;

            case ERROR_INVALID_PARAMETER:
                printf("Failed to convert UTF16 string to UTF8 string: Invalid params, check what is passed to the function.\n");
                break;

            case ERROR_NO_UNICODE_TRANSLATION:
                printf("Failed to convert UTF16 string to UTF8 string: No Unicode translation found.\n");
                break;

            default:
                printf("Failed to convert UTF16 string to UTF8 string.\n");
                break;
        }
    }
}

#ifdef __cplusplus
}
#endif

#endif
