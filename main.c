// CHAN TIAN WEN, 11/2/2021

//	26 letters have been mapped to their corresponding 26 hexadecimal numbers in the Seven_Segment_Alphabet.c file
//	Make sure to include the "Seven_Segment_Alphabet.h" header file as well
//	To display on 7-segment, simply input the word into the function seg_alphabet_display(word)
//	Remember that maximum length of word should only be 4


#include <stdio.h>
#include <string.h>
#include "NUC1xx.h"
#include "GPIO.h"
#include "SYS.h"
#include "Seven_Segment.h"
#include "Seven_Segment_Alphabet.h"

int main(void) {
	
	int i,j=0;
	char word[4] = "FGHI";
		
	for (j=0; j<100; i++) {
			seg_alphabet_display(word);
	}
	
	close_seven_segment();

}