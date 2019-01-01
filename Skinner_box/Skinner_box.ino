#include "Arduino.h"
#include "event.h"
#include "key.h"
#include "pin.h"
#include "serial.h"
#include "Timer.h"
#include "key.h"


// PINのセットアップ
void pinsetup( void )
{
  pinMode(FEED_LED_PIN,OUTPUT);
  pinMode(LIGHT_SENSOR_PIN,INPUT);
  pinMode(SOUND_SENSOR_PIN,INPUT);
  pinMode(BUZZER_PIN,OUTPUT);
  digitalWrite(BUZZER_PIN,HIGH);     // BUZZERはLOWアクティブ
}
// 初期セットアップ
void setup( void )
{
  pinsetup();
  Serial_Init();
  Event_Init();
  Timer_Init();
}


void loop( void )
{
  Serial_Main();
  Event_Main();
  Key_Main();
}