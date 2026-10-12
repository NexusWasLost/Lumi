#include <windows.h>
#include "lumi.h"
#include "lumi_functions.h"

void getDisplay(LUMI* lumi){
    lumi->displayCount = 0;
    DISPLAY_DEVICE disp = { 0 };

    disp.cb = sizeof(disp);

    for(DWORD x = 0; x < MAX_DISPLAY_COUNT; x++){
        if (!EnumDisplayDevices(NULL, x, &disp, 0)) break;

        // Skip inactive devices
        if (!(disp.StateFlags & DISPLAY_DEVICE_ACTIVE)) continue;

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
