#include "Arduino.h"
#include "serial.h"
#include "pin.h"
#include "event.h"
#include "Timer.h"
#include "avr/wdt.h"

static void software_reset( void )
{
	wdt_disable();
	wdt_enable(WDTO_15MS);
	while (1) {}
}

void Serial_Init( void )
{
	Serial.begin(9600);
}

void Serial_print_reward_state( boolean box_state , boolean feed_get )
{
	Serial.print(box_state);
	Serial.print(feed_get);
}


void Serial_Main( void )
{
	int inputchar;

	inputchar = Serial.read();

	if (inputchar != -1){
		switch(inputchar){
		case 'l':
			gb_led_event	= EVT_ON;
			break;

		case 'b':
			gb_buzzer_event = EVT_ON;
			break;

		case 'r':
			// リスタートする。
			software_reset();
			break;
		}
	}
}