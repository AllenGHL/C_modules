#ifndef __HYSTERESIS_H__
#define __HYSTERESIS_H__

#define SECTION_RISING	0
#define SECTION_FALLING	1

typedef struct
{
	uint8_t section_max;						/*进度条数目*/
	uint8_t init_boundary;					/*首次数据无法判定上升还是下降时，判定显示进度条格数依据*/
	const uint32_t *section_rising_boudary; 	/*上涨分界线*/
	const uint32_t *section_falling_boudary; 	/*下降分界线*/
	
}HysteresisCfg_t;

typedef struct
{
	const HysteresisCfg_t *config;
	uint8_t section_current;
	uint8_t section_derection;

}HysteresisRuntime_t;

void HysteresisRegister(HysteresisRuntime_t *runtime, HysteresisCfg_t *config);
void HysteresisDataUpdate(HysteresisRuntime_t *runtime, uint32_t input_data);
uint32_t HysteresisDataGet(HysteresisRuntime_t *runtime);

#endif