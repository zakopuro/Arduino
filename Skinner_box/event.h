#ifndef	EVENT_H
#define	EVENT_H
// Event状態
enum {
	EVT_NONE,
	EVT_ON,
	EVT_OFF,
	EVT_ONOFF,
};
enum {
	SOUND_SENSOR,
	LIGHT_SENSOR,
	SENSOR_NUM,
};

extern uint8_t gb_buzzer_event;
extern uint8_t gb_sound_event;
extern uint8_t gb_light_event;
extern uint8_t gb_led_event;

// class EvtChecker {
// 	public:
// 		EvtChecker();
// 		void soundcheck();
// 		void lightcheck();
// };

extern void Event_Main( void );
extern void Event_Init( void );
extern void EvtHappenSound( uint8_t event );
extern void EvtHappenLight( uint8_t light );
#endif	// EVENT_H