/*
 * timerCounter20.c
 *
 * Created: 02-Oct-19 9:34:59 PM
 * Author : quann
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

int main(void)
{
    DDRB = 0xFF;//THI?T L?P C?NG B L� C?NG XU?T
	PORTB = 0x00;//THI?T L?P GI� TR? ??U
	
	TCCR1B =(1<<CS10)|(1<<CS11);//CH?N MODE HO?T ??NG
	TCNT1 = 49910;//KH?I T?O GI� TR? ??U CHO T/C1
	TIMSK = (1<<TOIE1);//CHO PH�P NG?T KHI C� TR�N ? T/C1
	sei();//CHO PH�P NG?T TO�N C?C
    while (1) 
    {
		
    }
}
//CH??NG TR�NH PH?C V? NG?T T/C1
ISR(TIMER1_OVF_vect){
	TCNT1 = 49910;//KH?I T?O GI� TR? ??U CHO T/C1
	PORTB ^= 1;//??O GI� TR? ? C?NG B.
}

