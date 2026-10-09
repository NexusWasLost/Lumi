#include <windows.h>
#include "lumi.h"
#include "lumi_functions.h"

void getUptime(LUMI* lumi){
    lumi->uptime = GetTickCount64() / 1000ULL;
}
