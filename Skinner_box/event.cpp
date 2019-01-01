#include "Arduino.h"
#include "event.h"
#include "pin.h"
#include "Timer.h"

uint8_t gb_buzzer_event;
uint8_t gb_sound_event;

void Event_Init( void ){
	// EvtChecker evtCheck = EvtChecker();
	gb_buzzer_event = EVT_NONE;
	gb_sound_event	= EVT_NONE;
}

// void EvtChecker::soundcheck(){
// 	// if(sound_event == EVT_ON){
// 	// 	Led_switch(FEED_LED_PIN);
// 	// } else {
// 	// 	// Do Nothing
// 	// }
// }

static void evtBuzzerChk( void )
{
	if( gb_buzzer_event == EVT_ON){
		analogWrite(BUZZER_PIN,230);
		Timer_Buzzer_Start();
	} else if(gb_buzzer_event == EVT_OFF){
		analogWrite(BUZZER_PIN,255);
		Timer_Buzzer_Stop();
	}
	gb_buzzer_event = EVT_NONE;
}

static void evtSoundChk( void )
{
	if (gb_sound_event == EVT_ON){
		Serial.println("SOUND ON");
	}
	gb_sound_event = EVT_NONE;
}

void EvtHappenSound( uint8_t event )
{
	if( event != EVT_NONE ){
		if( (event == EVT_ON) || (event == EVT_ONOFF) ){
			gb_sound_event = EVT_ON;
		}
	}
}

void Event_Main( void )
{
	// evtCheck.soundcheck();
	// evtCheck.lightcheck();
	evtBuzzerChk();
	evtSoundChk();
}