#include <stdio.h>
#include <windows.h>
#include <dxgi.h>
#include "lumi.h"
#include "lumi_functions.h"

void getGPU(LUMI* lumi){
    IDXGIFactory1* factory = NULL;

    HRESULT result = CreateDXGIFactory1(&IID_IDXGIFactory1, (void**)&factory);
    if(FAILED(result)){
        printf("Unable to get GPU information...");
        return;
    }

    //create adapter pointer
    IDXGIAdapter1* adapter = NULL;
    UINT index = 0;
    lumi->gpuCount = 0;

    while(TRUE){
        if(lumi->gpuCount >= MAX_GPU_COUNT){
            printf("Warning: Maximum GPU limit (%d) reached. Skipping remaining GPU devices...\n", MAX_GPU_COUNT);
            return;
        }

        HRESULT hr = factory->lpVtbl->EnumAdapters1(factory, index, &adapter);

        //no more or any adapters found
        if(hr == DXGI_ERROR_NOT_FOUND) break;

        if(FAILED(hr)){
            printf("Failed to get GPU Information...");
            return;
        }

        DXGI_ADAPTER_DESC1 desc;
        adapter->lpVtbl->GetDesc1(adapter, &desc);
        // wprintf(L"GPU: %ls, VRAM: %llu MB\n", desc.Description, vram); //used for debugging

        //dont account for any software renderer GPU like VMWare and Microsoft renderer
        if(desc.Flags & DXGI_ADAPTER_FLAG_SOFTWARE){
            adapter->lpVtbl->Release(adapter);
            adapter = NULL;
            index++;
            continue;
        }

        //uses lumi->gpuCount as the index
        swprintf(
            lumi->gpu[lumi->gpuCount].GPU_Name,
            GPU_NAME_SIZE, L"%ls",
            desc.Description
        );
        lumi->gpu[lumi->gpuCount].totalVRAM = (desc.DedicatedVideoMemory / (1024ULL * 1024ULL));
        ++lumi->gpuCount;

        adapter->lpVtbl->Release(adapter);
        adapter = NULL;

        index++;
    }
}
