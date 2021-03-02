#include "mid_progressbar.h"

const uint32_t fuel_rising_boundary[] = {   11, 23, 35, 48, 60, 73, 85, 98};
const uint32_t fuel_falling_boundary[]= {6, 14, 27, 39, 52, 64, 77, 89    };

const PROGRESS_BAR_CFG_T fuel_bar_config =
{
	.bar_max 			= 8,
	.init_boundary		= BAR_IS_FALLING,
	.bar_rising_boudary	= fuel_rising_boundary,
	.bar_falling_boudary= fuel_falling_boundary
};

PROGRESS_BAR_RUNTIME_T fuel_bar_runtime;

PROGRESS_BAR_RUNTIME_T * FuelBarRuntime(void)
{
	return &fuel_bar_runtime;
}

/*
	ABNORMAL || BORDER || NORMAL || BORDER || ABNORMAL
		  =6.5v=>    ==9v=>    =16.5v=>  =18.5v=>
		   <=6v==   <=8.5v=    <=16v==   <=18v==
*/
const uint32_t battery_rising_boundary[] = {65, 90, 165, 185};
const uint32_t battery_falling_boundary[]= {60, 85, 160, 180};

const PROGRESS_BAR_CFG_T battery_bar_config =
{
	.bar_max 			= 4,
	.init_boundary		= BAR_IS_FALLING,
	.bar_rising_boudary	= battery_rising_boundary,
	.bar_falling_boudary= battery_falling_boundary
};

PROGRESS_BAR_RUNTIME_T battery_bar_runtime;

PROGRESS_BAR_RUNTIME_T * BatteryBarRuntime(void)
{
	return &battery_bar_runtime;
}


void ProgressBarInit(void)
{
	ProgressBarRegister(&fuel_bar_runtime, &fuel_bar_config);
	ProgressBarRegister(&battery_bar_runtime, &battery_bar_config);

}


