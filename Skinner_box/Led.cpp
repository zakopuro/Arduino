#include "Arduino.h"
#include "Led.h"

uint8_t lc_feed_led_state;

void Led_switch( uint8_t ledpin )
{
	lc_feed_led_state = !lc_feed_led_state;
	digitalWrite(ledpin,lc_feed_led_state);
}