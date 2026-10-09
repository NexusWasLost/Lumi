#pragma once
#ifndef LUMI_FUNCTIONS_H
#define LUMI_FUNCTIONS_H

#include "lumi.h"

#ifdef __cplusplus
extern "C" {
#endif

void getMemory(LUMI* lumi);
void getCPU(LUMI* lumi);
void getGPU(LUMI* lumi);
void getOS(LUMI* lumi);
void getDisplay(LUMI* lumi);
void getCurrentUsername(LUMI* lumi);
void getHostName(LUMI* lumi);
void getUptime(LUMI* lumi);
void getKernelUptime(LUMI* lumi);
void getLocale(LUMI* lumi);
void getNetwork(LUMI* lumi);

#ifdef __cplusplus
}
#endif

#endif
