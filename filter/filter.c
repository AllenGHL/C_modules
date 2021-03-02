#include "filter.h"
#include "math.h"
/*========================<KalmanFilter>============================*/
void KalmanFilterRegister(KalmanFilterRuntime_t *runtime, float Q, float R, float input_value_limit, float init_value)
{
	runtime->Q = Q;
	runtime->R = R;
	runtime->input_value_limit = input_value_limit;
	runtime->X_last = init_value;

	runtime->P = 0;
	runtime->Kg = 0;
	runtime->X = 0;
}

float KalmanFilterProcess(KalmanFilterRuntime_t *runtime, float value)
{
	/*粗略预测值（非卡尔曼算法部分），非超出限幅的预测本次值跟上次一样，超出限幅权重倾向于上次*/
	/*非卡尔曼算法部分可以根据实际情况修改预测函数 runtime->X = f(runtime->X_last)*/
	if (abs(runtime->X_last-value)>=runtime->input_value_limit)
		runtime->X= value*0.382 + runtime->X_last*0.618;
	else
		runtime->X = runtime->X_last;
	/*根据上个时刻位置估计出的当前位置的方差*/
	runtime->P = runtime->P + runtime->Q;
	/*计算卡尔曼增益系数*/
	runtime->Kg = runtime->P/(runtime->P + runtime->R);
	/*根据卡尔曼系数调整预测值*/
	runtime->X = runtime->X + runtime->Kg * (value - runtime->X_last);
	/*根据卡尔曼系数调整当前位置的方差*/
	runtime->P = (1 - runtime->Kg)*runtime->P;

	runtime->X_last = runtime->X;
	
	return runtime->X;
}

/*========================<SmoothFilter>============================*/

void SmoothFilterRegister(SmoothFilterRuntime_t *runtime, uint32_t *buf, uint16_t buf_len)
{
	//ASSERT(buf_len != 0);
	runtime->buf = buf;
	runtime->buf_len = buf_len;
	runtime->current_i = 0;
	runtime->sum = 0;
	runtime->fill_full_flag = false;
	memset(buf, 0 , buf_len<<2); //buf uint32_t
}


uint32_t SmoothFilterProcess(SmoothFilterRuntime_t *runtime, uint32_t value)
{
	uint32_t average = 0;
	runtime->sum -= runtime->buf[runtime->current_i];
	runtime->buf[runtime->current_i] = value;
	runtime->sum += runtime->buf[runtime->current_i];

	runtime->current_i++;

	if(runtime->current_i >= runtime->buf_len)
		runtime->fill_full_flag = true;
	runtime->current_i %= runtime->buf_len;

	if(true == runtime->fill_full_flag)
		average = runtime->sum / runtime->buf_len; //caution! divisor != 0
	else if(runtime->current_i)
		average = runtime->sum / runtime->current_i;//caution! divisor != 0

	return average;
}
