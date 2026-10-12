#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>
#include <iphlpapi.h>
#include "lumi.h"
#include "lumi_functions.h"

#define MAX_TRIES 3
#define BASE_BUFFER_SIZE 15000

void getNetwork(LUMI* lumi){
    DWORD dwRetVal = 0;
    lumi->networkAdapterCount = 0;

    //This flag tells the API to reuturn list of IP address prefixes
    //This is an IP Prefix -> 192.168.0.1/24 (The last 24 means total of 256)
    ULONG flags = GAA_FLAG_INCLUDE_PREFIX;
    ULONG family = AF_UNSPEC; //Allows both IPv4 and IPv6 connections

    PIP_ADAPTER_ADDRESSES pAddresses = NULL;
    ULONG outBufLen = BASE_BUFFER_SIZE; //15KB buffer size
    ULONG Iterations = 0;

    do{
        pAddresses = (IP_ADAPTER_ADDRESSES*)malloc(outBufLen);
        if(pAddresses == NULL){
            printf("Memory allocation failed for IP_ADAPTER_ADDRESSES sturct\n");
            exit(1);
        }

        //populate struct with adapters' info
        dwRetVal = GetAdaptersAddresses(family, flags, NULL, pAddresses, &outBufLen);

        if(dwRetVal == ERROR_BUFFER_OVERFLOW){
            free(pAddresses);
            pAddresses = NULL;
        }
        //break the loop if adapters fetched successfully !
        else break;

        Iterations++;

    }while(dwRetVal == ERROR_BUFFER_OVERFLOW && Iterations < MAX_TRIES);
    /*
    retry loop only when GetAdaptersAddress causes a ERROR_BUFFER_OVERFLOW error and the number
    of iterations is less than max tries.

    Loop based heap alloc basically to prevent a race condition:
    A new connection is connected after memory allocation in that case the GetAdapterAddresses
    will return ERROR_BUFFER_OVERFLOW error, causing it to retry the alloc with bigger memory !

    outBufLen is written with the buffer size it needs !
    */

    PIP_ADAPTER_ADDRESSES pCurrAddresses = NULL;
    int connectedDeviceIdx = 0;

        if(dwRetVal == NO_ERROR){
        pCurrAddresses = pAddresses;
        while(pCurrAddresses){
            if((pCurrAddresses->OperStatus) == 1 && (pCurrAddresses->IfType != IF_TYPE_SOFTWARE_LOOPBACK)){

                //copy the name
                swprintf(
                    lumi->net_adapters[connectedDeviceIdx].networkAdapterName,
                    NETWORK_ADAPTER_NAME_SIZE, L"%ls",
                    pCurrAddresses->FriendlyName
                );
                //copy the description
                swprintf(
                    lumi->net_adapters[connectedDeviceIdx].networkAdapterDesc,
                    NETWORK_ADAPTER_DESC_SIZE, L"%ls",
                    pCurrAddresses->Description
                );

                lumi->networkAdapterCount++;
                connectedDeviceIdx++;
            }

            pCurrAddresses = pCurrAddresses->Next; //move to next node
        }
    }
    else{
        printf("Call to GetAdaptersAddresses failed with error: %lu\n", dwRetVal);
        if (dwRetVal == ERROR_NO_DATA)
            printf("No addresses were found for the requested parameters\n");
    }

    if(pAddresses) {
        free(pAddresses);
        pAddresses = NULL;
    }
}
