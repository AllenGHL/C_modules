#ifndef __PROGRESSBAR_H__
#define __PROGRESSBAR_H__

#include "mid_progressbar.h"

void ProgressBarInit(void);
PROGRESS_BAR_RUNTIME_T * FuelBarRuntime(void);
PROGRESS_BAR_RUNTIME_T * BatteryBarRuntime(void);
#endif