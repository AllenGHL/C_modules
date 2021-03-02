#include "interpolation.h"
#include "interpolation_cfg.h"
/*========================<sample1>============================*/
//array_x和array_y元素个数必须相同
const int32_t	sample1_array_x[] = {-20,	-10,   0, 	   20, 		50, 	 60};
const int32_t	sample1_array_y[] = {1, 	100, 1000, 	10000, 	100000, 1000000};

InterpolationCfg_t sample1_interpolation_cfg = 
{
	.array_order= ARR_X_ASCENDING,
	.array_size = sizeof(sample1_array_x)/sizeof(sample1_array_x[0]),
	.array_x 	= sample1_array_x,	//array_x和array_y元素个数必须相同
	.array_y 	= sample1_array_y,

};

InterpolationRuntime_t sample1_interpolation_runtime;

InterpolationRuntime_t * Sample1InterpolatonHandle(void)
{
	return &sample1_interpolation_runtime;
}


/*========================<sample2>============================*/
//array_x和array_y元素个数必须相同
const int32_t	sample2_array_x[] = {60,	50,   40, 	   30, 		20, 	 10};
const int32_t	sample2_array_y[] = {1, 	100, 1000, 	10000, 	100000, 1000000};

InterpolationCfg_t sample2_interpolation_cfg = 
{
	.array_order= ARR_X_DESCENDING,
	.array_size = sizeof(sample2_array_x)/sizeof(sample2_array_x[0]),
	.array_x 	= sample2_array_x,	//array_x和array_y元素个数必须相同
	.array_y 	= sample2_array_y,

};

InterpolationRuntime_t sample2_interpolation_runtime;

InterpolationRuntime_t * Sample2InterpolatonHandle(void)
{
	return &sample2_interpolation_runtime;
}


void InterpolationInit(void)
{
	InterpolationRegister(Sample1InterpolatonHandle(), &sample1_interpolation_cfg);
	InterpolationRegister(Sample2InterpolatonHandle(), &sample2_interpolation_cfg);
}

