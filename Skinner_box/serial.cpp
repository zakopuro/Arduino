#include "Arduino.h"
#include "serial.h"


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
		case '1':
			lc_feed_led_state = !lc_feed_led_state;
			digitalWrite(FEED_LED_PIN,lc_feed_led_state);
			break;

		case '2':
			digitalWrite(BUZZER_PIN,LOW);
			delay(10);
			digitalWrite(BUZZER_PIN,HIGH);
			break;
		}
	}
}