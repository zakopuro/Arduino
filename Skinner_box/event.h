#ifndef	EVENT_H
#define	EVENT_H
// Event状態
enum {
	EVT_NONE,
	EVT_ON,
	EVT_OFF,
};
enum {
	SOUND_SENSOR,
	LIGHT_SENSOR,
	SENSOR_NUM,
};

class EvtChecker {
	public:
		EvtChecker();
		void soundcheck();
		void lightcheck();
};


#endif	// EVENT_H