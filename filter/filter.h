#ifndef __FILTER_H__
#define __FILTER_H__
/*========================<KalmanFilter>============================*/
typedef struct 
{
	float Q; //估计误差 协方差 Q越大新测量值权重越大 建议0.001
	float R;	// 测量误差 噪声协方差，建议0.1
	float P;	//方差，根据上个时刻位置估计出的当前位置的方差
	float Kg;	//卡尔曼增益 
	float X;	//预测值
	float X_last;   //上次预测值  也是init_value KalmanFilterRegister时估计一个初始值	
	float input_value_limit;  // 超出限幅权重倾向于上次值
}KalmanFilterRuntime_t;

void KalmanFilterRegister(KalmanFilterRuntime_t *runtime, float Q, float R, float input_value_limit, float init_value);
float KalmanFilterProcess(KalmanFilterRuntime_t *runtime, float value);

/*========================<SmoothFilter>============================*/
typedef struct 
{
	uint32_t *buf;
	uint16_t buf_len;
	uint16_t current_i;
	uint32_t sum;
	uint8_t	 fill_full_flag; //buffer未填满时求平均底数不能用buf_len
}SmoothFilterRuntime_t;

void SmoothFilterRegister(SmoothFilterRuntime_t *runtime, uint32_t *buf, uint16_t buf_len);
uint32_t SmoothFilterProcess(SmoothFilterRuntime_t *runtime, uint32_t value);

#endif