/*
 * GccApplication1.c
 *
 * Created: 14-Oct-19 2:40:26 AM
 * Author : quann
 */ 

#include <avr/io.h>
#include <util/delay.h>
#include "myLCD.h" //include th? vi?n myLCD
int main(){
	init_LCD(); //kh?i ?? LCD
	clr_LCD(); // x�a to� b? LCD
	putChar_LCD(' '); //ghi 1 kho?ng tr?ng
	putChar_LCD(' '); //ghi 1 kho?ng tr?ng
	putChar_LCD('D'); //Hi?n th? k�t? 'D'
	print_LCD("emo of the",10); //hi?n th? 1 chu?i k� t?
	move_LCD(2,1); //di chuy?n cursor ??n d�ng 2, c?t ??u ti�n
	print_LCD("2x16 LCD Display",16); //hi?n th? chu?i th? 2
	while(1){

	};
}
