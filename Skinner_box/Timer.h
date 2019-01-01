#ifndef TIMER_H
#define TIMER_H

extern uint16_t gb_TM_Key;

extern void Timer_Init( void );
extern void Timer_Buzzer_Start( void );
extern void Timer_Buzzer_Stop( void );
#endif // TIMER_H