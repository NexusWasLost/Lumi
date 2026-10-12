#include <windows.h>
#include <stdio.h>
#include "lumi.h"
#include "lumi_functions.h"

void getDisplay(LUMI* lumi){
    lumi->displayCount = 0;

    for(DWORD x = 0; ; x++){
        DISPLAY_DEVICE disp = { 0 };
        disp.cb = sizeof(disp);
        if (!EnumDisplayDevices(NULL, x, &disp, 0)) break;

        // Skip inactive and mirroring devices
        if (!(disp.StateFlags & DISPLAY_DEVICE_ACTIVE)) continue;
        if (disp.StateFlags & DISPLAY_DEVICE_MIRRORING_DRIVER) continue;

        if(lumi->displayCount >= MAX_DISPLAY_COUNT){
            printf("Warning: Maximum display limit (%d) reached. Skipped remaining displays.\n", MAX_DISPLAY_COUNT);
            return;
        }

        DEVMODE devmode = { 0 };
        devmode.dmSize = sizeof(DEVMODE);
        if (EnumDisplaySettings(disp.DeviceName, ENUM_CURRENT_SETTINGS, &devmode)){
            //access each elements of the lumi->monitor for the lumi->displayCount index;
            lumi->monitors[lumi->displayCount].height = devmode.dmPelsHeight;
            lumi->monitors[lumi->displayCount].width = devmode.dmPelsWidth;
            lumi->monitors[lumi->displayCount].refreshRate = devmode.dmDisplayFrequency;
            lumi->displayCount++;
        }
    }
}
