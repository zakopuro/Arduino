#include "Arduino.h"
#include "serial.h"
#include "pin.h"
#include "Led.h"
#include "event.h"

void Serial_Init( void )
{
	Serial.begin(9600);
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
		}
	}
}