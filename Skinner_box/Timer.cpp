#include "Arduino.h"
#include "MsTimer2.h"
#include "Timer.h"
#include "event.h"
#include "pin.h"

uint16_t gb_TM_buzzer;
uint16_t gb_TM_Key;
boolean buzzer_timer_flg;

void Timer_1ms_Interrupt( void )
{
	if (gb_TM_Key > 0){
		gb_TM_Key -= 1;
	}

	if ( buzzer_timer_flg ){
		gb_TM_buzzer += 1;
		if (gb_TM_buzzer >= 500){
			gb_buzzer_event = EVT_OFF;
		}
	}
}

void Timer_Buzzer_Start( void )
{
	gb_TM_buzzer = 0;
	buzzer_timer_flg = ON;
}

void Timer_Buzzer_Stop( void )
{
	gb_TM_buzzer = 0;
	buzzer_timer_flg = OFF;
}

void Timer_Init( void )
{
	// 100msタイマー生成
	gb_TM_buzzer	= 0;
	gb_TM_Key		= 0;
	buzzer_timer_flg = OFF;
	MsTimer2::set(1,Timer_1ms_Interrupt);
	MsTimer2::start();
}