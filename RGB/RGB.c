/**
* @file RGB.c
* @brief LIB to control the RGB-LED on the ZLV-Mint Board
*
* *******************************
* Date      Vers.   Name            Comment/Change
* 17.09.19  1.0     Kenneth Mathis  Created
*
* @author Kenneth Mathis
* @version 1.0
*/

#include "RGB.h"

// ***RGB LED***
void rgb(color newColor){
	PORTB |= (newColor.red<<5)|(newColor.green<<6)|(newColor.blue<<7);
	
	//Because a 0 turns anything off with an "and-set", its necessary to set every bit outside of
	//the RGB bits to 1. Thats why there is a |0x8f (|0b1000 1111) at the end.
	PORTB &= (newColor.red<<5)|(newColor.green<<6)|(newColor.blue<<7)|0x1f;
}