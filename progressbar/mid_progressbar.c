#include "mid_progressbar.h"

void ProgressBarRegister(PROGRESS_BAR_RUNTIME_T *runtime, PROGRESS_BAR_CFG_T *config)
{
	// configASSERT(runtime && config);
	runtime->config 		= config;
	runtime->bar_derection 	= config->init_boundary;
	if(config->init_boundary == BAR_IS_FALLING)
		runtime->bar_current 	= config->bar_max -1;
	else
		runtime->bar_current 	= 0;
}

void ProgressBarDataUpdate(PROGRESS_BAR_RUNTIME_T *runtime, uint32_t input_data)
{
	uint8_t i = 0;

	/*上升时边界值判定*/
	if(runtime->bar_derection == BAR_IS_RISING)
	{
		for(i = 0; i < runtime->config->bar_max; i++)
		{
			if(input_data < runtime->config->bar_rising_boudary[i])
			{
				if(i > runtime->bar_current)
				{
					runtime->bar_current = i;
				}
				break;			
			}
		}

		if(input_data >= runtime->config->bar_rising_boudary[runtime->config->bar_max-1])
			runtime->bar_current = runtime->config->bar_max;
	}

	/*下降时边界值判定*/
	if(runtime->bar_derection == BAR_IS_FALLING)
	{
		for(i = 0; i < runtime->config->bar_max; i++)
		{
			if(input_data < runtime->config->bar_falling_boudary[i])
			{
				if(i < runtime->bar_current)
				{
					runtime->bar_current = i;	
				}
				break;		
			}
		}

		if(input_data >= runtime->config->bar_falling_boudary[runtime->config->bar_max-1])
			runtime->bar_current = runtime->config->bar_max;
	}	

	/*上升时数据突然下降超过阈值方向改为下降*/
	if(runtime->bar_derection == BAR_IS_RISING)
	{
		if( (runtime->bar_current > 0) && \
			(input_data < runtime->config->bar_falling_boudary[runtime->bar_current-1]) )
		{
			runtime->bar_derection = BAR_IS_FALLING;
		}
	}

	/*下降时数据突然上升超过阈值方向改为上升*/
	if(runtime->bar_derection == BAR_IS_FALLING)
	{
		if( (runtime->bar_current < runtime->config->bar_max) && \
			(input_data > runtime->config->bar_rising_boudary[runtime->bar_current]) )
		{
			runtime->bar_derection = BAR_IS_RISING;
		}
	}	
}

uint32_t ProgressBarDataGet(PROGRESS_BAR_RUNTIME_T *runtime)
{
	return runtime->bar_current;
}