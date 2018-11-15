#ifndef APP_COMMON_H_
#define APP_COMMON_H_
#include "appUartApi.h"



#define ASSERT(x)	{ 	if(!(x))  \
	                              	{            \
							Uart_Printf("Asserted in file: %s  line:%s \r\n",  __FILE__, __LINE__); \
					   		while(1); \
						} \
					}

#define 				AutoCycleTest				1
#define				DCPowerAutoSet				0 //每次参数设置均需要设置DC 电源，需要响应
#define				DCPowerManualSet			1//手工设置
#define				Enable_600usLimit			1 //最小IGBT 开启时间锁死在600us
#define 				AutoCycleTestEnable			1
#define				AutoCycleTestDisable		0
#define				LcdReflashEnable			1
#define				LcdReflashDisable			0

extern u8 			wave_display_buf[200];
extern u8				wave_display_buf_last[200];
extern u8				Lcd_CFG_Idle_Cnts;
extern u8				Lcd_Reflash_Cnts;

extern u8 			DC_Power_SetMode;
extern u8 			DischargeWithBuzzer;
extern u8				Auto_Test;
extern u8				LCD_Clear_Enable;


void memsetv(u8*a,u8 b,u16 c);
void memcopy(u8* a, const u8* b, u16 c);
void DelaySync(u32 nFactor);

void Delay1Us(void);
void Delay5Us(void);
void DelayUs(u32 nFactor);
void DelayMs(u16 nFactor);
bool  set_power(u16 val);



#endif


