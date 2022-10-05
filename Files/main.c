//Group 17
//Marco Stanco
//Georges Richard

#include <stdint.h>
#include <stdio.h>
#include <util/delay.h>
#include <avr/io.h>
#include "lcd_driver.h"
#include "port_macros.h"
#define PWM_TOP 100


unsigned int pwm_counter=0;
unsigned int duty_cycle=20;
unsigned int last_mid_button_state=0;
unsigned int mid_button_pressed=0;

int x=0;
int y=0;
int county=0;
int count=0;

void configure_all();
void move_fwd_inch();
void move_bwd_inch();
void turn_left();
void turn_right();

int main(){

configure_all();

last_mid_button_state = (PINB & (1<<4));

initialize_LCD_driver();

LCD_execute_command(TURN_ON_DISPLAY);

while(1)
{
//hold x value until ready (middle button pressed)
while(mid_button_pressed==0)
{
	if( (PINB & (1<<4)) != last_mid_button_state )
	{
		if( (PINB & (1<<4)) == 0 )
		{
			mid_button_pressed=1;
		}
	last_mid_button_state = (PINB & (1<<4));
	}
	else
	{
	mid_button_pressed=0;
	}
//x coordinate displaying on LCD
	if((PINB & (1<<1)) == 0)
	{
    count = (count+1)%400;
    if (count == 399)
		{
      x++;
			LCD_execute_command(CLEAR_DISPLAY);
    }
		if (x>30)
		{
			x=-30;
			count = (count+1)%400;
					if (count == 399)
					{
						x++;
					}
    }
	}

char xchar[5];
itoa(x,xchar,10);
LCD_move_cursor_to_col_row(0,2);
LCD_print_String("X: ");
LCD_move_cursor_to_col_row(3,2);
LCD_print_String(xchar);

//y-coordinate displaying on LCD
	if((PINB & (1<<5)) == 0)
	{
    county = (county+1)%400;
    if (county == 399)
		{
      y++;
			LCD_execute_command(CLEAR_DISPLAY);
    }
		if (y>30)
		{
			y=-30;
			county = (county+1)%400;
				if (county == 399)
				{
					y++;
				}
		}
	}

char ychar[5];
itoa(y,ychar,10);
LCD_move_cursor_to_col_row(0,1);
LCD_print_String("Y: ");
LCD_move_cursor_to_col_row(3,1);
LCD_print_String(ychar);
}

if(mid_button_pressed==1)
{
	_delay_us(1000000);
}

// if we are moving +x and +y
if ((x>0)&&(y>0))
{
	turn_right();
		for(int i=0; i<x; i++)
			{
			move_fwd_inch();
			}
	turn_left();
		for(int i=0; i<y; i++)
			{
			move_fwd_inch();
			}
}

// moving +x but -y
if((x>0)&&(y<0))
{
	turn_right();
	for(int i=0; i<x; i++)
		{
		move_fwd_inch();
		}
	turn_right();
		for(int i=0; i<abs(y); i++)
		{
			move_fwd_inch();
		}
}

//If we are moving -x and +y
if((x<0)&&(y>0))
{
	turn_left();
	for(int i=0; i<abs(x); i++)
	{
	move_fwd_inch();
	}
	turn_right();
		for(int i=0; i<y; i++)
		{
		move_fwd_inch();
		}
}

//moving -x and -y
if((x<0)&&(y<0))
{
	turn_left();
		for(int i=0; i<abs(x); i++)
		{
			move_fwd_inch();
		}
	turn_left();
		for(int i=0; i<abs(y); i++)
		{
		move_fwd_inch();
		}
}

// if x- coordinate is 0 and +y
if((x==0)&&(y>0))
{
		for(int i=0; i<y;i++)
		{
			move_fwd_inch();
		}
}

// if x-coordinate is 0 and -y
if((x==0)&&(y<0))
{
		for(int i=0; i<abs(y);i++)
		{
			move_bwd_inch();
		}
}

// if x-coordinate is neg and y is 0
if((x<0)&&(y==0))
{
	turn_left();
		for(int i=0; i<abs(x);i++)
		{
			move_fwd_inch();
		}
}

// if x-coordinate is pos and y is 0
if((x>0)&&(y==0))
{
	turn_right();
		for(int i=0; i<(x);i++)
		{
			move_fwd_inch();
		}
}

y=0;
x=0;
PORTD |= (1<<5); //Turn off M1
PORTD |= (1<<3); //Turn off M2
PORTD |= (1<<6); //Turn on M1
PORTB |= (1<<3); //Turn on M2
_delay_us(200);
}

    return 0;

}

//Define movement functions
void move_fwd_inch()
{
	for(int i=0; i<1365; i++)
	{
				while( pwm_counter < PWM_TOP )
				{
					if(pwm_counter<duty_cycle)
					{
						PORTD |= (1<<6); //Turn on M1
						PORTB |= (1<<3); //Turn on M2
						PORTD &= ~(1<<5);
						PORTD &= ~(1<<3);
					}
					else
					{
						PORTD |= (1<<5); //Turn off M1
						PORTD |= (1<<3); //Turn off M2
						PORTD |= (1<<6); //Turn on M1
						PORTB |= (1<<3); //Turn on M2
					}
					pwm_counter++;
				}
	pwm_counter=0;
	}
}

void move_bwd_inch()
{
	for(int i=0; i<1365; i++)
	{
				while( pwm_counter < PWM_TOP )
				{
					if(pwm_counter<duty_cycle)
					{
						PORTD &= ~(1<<6); //Turn on M1
						PORTB &= ~(1<<3); //Turn on M2
						PORTD |= (1<<5);
						PORTD |= (1<<3);
					}
					else
					{
						PORTD |= (1<<5); //Turn off M1
						PORTD |= (1<<3); //Turn off M2
						PORTD |= (1<<6); //Turn on M1
						PORTB |= (1<<3); //Turn on M2
					}
					pwm_counter++;
				}
	pwm_counter=0;
	}
}

void turn_right()
{
	_delay_us(500000);
	for(int i=0; i<3485; i++)//3475
	{
				while( pwm_counter < PWM_TOP )
				{
					if(pwm_counter<duty_cycle)
					{
						PORTD |= (1<<6); //Turn on M1
						PORTB &= ~(1<<3); //Turn on M2
						PORTD &= ~(1<<5);
						PORTD |=(1<<3);
					}
					else
					{
						PORTD |= (1<<5); //Turn off M1
						PORTD |= (1<<3); //Turn off M2
						PORTD |= (1<<6); //Turn on M1
						PORTB |= (1<<3); //Turn on M2
					}
					pwm_counter++;
				}
	pwm_counter=0;
	}
//	_delay_us(500000);
}

void turn_left()
{
	_delay_us(500000);
	for(int i=0; i<3275; i++)//3475
	{
				while( pwm_counter < PWM_TOP )
				{
					if(pwm_counter<duty_cycle)
					{
						PORTD &= ~(1<<6); //Turn on M1
						PORTB |= (1<<3); //Turn on M2
						PORTD |= (1<<5);
						PORTD &=~(1<<3);
					}
					else{
						PORTD |= (1<<5); //Turn off M1
						PORTD |= (1<<3); //Turn off M2
						PORTD |= (1<<6); //Turn on M1
						PORTB |= (1<<3); //Turn on M2
					}
					pwm_counter++;
				}
	pwm_counter=0;
	}
}

void configure_all()
{
	DDRD |= (1<<6); //configure pin as output
	DDRB |= (1<<3);
	DDRD |= (1<<5); //configure pin as output
	DDRD |= (1<<3);

	//Configure button
	DDRB &= ~(1<<1); //configure button as input
	PINB |= (1<<1);
	DDRB &= ~(1<<5); //configure button as input
	PINB |= (1<<5);
	DDRB &= ~(1<<4); //configure button as input
	PINB |= (1<<4);
}
