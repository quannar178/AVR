#include <avr/io.h>
#include <avr/interrupt.h>

int main(void){
       DDRB=0xFF;//THI?T L?P C?NG B L� C?NG XU?T.
       PORTB=0x00;
       DDRD=0x00;//THI?T L?P C?NG D L� C?NG V�O ?? NH?N BUTTON
       PORTD=0xFF;//S? D?NG ?I?N TR? K�O L�N ? C?NG B

       TCCR0=(1<<CS02)|(1<<CS01);//THI?T L?P MODE CLOCK ON FAILING EDGE.
       TCNT0=0;

       while (1){
             if (TCNT0==10) TCNT0=0;
             PORTB=TCNT0;//XU?T GI� TR? RA LED 7 ?O?N
             if (bit_is_clear(PIND,7)) TCNT0=0;//??A V? GI� TR? 0 N?U NH?N BUTTON ? C?NG D, C? TH? PD7.
       }
       return 0;
}