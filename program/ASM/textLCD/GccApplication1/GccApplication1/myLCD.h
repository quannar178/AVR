#include <util/delay.h>
#define sbi(sfr,bit) sfr|=_BV(bit)
#define cbi(sfr,bit) sfr&=~(_BV(bit))
#define EN                            2
#define RW                           1
#define RS                            0
#define CTRL                       PORTB
#define DDR_CTRL             DDRB
#define DATA_O                  PORTB
#define DATA_I                    PINB
#define DDR_DATA             DDRB
/*
#define LCD8BIT
#define DATA_O                  PORTD
#define DATA_I                    PIND
#define DDR_DATA             DDRD
*/
char Read2Nib(){
       char HNib, LNib;
       DATA_O |=0xF0;
       sbi(CTRL,EN); //enable
        DDR_DATA &=0x0F; //set 4 bits cao cua PORT DATA lam input
        HNib=DATA_I & 0xF0;
       cbi(CTRL,EN); //disable       sbi(CTRL,EN); //enable
       LNib = DATA_I &0xF0;
       cbi(CTRL,EN); //disable
       LNib>>=4;
       return (HNib|LNib);
}
void Write8Bit(uint8_t chr){
       DATA_O=chr;   //out 8 bits to DATA Line
       sbi(CTRL,EN); //enable
       cbi(CTRL,EN); //disable
}

void wait_LCD(){
       #ifdef LCD8BIT
              while(1){
                     cbi(CTRL,EN); //x�a EN
                     cbi(CTRL,RS);  //d�y l� Instruction
                      sbi(CTRL,RW); //chi?u t? LCD ra ngo�i

                     DDR_DATA=0xFF; //hu?ng data out
                     DATA_O=0xFF;    // g?i l?nh d?c BF
                      sbi(CTRL,EN);     //enable

                     DDR_DATA=0x00; // �?i hu?ng data in
                     if(bit_is_clear(DATA_I,7)) break;
              }
              cbi(CTRL,EN); //disable for next step
              cbi(CTRL,RW); //ready for next step
              DDR_DATA=0xFF; //Ready to Out
       #else
              char temp_val;
              while(1){
                     cbi(CTRL,RS); //RS=0, the following data is COMMAND
                     sbi(CTRL,RW); //LCD -> AVR
                     temp_val=Read2Nib();
                     if (bit_is_clear(temp_val,7)) break;
              }
              cbi(CTRL, RW); //ready for next step
               DDR_DATA=0xFF;//Ready to Out
       #endif
      //_delay_ms(1); }
      
void init_LCD(){
       DDR_CTRL=0xFF;
       DDR_DATA=0xFF;
//Function set------------------------------------------------------------------------------       cbi(CTRL,RS);   // the following data is COMMAND
       cbi(CTRL, RW); // AVR->LCD
       cbi(CTRL, EN);
       #ifdef LCD8BIT
              Write8Bit(0x38);
             wait_LCD();
       #else
             sbi(CTRL,EN); //enable
              sbi(DATA_O, 5);
              cbi(CTRL,EN); //disable
              wait_LCD();
              Write2Nib(0x28);//4 bit mode, 2 line, 5x8 font
              wait_LCD();
       #endif
//Display control-------------------------------------------------------------------------        cbi(CTRL,RS); // the following data is COMMAND
        #ifdef LCD8BIT
              Write8Bit(0x0E);
              wait_LCD();
       #else
              Write2Nib(0x0E);
              wait_LCD();
       #endif
//Entry mode set------------------------------------------------------------------------
       cbi(CTRL,RS); // the following data is COMMAND
       #ifdef LCD8BIT
              Write8Bit(0x06);
              wait_LCD();
       #else
              Write2Nib(0x06);
              wait_LCD();
       #endif}
       
void home_LCD(){
       cbi(CTRL,RS); // the following data is COMMAND
        #ifdef LCD8BIT
              Write8Bit(0x02);
              wait_LCD();
       #else
              Write2Nib(0x02);
              wait_LCD();
       #endif 
}
void move_LCD(uint8_t y,uint8_t x){
       uint8_t Ad;
       Ad=64*(y-1)+(x-1)+0x80; // t�nh m� l?nh
       cbi(CTRL,RS); // the following data is COMMAND
       #ifdef LCD8BIT
              Write8Bit(Ad);
              wait_LCD();
       #else
              Write2Nib(Ad);
              wait_LCD();
       #endif

void clr_LCD(){ //x�a to�n b? LCD
       cbi(CTRL,RS); //RS=0 mean the following data is COMMAND (not normal DATA)
       #ifdef LCD8BIT
              Write8Bit(0x01);
              wait_LCD();
       #else              Write2Nib(0x01);
              wait_LCD();
       #endif
}
void putChar_LCD(uint8_t chr){ //hi?n th? 1 k� t? chr l�n LCD
       sbi(CTRL,RS); //this is a normal DATA
       #ifdef LCD8BIT
              Write8Bit(chr);
              wait_LCD();
       #else
              Write2Nib(chr);
              wait_LCD();
       #endif
}
void print_LCD(char* str, unsigned char len){ //Hi?n th? 1 chu?i k� t?
       unsigned char i;
       for (i=0; i<len; i++)
              if(str[i] > 0) putChar_LCD(str[i]);
             else putChar_LCD(' ');
       }
}
