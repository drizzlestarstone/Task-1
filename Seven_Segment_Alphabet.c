// CHAN TIAN WEN, 11/2/2021

#include <stdio.h>
#include <ctype.h>
#include "NUC1xx.h"
#include "GPIO.h"
#include "SYS.h"
#include "Seven_Segment.h"
#include "Seven_Segment_Alphabet.h"

//non-existent characters or undisplayable characters are mapped to all off
#define SEG_NONE	0xFF
#define SEG_A   0x22 
#define SEG_B   0x1A 
#define SEG_C   0x93 
#define SEG_D   0x0E 
#define SEG_E   0x13  
#define SEG_F   0x33 
#define SEG_G   0x12 
#define SEG_H   0x2A 
#define SEG_I   0xEE 
#define SEG_J   0x8E
#define SEG_K	 0x00
#define SEG_L  0x9B
#define SEG_M  0x00
#define SEG_N  0x3E
#define SEG_O  0x82
#define SEG_P  0x23
#define SEG_Q  0x62
#define SEG_R  0x3F
#define SEG_S  0x52
#define SEG_T  0x2B
#define SEG_U  0x8A
#define SEG_V  0x00
#define SEG_W  0x00
#define SEG_X  0x00
#define SEG_Y  0x4A
#define SEG_Z  0x00

unsigned short SEG_ALPHABET_BUF[27]={SEG_NONE, SEG_A, SEG_B, SEG_C, SEG_D, SEG_E, SEG_F, SEG_G, SEG_H, SEG_I, SEG_J, SEG_K, SEG_L, SEG_M, SEG_N, SEG_O, SEG_P, SEG_R, SEG_S, SEG_T, SEG_U, SEG_V, SEG_W, SEG_X, SEG_Y, SEG_Z}; 
char alphabet[26]={'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'}; 

void show_seven_segment_alphabet(unsigned char no, unsigned char number)
{
  unsigned short temp,i;
	temp=SEG_ALPHABET_BUF[number];
	
	for(i=0;i<8;i++)
	    {
		if((temp&0x01)==0x01)		   		   
		   DrvGPIO_SetBit(E_GPE,i);
		   else
		   DrvGPIO_ClrBit(E_GPE,i);		  
		   temp=temp>>1;
		}
		DrvGPIO_SetBit(E_GPC,4+no);	

}

// this function compares the letter of the word to the 26 alphabets
// and selects the index that corresponds to the right alphabet
int char_input(char letter) 
{
	int j=0;
	int number;
	char character;
	
	character = toupper(letter);
	for (j=0; j<26; j++) {
		if (character == alphabet[j]) {
			// we add one, because the SEG_ALPHABET_BUF and alphabet arrays have different number of indices
			//	SEG_ALPHABET_BUFF has an extra index for empty/off display (for characters that can't be displayed, like 'k')
			number = j+1;
			break;
		} else {
			number = 0;
		}
	}
	
	return number;
}

// user-added on function to display 4-char word on 7-segment LEDs
void seg_alphabet_display(char word[4])
{

	int alphabet_index[4];
	int i=0;
	
	//	this function gets the index of the right alphabet
	for (i=0;i<4;i++) {
		alphabet_index[i] = char_input(word[i]);
	}
	
	close_seven_segment();
	show_seven_segment_alphabet(3,alphabet_index[0]);
	DrvSYS_Delay(4500);
	
	close_seven_segment();
	show_seven_segment_alphabet(2,alphabet_index[1]);
	DrvSYS_Delay(4500);
	
	close_seven_segment();
	show_seven_segment_alphabet(1,alphabet_index[2]);
	DrvSYS_Delay(4500);
	
	close_seven_segment();
	show_seven_segment_alphabet(0,alphabet_index[3]);
	DrvSYS_Delay(4500);
}