#ifndef	KEY_H
#define	KEY_H

// class Keychecker
// {

// 	public:
// 		Keychecker():
// }
typedef struct {
	uint16_t	sound	:1;
} KeyStatus_t;

typedef struct {
	uint16_t	sound	:2;
} KeyEvt_t;

extern KeyStatus_t	gb_KeyStatus;
extern KeyEvt_t		gb_KeyEvt;

extern void Key_Main( void );
#endif	// KEY_H