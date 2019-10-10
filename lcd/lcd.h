/**
* @file lcd.h
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


#ifndef LCD_H
#define LCD_H
	#include <stdio.h>

	//**commands**
	#define LCD_CLEARDISPLAY 0x01
	#define LCD_RETURNHOME 0x02
	#define LCD_ENTRYMODESET 0x04
	#define LCD_DISPLAYCONTROL 0x08
	#define LCD_CURSORSHIFT 0x10
	#define LCD_FUNCTIONSET 0x20
	#define LCD_SETCGRAMADDR 0x40
	#define LCD_SETDDRAMADDR 0x80

	//*flags for display entry mode*
	#define LCD_ENTRYRIGHT 0x00
	#define LCD_ENTRYLEFT 0x02
	#define LCD_ENTRYSHIFTINCREMENT 0x01
	#define LCD_ENTRYSHIFTDECREMENT 0x00

	//*flags for display on/off control*
	#define LCD_DISPLAY_ON 0x04
	#define LCD_DISPLAY_OFF 0x00
	#define LCD_CURSOR_ON 0x02
	#define LCD_CURSOR_OFF 0x00
	#define LCD_BLINK_ON 0x01
	#define LCD_BLINK_OFF 0x00

	//*flags for display/cursor shift*
	#define LCD_DISPLAYMOVE 0x08
	#define LCD_CURSORMOVE 0x00
	#define LCD_MOVERIGHT 0x04
	#define LCD_MOVELEFT 0x00

	//*flags for function set*
	#define LCD_4BITMODE 0x00
	#define LCD_1LINE 0x00
	#define LCD_2LINE 0x08
	#define LCD_5x8DOTS 0x00
	
	/**
	* @brief Initialize the LCD
	* @param void
	*/
	void lcd_init(void);
	
	/**
	* @brief Send a command to the LCD
	* @param theCommand The command to be sent to the display
	*/
	void lcd_sendCommand(uint8_t theCommand);
	
	/**
	* @brief Send data to the LCD
	* @param theData The data to be sent to the display
	*/
	void lcd_sendData(uint8_t theData);
	
	/**
	* @brief Set a new cursor position
	* @param col The new column the cursor should be on
	*/
	void lcd_setCursor(uint8_t col, uint8_t row);
	
	/**
	* @brief Print an array of char's on the LCD
	* @param text A string which needs to be printed
	*/
	void lcd_writeString(uint8_t *text);

#endif