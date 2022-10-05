F_CPU = 20000000
MCU = atmega328p
CCOPTS= -g -Wall -Os -std=c99

default: compile

all: program

compile: main.c  
	avr-gcc  $(CCOPTS) -mmcu=$(MCU) -DF_CPU=$(F_CPU) -o main -g main.c lcd_driver.o 
	    
hex: compile
	avr-strip main
	avr-objcopy -R .eeprom -O ihex main main.hex

program: hex
	avrdude -p m328p -c avrisp2 -P COM9 -U flash:w:main.hex

clean:
	rm main main.hex
