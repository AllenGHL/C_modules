typedef unsigned int 	uint32_t;
typedef  int 	int32_t;
typedef unsigned short 	uint16_t;
typedef unsigned char 	uint8_t;
#include "interpolation.c"
#include "interpolation_cfg.c"
/*以上文件可以让编译器只编译main.c不用编译其他c文件*/
#include "interpolation.h"
#include "interpolation_cfg.h"
#include "stdio.h"

int main(void)
{
	printf("helloworld\n");
	InterpolationInit();
	for (int i = -30; i < 70; i+=5)
	{
		printf("%d=\t%d\n", i, InterpolationGetValueY(Sample1InterpolatonHandle(), i));
	}

	for (int i = 100; i > -20; i-= 5)
	{
		printf("%d=\t%d\n", i, InterpolationGetValueY(Sample2InterpolatonHandle(), i));
	}	
	return 0;
}