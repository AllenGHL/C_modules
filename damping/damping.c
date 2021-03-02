#include "damping.h"

#define DAPMING_UP		0
#define DAPMING_DOWN	1

#define ENABLE_DAMPING_PARAMETER_CHECK

static void DampingParameterCheck(DampingRuntime_t *runtime)
{
	#ifdef ENABLE_DAMPING_PARAMETER_CHECK
	if(runtime->cfg->step_up <= 0)
		printf("\n\ndamping parameter error!!!: step_up <= 0\n\n");
	if(runtime->cfg->dead_up <= 0)
		printf("\n\ndamping parameter error!!!: dead_up <= 0\n\n");
	if(runtime->cfg->step_down >= 0)
		printf("\n\ndamping parameter error!!!: step_down >= 0\n\n");
	if(runtime->cfg->dead_down >= 0)
		printf("\n\ndamping parameter error!!!: dead_down >= 0\n\n");	
	if(runtime->cfg->border_up < runtime->cfg->border_down)
		printf("\n\ndamping parameter error!!!: border_up < border_down\n\n");		
	#endif
}

void DampingRegister(DampingRuntime_t *runtime, DampingConfig_t *cfg)
{
	runtime->cfg = cfg;
	runtime->display = cfg->init_value;
	DampingParameterCheck(runtime);
}

int32_t DampingProcess(DampingRuntime_t *runtime, int32_t value)
{
	if(value != runtime->display)
	{
		if(value > runtime->display)
		{
			if( (value-runtime->display) > runtime->cfg->dead_up )
			{
				runtime->display += runtime->cfg->step_up;
			}
			else // 目标值是边界值时即使小于死区也要更新
			{
				if(value == runtime->cfg->border_up)
				{
					runtime->display += runtime->cfg->step_up;
				}
			}

			if(runtime->display > runtime->cfg->border_up)
			{
				runtime->display = runtime->cfg->border_up;
			}
		}
		else
		{
			if( (value-runtime->display) < runtime->cfg->dead_down )
			{
				runtime->display += runtime->cfg->step_down;
			}
			else // 目标值是边界值时即使小于死区也要更新
			{
				if(value == runtime->cfg->border_down)
				{
					runtime->display += runtime->cfg->step_down;
				}
			}
			
			if(runtime->display < runtime->cfg->border_down)
			{
				runtime->display = runtime->cfg->border_down;
			}			
		}

	}

	return runtime->display;	
}

int32_t DampingGetDisplay(DampingRuntime_t *runtime)
{
	return runtime->display;
}

void DampingSetDisplay(DampingRuntime_t *runtime, int32_t value)
{
	runtime->display = value;
}

void DampingSetStep(DampingRuntime_t *runtime, int32_t step_up, int32_t step_down)
{
	runtime->cfg->step_up = step_up;
	runtime->cfg->step_down = step_down;
	DampingParameterCheck(runtime);
}

void DampingSetDead(DampingRuntime_t *runtime, int32_t dead_up, int32_t dead_down)
{
	runtime->cfg->dead_up = dead_up;
	runtime->cfg->dead_down = dead_down;
	DampingParameterCheck(runtime);
}

void DampingSetBorder(DampingRuntime_t *runtime, int32_t border_up, int32_t border_down)
{
	runtime->cfg->border_up = border_up;
	runtime->cfg->border_down = border_down;
	DampingParameterCheck(runtime);
}
