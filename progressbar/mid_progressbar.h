#ifndef __MID_PROGRESSBAR_H__
#define __MID_PROGRESSBAR_H__

#include "main.h"

#define BAR_IS_RISING	0
#define BAR_IS_FALLING	1



typedef struct
{
	uint8_t bar_max;						/*进度条数目*/
	uint8_t init_boundary;					/*首次数据无法判定上升还是下降时，判定显示进度条格数依据*/
	const uint32_t *bar_rising_boudary; 	/*上涨分界线*/
	const uint32_t *bar_falling_boudary; 	/*下降分界线*/
	
}PROGRESS_BAR_CFG_T;

typedef struct
{
	const PROGRESS_BAR_CFG_T *config;
	uint8_t bar_current;
	uint8_t bar_derection;

}PROGRESS_BAR_RUNTIME_T;

void ProgressBarRegister(PROGRESS_BAR_RUNTIME_T *runtime, PROGRESS_BAR_CFG_T *config);
void ProgressBarDataUpdate(PROGRESS_BAR_RUNTIME_T *runtime, uint32_t input_data);
uint32_t ProgressBarDataGet(PROGRESS_BAR_RUNTIME_T *runtime);

#endif