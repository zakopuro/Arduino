#ifndef TIMER_H
#define TIMER_H

extern uint16_t gb_TM_Key;
extern uint16_t gb_TM_Long_Key;

extern void Timer_Init( void );
extern void Timer_Buzzer_Start( void );
extern void Timer_Buzzer_Stop( void );
extern void Timer_Led_Start( void );
extern void Timer_Led_Stop( void );
#endif // TIMER_H