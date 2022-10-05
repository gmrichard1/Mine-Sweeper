#include <stdint.h>
#include <stdio.h>
#include <util/delay.h>
#include <avr/io.h>
#include "lcd_driver.h"
#include "port_macros.h"

int main(){
//Configure button
DDRB |= (1<<1); //configure button as input
PORTB |= (1<<1);

int x = 0;
while(1){
	if(PORTB & (1<<1) == 0){
		x++;
	}
char xchar[5];
itoa(x,xchar,10);
initialize_LCD_driver();
LCD_execute_command(TURN_ON_DISPLAY);
LCD_execute_command(CLEAR_DISPLAY);
LCD_print_String(xchar);
}
}
