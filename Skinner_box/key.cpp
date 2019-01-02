#include "Arduino.h"
#include "key.h"
#include "event.h"
#include "Timer.h"
#include "pin.h"

const uint16_t KEY_CHAT_TIME		= 100;			// 通常チャタリングキャンセル時間
const uint16_t KEY_CHAT_LONG_TIME	= 150;			// 長押しチャタリングキャンセル時間
const uint16_t KEY_CHATTER_MASK		= 0x0007;		// チャタリング
static uint16_t lc_KeyBuf[SENSOR_NUM];
KeyStatus_t	gb_KeyStatus;
KeyEvt_t		gb_KeyEvt;

// 入力のチャタリング処理
static uint8_t keyChk(
	uint8_t		key_sts,		///< キー判定状態
	uint8_t		key_in, 		///< キー入力状態
	uint16_t	*chat_buf,		///< チャタリングバッファ
	uint16_t	chat_mask)		///< チャタリングマスク(キャンセル時間)
{
	uint8_t key_evt;

	*chat_buf <<= 1;
	if (key_in == LOW) {
		 *chat_buf |= 0x01;
	}

	key_evt = EVT_NONE;
	if (key_sts == OFF) {
		if ((*chat_buf & chat_mask) == chat_mask) {
			key_evt = EVT_ON;
		}
	} else {
		// OFF判定はすぐにするように変更
		if ( (*chat_buf & 0x01) == 0x00 ) {
			key_evt = EVT_OFF;
		}
	}

	return key_evt;
}


static void Key_Sound( void )
{
	uint8_t sound_evt;
	uint8_t sound_sts;

	sound_sts = digitalRead(SOUND_SENSOR_PIN);

	sound_evt = keyChk( sound_sts,
						gb_KeyStatus.sound,
						&lc_KeyBuf[SOUND_SENSOR],
						KEY_CHATTER_MASK);

	if( sound_evt == EVT_ON ){
		gb_KeyStatus.sound = ON;
	} else if (sound_evt == EVT_OFF) {
		gb_KeyStatus.sound = OFF;
		}

	if( sound_evt != EVT_NONE ){
		switch(gb_KeyEvt.sound) {
		case EVT_NONE:
			gb_KeyEvt.sound = sound_evt;
			break;
		case EVT_ON:
			// SW_ON情報を通知する前にOFF判定が行われた
			if (sound_evt == EVT_OFF) {
				gb_KeyEvt.sound = EVT_ONOFF;
			}
			break;
		case EVT_OFF:
			// SW OFF情報を通知する前にON判定が行われた
			if (sound_evt == EVT_ON) {
				gb_KeyEvt.sound = EVT_ONOFF;
			}
			break;
		default:
			break;
		}
		EvtHappenSound( gb_KeyEvt.sound );
		gb_KeyEvt.sound = EVT_NONE;			// イベントクリア
	}
}

static void Key_Light( void )
{
	uint8_t light_evt;
	uint8_t light_sts;

	light_sts = digitalRead(LIGHT_SENSOR_PIN);

	light_evt = keyChk( light_sts,
						gb_KeyStatus.light,
						&lc_KeyBuf[LIGHT_SENSOR],
						KEY_CHATTER_MASK);

	if( light_evt == EVT_ON ){
		gb_KeyStatus.light = ON;
	} else if (light_evt == EVT_OFF) {
		gb_KeyStatus.light = OFF;
		}

	if( light_evt != EVT_NONE ){
		switch(gb_KeyEvt.light) {
		case EVT_NONE:
			gb_KeyEvt.light = light_evt;
			break;
		case EVT_ON:
			// SW_ON情報を通知する前にOFF判定が行われた
			if (light_evt == EVT_OFF) {
				gb_KeyEvt.light = EVT_ONOFF;
			}
			break;
		case EVT_OFF:
			// SW OFF情報を通知する前にON判定が行われた
			if (light_evt == EVT_ON) {
				gb_KeyEvt.light = EVT_ONOFF;
			}
			break;
		default:
			break;
		}
		EvtHappenLight( gb_KeyEvt.light );
		gb_KeyEvt.light = EVT_NONE;			// イベントクリア
	}
}



void Key_Init( void )
{
	uint8_t i;

	gb_KeyStatus.sound	= ON;

	gb_KeyEvt.sound		= EVT_NONE;

	// キーチャタリングバッファの初期化
	for (i = 0; i < SENSOR_NUM; i++) {
		lc_KeyBuf[i]		= 0;
	}
}

void Key_Main( void )
{
	if (gb_TM_Key == 0) {
		Key_Light();
		gb_TM_Key = KEY_CHAT_TIME;
	}

	if (gb_TM_Long_Key == 0){
		Key_Sound();
		gb_TM_Long_Key = KEY_CHAT_LONG_TIME;
	}
}