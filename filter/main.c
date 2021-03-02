typedef unsigned int 	uint32_t;
typedef  int 	int32_t;
typedef unsigned short 	uint16_t;
typedef unsigned char 	uint8_t;
#define true 1
#define false 0
#include "filter.c"
/*以上文件可以让编译器只编译main.c不用编译其他c文件*/
#include "stdio.h"
#include "stdlib.h"
#include "math.h"
#include "filter.h"

#define L_RAND_MAX 100




double frand(void)
{
	double ra= rand()%L_RAND_MAX;
	double rtn = 2 * (( ra/ (double)L_RAND_MAX) - 0.5);//随机噪声
	return rtn;
}
 
void main(void)
{
	float z_real = 0.56;
	float z_measure;
	float summerror_kalman = 0;
	float summerror_smooth = 0;
	float summerror_measure = 0;
	float kalman_result;
	float kalman_smooth;
	int i;
/*========================<KalmanFilter>============================*/
	KalmanFilterRuntime_t k_f_rt;
	KalmanFilterRegister(&k_f_rt, 0.001, 0.01, 100, 0.5);

/*========================<SmoothFilter>============================*/
	#define SF_BUF_MAX  10
	uint32_t smooth_buffer[SF_BUF_MAX];
	SmoothFilterRuntime_t sf_rt;
	SmoothFilterRegister(&sf_rt, smooth_buffer, SF_BUF_MAX);

	for (i = 0; i < 100;i++)
	{
		z_measure = z_real + frand()*0.03;//测量值
 
		printf("Real position:%6.3f\n", z_real);
		printf("Measure position:%6.3f [diff:%.3f]\n", z_measure, fabs(z_real - z_measure));
		kalman_result = KalmanFilterProcess(&k_f_rt, z_measure);
		printf("Kalman position: %6.3f [diff:%.3f]\n", kalman_result, fabs(z_real - kalman_result));
		kalman_smooth = SmoothFilterProcess(&sf_rt, z_measure*1000)/1000.0;
		printf("Smooth position: %6.3f [diff:%.3f]\n", kalman_smooth, fabs(z_real - kalman_smooth));		
		printf("\n\n");
		summerror_kalman += fabs(z_real - kalman_result);
		summerror_measure += fabs(z_real - z_measure);
		summerror_smooth += fabs(z_real - kalman_smooth);
	}
	printf("总体测量误差	  :%f\n", summerror_measure);
	printf("总体卡尔曼滤波误差:%f\n", summerror_kalman);
	printf("总体平滑滤波误差:%f\n", summerror_smooth);
 
	// getchar();
}
