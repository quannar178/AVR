#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

//CH??NG TR�NH CON PH�T D? LI?U RA M�N H�NH
void uart_char_tx(unsigned char chr){
      while (bit_is_clear(UCSRA,UDRE)) {};//
       UDR=chr;
}
volatile unsigned char u_Data;//BI?N L?U GI� TR? NH?N ???C

int main(void){
	//THI?T L?P T?C ?? TRUY?N 57600K ?NG V?I F = 8MHZ
      UBRRH=0;
      UBRRL=8;
	  //THI?T L?P TH�NG S? KH�C V� K�CH HO?T B? TRUY?N, NH?N D? LI?U
      UCSRA=0x00;
      UCSRC=(1<<URSEL)|(1<<UCSZ1)|(1<<UCSZ0);
      UCSRB=(1<<RXEN)|(1<<TXEN)|(1<<RXCIE);//CHO PH�P C? TRUY?N V� NH?N, NG?T SAU KHI NH?N D? LI?U
       sei(); ////CHO PH�P NG?T TO�N C?C
      while(1){      }
}
//TR�NH PH?C V? NG�T USART
ISR(USART_RXC_vect){
       u_Data=UDR;
      uart_char_tx(u_Data);
}