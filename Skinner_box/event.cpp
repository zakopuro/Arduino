#include "Arduino.h"
#include "event.h"
#include "pin.h"
#include "Timer.h"

uint8_t gb_buzzer_event;
uint8_t gb_sound_event;
uint8_t gb_light_event;
uint8_t gb_led_event;

boolean gb_skinner_box_state;

void Event_Init( void ){
	// EvtChecker evtCheck = EvtChecker();
	gb_buzzer_event = EVT_NONE;
	gb_sound_event	= EVT_NONE;
	gb_light_event	= EVT_NONE;
	gb_led_event	= EVT_NONE;

	gb_skinner_box_state = OFF;
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
		analogWrite(BUZZER_PIN,200);
		Timer_Buzzer_Start();
	} else if(gb_buzzer_event == EVT_OFF){
		analogWrite(BUZZER_PIN,255);
		Timer_Buzzer_Stop();
	}
	gb_buzzer_event = EVT_NONE;
}

static void evtLedChk( void )
{
	if( gb_led_event == EVT_ON){
		digitalWrite(FEED_LED_PIN,HIGH);
		Timer_Led_Start();
	} else if(gb_led_event == EVT_OFF){
		digitalWrite(FEED_LED_PIN,LOW);
		Timer_Led_Stop();
	}
	gb_led_event = EVT_NONE;
}






static void evtSoundChk( void )
{
	if (gb_sound_event == EVT_ON){

		gb_skinner_box_state = !gb_skinner_box_state;
		if (gb_skinner_box_state){
			Serial.println("POWER ON");
		} else{
			Serial.println("POWER OFF");
		}

	}
	gb_sound_event = EVT_NONE;
}

static void evtLightChk( void )
{
	if (gb_light_event == EVT_ON){

		if (gb_skinner_box_state){
			Serial.println("FEED GET");
		} else{
			// Do Nothing
		}
	}
	gb_light_event = EVT_NONE;
}



void EvtHappenSound( uint8_t event )
{
	if( event != EVT_NONE ){
		if( (event == EVT_ON) || (event == EVT_ONOFF) ){
			gb_sound_event = EVT_ON;
		}
	}
}

void EvtHappenLight( uint8_t event )
{
	if( event != EVT_NONE ){
		if( (event == EVT_ON) || (event == EVT_ONOFF) ){
			gb_light_event = EVT_ON;
		}
	}
}


void Event_Main( void )
{
	// evtCheck.soundcheck();
	// evtCheck.lightcheck();
	evtBuzzerChk();
	evtSoundChk();
	evtLedChk();
	evtLightChk();
}