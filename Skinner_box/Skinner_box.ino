#include "Arduino.h"
#include "MsTimer2.h"
#include "event.h"
#include "key.h"
#include "pin.h"


uint8_t lc_buzzer_input_event;

// PINのセットアップ
void pinsetup( void )
{
  pinMode(FEED_LED_PIN,OUTPUT);
  pinMode(LIGHT_SENSOR_PIN,INPUT);
  pinMode(SOUND_SENSOR_PIN,INPUT);
  pinMode(BUZZER_PIN,OUTPUT);
  digitalWrite(BUZZER_PIN,HIGH);     // BUZZERはLOWアクティブ
  pinMode(SKINNER_BOX_STATE_LED_PIN,OUTPUT);
  lc_feed_led_state = LOW;
}
// 初期セットアップ
void setup( void )
{
  pinsetup();
  Serial_Init();
  Evetn_Init();
}


void loop( void )
{
  Serial_Main();
  Event_Main();
}