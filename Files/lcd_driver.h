#ifndef LCD_DRIVER_H
#define LCD_DRIVER_H

#include <stdint.h>

#define DB0_PORT B
#define DB0_LOC 1
#define DB1_PORT B
#define DB1_LOC 4
#define DB2_PORT B
#define DB2_LOC 5
#define DB3_PORT D
#define DB3_LOC 7
#define RS_PORT D
#define RS_LOC 2
#define RW_PORT B
#define RW_LOC 0
#define E_PORT D
#define E_LOC 4

typedef enum { 	
	TURN_OFF_DISPLAY	=0x00, 
	CLEAR_DISPLAY		=0x01,
	MOVE_CURSOR_HOME 	=0x02,
	TURN_ON_DISPLAY		=0x0C,
	TURN_ON_STEADY_CURSOR  	=0x0E,
	TURN_ON_BLINKING_CURSOR	=0x0F
} lcd_command_t;


void initialize_LCD_driver();
void LCD_print_String(const char *str);
void LCD_move_cursor_to_col_row(uint8_t column, uint8_t row);
void LCD_execute_command( lcd_command_t);
void LCD_print_hex4( uint8_t);
void LCD_print_hex8( uint8_t);
void LCD_print_hex16( uint16_t);

#endif