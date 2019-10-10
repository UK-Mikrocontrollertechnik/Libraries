/**
* @file lcd.c
* @brief LIB to control the LCD char display on the ZLV-Mint Board
* @author Kenneth Mathis
* @version 1.1
*
* *******************************
* Date      Vers.   Name            Comment/Change
* 01.10.19  1.0     Kenneth Mathis  Created
* 10.10.19  1.1     Kenneth Mathis  Added writeString
*
*/

//***INCLUDES***
#define F_CPU 16000000UL
#include <util/delay.h>
#include <avr/io.h>
#include "lcd.h"

//***DEFINES***
//**Ports**
#define readWrite_On PORTL |= (1<<1) //Read
#define readWrite_Off PORTL &= ~(1<<1)//Write
#define registerSelect_On PORTL |= (1<<0) //Data
#define registerSelect_Off PORTL &= ~(1<<0)//Instruction
#define enable_On PORTL |= (1<<2)
#define enable_Off PORTL &= ~(1<<2)

//**Data Bus Pins**
#define DB4_On (PORTL|= (1<<4))
#define DB4_Off (PORTL &= ~(1<<4))
#define DB5_On (PORTL |= (1<<5))
#define DB5_Off (PORTL &= ~(1<<5))
#define DB6_On (PORTL |= (1<<6))
#define DB6_Off (PORTL &= ~(1<<6))
#define DB7_On (PORTL |= (1<<7))
#define DB7_Off (PORTL &= ~(1<<7))

//***PROTOTYPES***
void write4Bits(uint8_t value);
int lcdPutS(char, FILE *);

//***GLOBAL VARS***
static FILE lcdstdout = FDEV_SETUP_STREAM(lcdPutS, NULL, _FDEV_SETUP_WRITE);

void lcd_init(void){
	stdout = &lcdstdout;
	
	DDRL = 0xff;
	_delay_ms(50);
	registerSelect_Off;
	enable_Off;
	readWrite_Off;
	
	// we start in 8bit mode, try to set 4 bit mode thrice
	write4Bits(0x03);
	_delay_ms(5);
	write4Bits(0x03);
	_delay_ms(5);
	write4Bits(0x03);
	_delay_us(150);

	//set to 4-bit interface
	write4Bits(0x02);

	lcd_sendCommand(LCD_FUNCTIONSET | LCD_4BITMODE | LCD_2LINE | LCD_5x8DOTS);
	lcd_sendCommand(LCD_DISPLAYCONTROL | LCD_DISPLAY_ON | LCD_CURSOR_ON | LCD_BLINK_ON);
	lcd_sendCommand(LCD_CLEARDISPLAY);
	lcd_sendCommand(LCD_ENTRYMODESET | LCD_ENTRYLEFT | LCD_ENTRYSHIFTDECREMENT);
}

void lcd_sendCommand(uint8_t theCommand){
	registerSelect_Off; //Send Command
	readWrite_Off; //Write Mode
	write4Bits(theCommand>>4);
	write4Bits(theCommand);
	_delay_ms(1);
}

void lcd_sendData(uint8_t theData){
	registerSelect_On; //Send Data
	readWrite_Off; //Write Mode
	write4Bits(theData>>4);
	write4Bits(theData);
	_delay_ms(5);
}

void lcd_writeString(uint8_t *text) {
	while (*text) lcd_sendData(*text++);
}

void lcd_setCursor(uint8_t col, uint8_t row){
	if(col<16){
		if(row) lcd_sendCommand(LCD_SETDDRAMADDR | (col+0x40));
		else lcd_sendCommand(LCD_SETDDRAMADDR | col);
	}
}

/**
* @brief Takes a char from printf and puts it on the LCD. Filters illegal chars.
* @param value The four bits to send. (Less significant nibble is sent!)
*/
int lcdPutS(char var, FILE *stream){
	if(var>31 && var<126) lcd_sendData(var); //Filter out special and non-ascii char's
	return 0;
}

/**
* @brief Sends four bits at the same time to the LCD
* @param value The four bits to send. (Less significant nibble is sent!)
*/
void write4Bits(uint8_t value){
	(value&(1<<0)) ? DB4_On : DB4_Off;
	(value&(1<<1)) ? DB5_On : DB5_Off;
	(value&(1<<2)) ? DB6_On : DB6_Off;
	(value&(1<<3)) ? DB7_On : DB7_Off;
	
	/*
	PORTL |= (value<<4);
	PORTL &= (value<<4)|0x0f;*/
	
	//*Do A Clock Tick*
	enable_On;
	_delay_us(1);    //enable pulse, must be >450ns
	enable_Off;
	_delay_us(100);   //command needs over 37us to settle
}