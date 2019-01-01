#include "Arduino.h"
#include "event.h"

void Evetn_Init( void )
{
	EvtChecker evtCheck = EvtChecker();
}

static void EvtChecker::soundcheck( void )
{
	if(sound_event == EVT_ON){
		Led_switch(FEED_LED_PIN);
	} else {
		// Do Nothing
	}
}

static void EvtChecker::soundcheck( void )
{
	if(light_event == EVT_ON){
		Led_switch(FEED_LED_PIN);
	} else {
		// Do Nothing
	}
}

void Event_Main( void )
{
	evtCheck.soundcheck();
	evtCheck.lightcheck();
}