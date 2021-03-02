#include "hysteresis.h"

void HysteresisRegister(HysteresisRuntime_t *runtime, HysteresisCfg_t *config)
{
	// configASSERT(runtime && config);
	runtime->config 		= config;
	runtime->section_derection 	= config->init_boundary;
	if(config->init_boundary == SECTION_FALLING)
		runtime->section_current 	= config->section_max -1;
	else
		runtime->section_current 	= 0;
}

void HysteresisDataUpdate(HysteresisRuntime_t *runtime, uint32_t input_data)
{
	uint8_t i = 0;

	/*上升时边界值判定*/
	if(runtime->section_derection == SECTION_RISING)
	{
		for(i = 0; i < runtime->config->section_max; i++)
		{
			if(input_data < runtime->config->section_rising_boudary[i])
			{
				if(i > runtime->section_current)
				{
					runtime->section_current = i;
				}
				break;			
			}
		}

		if(input_data >= runtime->config->section_rising_boudary[runtime->config->section_max-1])
			runtime->section_current = runtime->config->section_max;
	}

	/*下降时边界值判定*/
	if(runtime->section_derection == SECTION_FALLING)
	{
		for(i = 0; i < runtime->config->section_max; i++)
		{
			if(input_data < runtime->config->section_falling_boudary[i])
			{
				if(i < runtime->section_current)
				{
					runtime->section_current = i;	
				}
				break;		
			}
		}

		if(input_data >= runtime->config->section_falling_boudary[runtime->config->section_max-1])
			runtime->section_current = runtime->config->section_max;
	}	

	/*上升时数据突然下降超过阈值方向改为下降*/
	if(runtime->section_derection == SECTION_RISING)
	{
		if( (runtime->section_current > 0) && \
			(input_data < runtime->config->section_falling_boudary[runtime->section_current-1]) )
		{
			runtime->section_derection = SECTION_FALLING;
		}
	}

	/*下降时数据突然上升超过阈值方向改为上升*/
	if(runtime->section_derection == SECTION_FALLING)
	{
		if( (runtime->section_current < runtime->config->section_max) && \
			(input_data > runtime->config->section_rising_boudary[runtime->section_current]) )
		{
			runtime->section_derection = SECTION_RISING;
		}
	}	
}

uint32_t HysteresisDataGet(HysteresisRuntime_t *runtime)
{
	return runtime->section_current;
}