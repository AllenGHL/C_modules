typedef unsigned int 	uint32_t;
typedef  int 	int32_t;
typedef unsigned short 	uint16_t;
typedef unsigned char 	uint8_t;

#include "damping.c"
/*以上文件可以让编译器只编译main.c不用编译其他c文件*/

#include "stdio.h"
#include "damping.h"

int main(void)
{
	int base = -17;
	DampingConfig_t cfg = 
	{
		.step_up 	= 1,
		.step_down 	= -1,
		.dead_up	= 1,
		.dead_down	= -1,
		.border_up	= 100,
		.border_down= -20,
		.init_value = -17,
	};

	DampingRuntime_t rt;

	DampingRegister(&rt, &cfg);
	for (int i = 0; i > -4; --i)
	{
		printf("target:%d\t current:%d\n", base+i, DampingProcess(&rt, base+i));
		printf("target:%d\t current:%d\n", base+i, DampingProcess(&rt, base+i));
		printf("target:%d\t current:%d\n", base+i, DampingProcess(&rt, base+i));
		// printf("target:%d\t current:%d\n", base+i, DampingProcess(&rt, base+i));
		// printf("target:%d\t current:%d\n", base+i, DampingProcess(&rt, base+i));
		// printf("target:%d\t current:%d\n", base+i, DampingProcess(&rt, base+i));

	}		
	// for (int i = 0; i < 100; ++i)
	// {
	// 	printf("target:%d\t current:%d\n", i, DampingProcess(&rt, i));
	// }
	// for (int i = 100; i > -30; --i)
	// {
	// 	printf("target:%d\t current:%d\n", i, DampingProcess(&rt, i));
	// }	
	// DampingSetDisplay(&rt, 56);
	// DampingSetStep(&rt, 2, -3);
	// DampingSetBorder(&rt, 78, 0);
	// for (int i = 0; i < 100; ++i)
	// {
	// 	printf("target:%d\t current:%d\n", i, DampingProcess(&rt, i));
	// }	
	return 0;
}