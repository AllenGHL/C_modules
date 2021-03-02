typedef unsigned char uint8_t;
typedef unsigned int uint32_t;
#include "hysteresis.c"
#include "hysteresis_config.c"
/*以上文件可以让编译器只编译main.c不用编译其他c文件*/

#include "hysteresis.h"
#include "hysteresis_config.h"
#include "stdio.h"


int main(void)
{
	uint32_t data;
	HysteresisInit();

	for(int i = 0; i < 110; i = i +5)
	{
		HysteresisDataUpdate(Sample1HysteresisRuntime(),i);
		data = HysteresisDataGet(Sample1HysteresisRuntime());
		printf("Sample1: %d->\t %d\n", i, data);	
		
	}

	for(int i = 200; i >= 50; i = i -5)
	{
		HysteresisDataUpdate(Sample2HysteresisRuntime(),i);
		data = HysteresisDataGet(Sample2HysteresisRuntime());
		printf("Sample2: %d->\t %d\n", i, data);	
		
	}

	return 0;
}