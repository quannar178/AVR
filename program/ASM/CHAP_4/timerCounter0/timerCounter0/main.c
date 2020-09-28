#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

int main(void){
	DDRB=0xFF;//C?NG B L� C?NG XU?T
	PORTB=0x00;

	TCCR0=(1<<CS01);//THI?T L?P B? CHIA PRESCALER = 8
	TCNT0=131;//G�N GI� TR? KH?I T?O CHO T/C0
	TIMSK=(1<<TOIE0);//CHO PH�P NG?T KHI C� TR�N ? T/C0
	sei();//CHO PH�P NG?T TO�N C?C
	while (1){
	}
	return 0;
}

//TR�NH PH?C V? NG?T TR�N ? T/C0
ISR (TIMER0_OVF_vect ){
	TCNT0=131;//G�N GI� TR? KH?I T?O CHO T/C0
	PORTB^=1;//??I TR?NG TH�I ? C?NG B.
}