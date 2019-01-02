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
  pinMode(SKINNER_BOX_STATE_LED_PIN,OUTPUT);
  pinMode(FEED_GET_LED_PIN,OUTPUT);
  digitalWrite(BUZZER_PIN,HIGH);	 // BUZZERはLOWアクティブ
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
  Serial_Main();	// シリアル通信の管理
  Event_Main();	 // イベント処理の管理
  Key_Main();	   // 入力処理の管理
}