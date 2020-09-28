/*
 * interrupt.c
 *
 * Created: 29-Sep-19 8:19:18 PM
 * Author : quann
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/delay.h>

volatile int8_t val=0; //KHAI B�O BI?N VAL.

int main(void)
{
    DDRD = 0x00; //KHAI B�O C?NG D L� NG� NH?P ?? S? D?NG CHO NG?T.
	PORTD = 0xFF; //S? D?NG ?I?N TR? N?I K�O L�N.
	DDRB = 0xFF; //C?NG C L� NG� XU?T
	
	MCUCR |= (1<<ISC11)|(1<<ISC01); //THI?T L?P MODE: 2 NG?T C?NH XU?NG.
	GICR |= (1<<INT1) | (1<<INT0); //THI?T L?P: CHO PH�P NG?T HO?T ??NG.
	sei();//THI?T L?P: NG?T TO�N C?C.

    while (1) 
    {
		PORTC++;
		_delay_loop_2(60000);
    }
	return 0;
}

ISR(INT0_vect){
	val++;
	if(val > 9) val = 0;
	PORTB = val;
}

ISR(INT1_vect){
	val--;
	if(val < 0) val = 9;
	PORTB = val;
}

