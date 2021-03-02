#include "hysteresis.h"

/*
	SECTION0 || SECTION1 || SECTION2 || SECTION3 || SECTION4 ||SECTION5 || SECTION6 || SECTION7 || SECTION8
		  	=11=>      ==23=>       =35=>	    =48=> 		=60=>	  ==73=> 	   =85=>	   =98=>
		   <=6==  	   <=14=       <=27==      <=39==      <=52==     <=64=       <=77==      <=89==
*/

const uint32_t sample1_rising_boundary[] = {11, 23, 35, 48, 60, 73, 85, 98};
const uint32_t sample1_falling_boundary[]= { 6, 14, 27, 39, 52, 64, 77, 89};

const HysteresisCfg_t sample1_hysteresis_config =
{
	.section_max 			= 8,
	.init_boundary			= SECTION_RISING,
	.section_rising_boudary	= sample1_rising_boundary,
	.section_falling_boudary= sample1_falling_boundary
};

HysteresisRuntime_t sample1_hysteresis_runtime;

HysteresisRuntime_t * Sample1HysteresisRuntime(void)
{
	return &sample1_hysteresis_runtime;
}

/*
	SECTION0 || SECTION1 || SECTION2 || SECTION3 || SECTION5
		  =6.5v=>    ==9v=>    =16.5v=>  =18.5v=>
		   <=6v==   <=8.5v=    <=16v==   <=18v==
*/
const uint32_t sample2_rising_boundary[] = {65, 90, 165, 185};
const uint32_t sample2_falling_boundary[]= {60, 85, 160, 180};

const HysteresisCfg_t sample2_hysteresis_config =
{
	.section_max 			= 4,
	.init_boundary			= SECTION_FALLING,
	.section_rising_boudary	= sample2_rising_boundary,
	.section_falling_boudary= sample2_falling_boundary
};

HysteresisRuntime_t sample2_hysteresis_runtime;

HysteresisRuntime_t * Sample2HysteresisRuntime(void)
{
	return &sample2_hysteresis_runtime;
}


void HysteresisInit(void)
{
	HysteresisRegister(&sample1_hysteresis_runtime, &sample1_hysteresis_config);
	HysteresisRegister(&sample2_hysteresis_runtime, &sample2_hysteresis_config);

}


