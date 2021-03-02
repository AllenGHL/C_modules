#include "interpolation.h"
#include "interpolation_cfg.h"

void InterpolationRegister(InterpolationRuntime_t *runtime, InterpolationCfg_t *cfg)
{
	runtime->cfg 	= cfg;
}

static int32_t GetYi(int32_t xi, int32_t x0, int32_t x1, int32_t y0, int32_t y1)
{
	//ASSERT(x0 != x1);
	return (int32_t)(y0 + (xi - x0)*(y1 - y0)/(x1 - x0));
}

int32_t InterpolationGetValueY(InterpolationRuntime_t *runtime, int32_t value_x)
{
	int32_t rtn;
	uint16_t i, arr_max = runtime->cfg->array_size;

	if(ARR_X_ASCENDING == runtime->cfg->array_order) 
	{
		/*边界检查*/
		if(value_x < runtime->cfg->array_x[0])
			rtn = runtime->cfg->array_y[0];
		else if(value_x >= runtime->cfg->array_x[arr_max-1])
			rtn = runtime->cfg->array_y[arr_max-1];
		else
		{
			for(i = 0; i < arr_max; i++)
			{
				if(value_x < runtime->cfg->array_x[i])
				{
					rtn = GetYi(value_x, \
						runtime->cfg->array_x[i-1],\
						runtime->cfg->array_x[i],\
						runtime->cfg->array_y[i-1],\
						runtime->cfg->array_y[i]);
					break;
				}
			}
		}
		
	}

	if(ARR_X_DESCENDING == runtime->cfg->array_order) 
	{
		/*边界检查*/
		if(value_x > runtime->cfg->array_x[0])
			rtn = runtime->cfg->array_y[0];
		else if(value_x <= runtime->cfg->array_x[arr_max-1])
			rtn = runtime->cfg->array_y[arr_max-1];
		else
		{
			for(i = 0; i < arr_max; i++)
			{
				if(value_x > runtime->cfg->array_x[i])
				{
					rtn = GetYi(value_x, \
						runtime->cfg->array_x[i-1],\
						runtime->cfg->array_x[i],\
						runtime->cfg->array_y[i-1],\
						runtime->cfg->array_y[i]);
					break;
				}
			}
		}
		
	}
	return rtn;
}