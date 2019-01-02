#include "Arduino.h"
#include "MsTimer2.h"
#include "Timer.h"
#include "event.h"
#include "pin.h"

// タイマー関連
uint16_t gb_TM_buzzer;
uint16_t gb_TM_led;
uint16_t gb_TM_Key;
uint16_t gb_TM_Long_Key;

const uint16_t BUZZER_TIME	= 750;
const uint16_t LED_TIME	 	= 500;

boolean buzzer_timer_flg;
boolean led_timer_flg;

void Timer_1ms_Interrupt( void )
{
	// チャタリング
	if (gb_TM_Key > 0){
		gb_TM_Key -= 1;
	}
	if (gb_TM_Long_Key > 0){
		gb_TM_Long_Key -= 1;
	}

	// ブザー
	if ( buzzer_timer_flg ){
		gb_TM_buzzer += 1;
		if (gb_TM_buzzer >= BUZZER_TIME){
			gb_buzzer_event = EVT_OFF;
		}
	}

	// LED
	if ( led_timer_flg ){
		gb_TM_led += 1;
		if (gb_TM_led >= LED_TIME){
			gb_led_event = EVT_OFF;
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

void Timer_Led_Start( void )
{
	gb_TM_led = 0;
	led_timer_flg = ON;
}

void Timer_Led_Stop( void )
{
	gb_TM_led = 0;
	led_timer_flg = OFF;
}



void Timer_Init( void )
{

	gb_TM_buzzer	= 0;
	gb_TM_Key		= 0;
	gb_TM_Long_Key	= 0;
	gb_TM_led		= 0;
	buzzer_timer_flg = OFF;
	MsTimer2::set(1,Timer_1ms_Interrupt);
	MsTimer2::start();
}