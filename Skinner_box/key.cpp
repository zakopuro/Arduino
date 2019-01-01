#include "Arduino.h"
#include "key.h"

const uint16_t KEY_CHATTER_MASK	= 0x0007;		// チャタリング
static uint16_t lc_KeyBuf[SENSOR_NUM];

// 入力のチャタリング処理
static Uint8_t keyChk(
	Uint8_t		key_in, 		///< キー入力状態
	Uint8_t		key_sts,		///< キー判定状態
	Uint16_t	*chat_buf,		///< チャタリングバッファ
	Uint16_t	chat_mask)		///< チャタリングマスク(キャンセル時間)
{
	Uint8_t key_evt;

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
			// Keyが離された
			key_evt = EVT_OFF;
		}
	}

	return key_evt;
}


static void Evt_Sound()
{
	uint8_t sound_evt;
	uint8_t sound_sts;

	sound_evt = keyChk(SOUND_SENSOR_PIN,
							,
							&lc_KeyBuf[SOUND_SENSOR],
							KEY_CHATTER_MASK);

	if( sound_evt == KEVT_SW_ON ){
		gb_KeyStatus.time_levelup = ON;
	} else if (sound_evt == KEVT_SW_OFF) {
		gb_KeyStatus.time_levelup = OFF;
		}

	if( sound_evt != KEVT_NONE ){
		switch(gb_KeyEvt.time_levelup) {
		case KEVT_NONE:
			gb_KeyEvt.time_levelup = sound_evt;
			break;
		case KEVT_SW_ON:
			// SW_ON情報を通知する前にOFF判定が行われた
			if (sound_evt == KEVT_SW_OFF) {
				gb_KeyEvt.time_levelup = KEVT_SW_ONOFF;
			}
			break;
		case KEVT_SW_OFF:
			// SW OFF情報を通知する前にON判定が行われた
			if (sound_evt == KEVT_SW_ON) {
				gb_KeyEvt.time_levelup = KEVT_SW_ONOFF;
			}
			break;
		default:
			break;
		}
		EvtHappenTimeLvUpSw( gb_KeyEvt.time_levelup );
		gb_KeyEvt.time_levelup = KEVT_NONE;			// イベントクリア
	}
}


static void Evt_Light()
{
	uint8_t sound_evt;
	uint8_t sound_sts;

	sound_evt = keyChk( SOUND_SENSOR_PIN,
						,
						&lc_KeyBuf[SOUND_SENSOR],
						KEY_CHATTER_MASK);

	if( sound_evt == KEVT_SW_ON ){
		gb_KeyStatus.time_levelup = ON;
	} else if (sound_evt == KEVT_SW_OFF) {
		gb_KeyStatus.time_levelup = OFF;
	}

	if( sound_evt != KEVT_NONE ){
		switch(gb_KeyEvt.time_levelup) {
		case KEVT_NONE:
			gb_KeyEvt.time_levelup = sound_evt;
			break;
		case KEVT_SW_ON:
			// SW_ON情報を通知する前にOFF判定が行われた
			if (sound_evt == KEVT_SW_OFF) {
				gb_KeyEvt.time_levelup = KEVT_SW_ONOFF;
			}
			break;
		case KEVT_SW_OFF:
			// SW OFF情報を通知する前にON判定が行われた
			if (sound_evt == KEVT_SW_ON) {
				gb_KeyEvt.time_levelup = KEVT_SW_ONOFF;
			}
			break;
		default:
			break;
		}
		EvtHappenTimeLvUpSw( gb_KeyEvt.time_levelup );
		gb_KeyEvt.time_levelup = KEVT_NONE;        // イベントクリア
	}
}


