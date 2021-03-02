#ifndef __INTERPOLATION_H__
#define __INTERPOLATION_H__

#define ARR_X_ASCENDING		0
#define ARR_X_DESCENDING	1

typedef struct 
{
	uint8_t			array_order;  //x数组升序or降序
	uint16_t		array_size;
	const int32_t	*array_x;  //array_x和array_y元素个数必须相同
	const int32_t	*array_y;	//array_x和array_y元素个数必须相同
}InterpolationCfg_t;

typedef struct 
{
	const InterpolationCfg_t *cfg;

}InterpolationRuntime_t;

void InterpolationRegister(InterpolationRuntime_t *runtime, InterpolationCfg_t *cfg);
int32_t InterpolationGetValueY(InterpolationRuntime_t *runtime, int32_t value_x);
#endif