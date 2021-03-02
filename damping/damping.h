#ifndef __DAMPING_H__
#define __DAMPING_H__

typedef struct 
{
	int32_t step_up;		/*正步进*/
	int32_t step_down;		/*负步进*/
	int32_t dead_up;		/*正死区*/
	int32_t dead_down;		/*负死区*/
	int32_t border_up;		/*上限*/
	int32_t border_down;	/*下限*/
	int32_t	init_value;		/*初始值*/
}DampingConfig_t;

typedef struct 
{
	DampingConfig_t * cfg;
	int32_t	display;	/*当前结算值*/
}DampingRuntime_t;

void DampingRegister(DampingRuntime_t *runtime, DampingConfig_t *cfg);
int32_t DampingProcess(DampingRuntime_t *runtime, int32_t value);
int32_t DampingGetDisplay(DampingRuntime_t *runtime);

void DampingSetDisplay(DampingRuntime_t *runtime, int32_t value);
void DampingSetStep(DampingRuntime_t *runtime, int32_t step_up, int32_t step_down);
void DampingSetDead(DampingRuntime_t *runtime, int32_t dead_up, int32_t dead_down);
void DampingSetBorder(DampingRuntime_t *runtime, int32_t border_up, int32_t border_down);

#endif