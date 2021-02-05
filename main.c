#include <stdio.h>
#include "NUC1xx.h"
#include "SYS.h"
#include "GPIO.h"
#include "Seven_segment.h"
#include "Scankey.h"
#include "LCD.h"

void seg_display(int16_t value){
	
	int digit1, t;
	int8_t digit;
	digit = value / 1000;
	
	value = value - digit * 100;
	digit = value / 10;
	
	value = value - digit * 10;
	digit1 = value;
	
	for(t=0; t<16; t++){
		
		close_seven_segment();
		show_seven_segment(1,digit);
		DrvSYS_Delay(62500);
		
		close_seven_segment();
		show_seven_segment(0,digit1);
		DrvSYS_Delay(62500);
	}
	close_seven_segment();
}

void FirstTask(){
	DrvGPIO_ClrBit(E_GPC,12);
	DrvGPIO_ClrBit(E_GPC,13);
	DrvGPIO_ClrBit(E_GPC,14);
	DrvGPIO_ClrBit(E_GPC,15);
	
	DrvSYS_Delay(1000000);
	
	DrvGPIO_SetBit(E_GPC,12);  //output High to turn off LED
	DrvGPIO_SetBit(E_GPC,13);	 //output High to turn off LED
	DrvGPIO_SetBit(E_GPC,14);	 //output High to turn off LED
	DrvGPIO_SetBit(E_GPC,15);	 //output High to turn off LED

}

void SecondTask(){
	
	DrvGPIO_SetBit(E_GPC,12);
	DrvGPIO_SetBit(E_GPC,13);
	DrvGPIO_SetBit(E_GPC,14);
	DrvGPIO_SetBit(E_GPC,15);
	
	DrvSYS_Delay(300000);
	DrvGPIO_ClrBit(E_GPC,12); //output Low to turn on LED
	DrvSYS_Delay(300000);
	DrvGPIO_SetBit(E_GPC,12);
	DrvGPIO_ClrBit(E_GPC,13); //output Low to turn on LED
	DrvSYS_Delay(300000);
	DrvGPIO_SetBit(E_GPC,13);
	DrvGPIO_ClrBit(E_GPC,14); //output Low to turn on LED
	DrvSYS_Delay(300000);
	DrvGPIO_SetBit(E_GPC,14);
	DrvGPIO_ClrBit(E_GPC,15); //output Low to turn on LED
	DrvSYS_Delay(300000);
	DrvGPIO_SetBit(E_GPC,15);
}

void ThirdTask(){
	DrvGPIO_ClrBit(E_GPA,12); // GPA12 = Blue,  0 : on, 1 : off
  DrvGPIO_SetBit(E_GPA,13); 
  DrvGPIO_SetBit(E_GPA,14); 
	DrvSYS_Delay(1000000); 		   

	// set RGBled to Green
  DrvGPIO_SetBit(E_GPA,12); 
  DrvGPIO_ClrBit(E_GPA,13); // GPA13 = Green, 0 : on, 1 : off
  DrvGPIO_SetBit(E_GPA,14); 
	DrvSYS_Delay(1000000);			  

	// set RGBled to Red
  DrvGPIO_SetBit(E_GPA,12); 
  DrvGPIO_SetBit(E_GPA,13); 
  DrvGPIO_ClrBit(E_GPA,14); // GPA14 = Red,   0 : on, 1 : off
	DrvSYS_Delay(1000000);			  
	
	// set RGBled to off	 
  DrvGPIO_SetBit(E_GPA,12); // GPA12 = Blue,  0 : on, 1 : off
  DrvGPIO_SetBit(E_GPA,13); // GPA13 = Green, 0 : on, 1 : off
  DrvGPIO_SetBit(E_GPA,14); // GPA14 = Red,   0 : on, 1 : off
	DrvSYS_Delay(1000000);
	
}

void FourthTask(int number){ //initialize Buzz_GPIO
	int i;
	for (i = 0; i < number; i++){
		DrvGPIO_ClrBit(E_GPB,11);
		DrvSYS_Delay(1000000);
		DrvGPIO_SetBit(E_GPB, 11);
		DrvSYS_Delay(1000000);
	}
}

void FifthTask() {
	uint32_t i = 0;
	
	for(i = 0; i < 100; i++){
		seg_display(i);
	}
}

void Init_LED(){
	DrvGPIO_Open(E_GPC, 12, E_IO_OUTPUT);
	DrvGPIO_Open(E_GPC, 13, E_IO_OUTPUT);
	DrvGPIO_Open(E_GPC, 14, E_IO_OUTPUT);
	DrvGPIO_Open(E_GPC, 15, E_IO_OUTPUT);
	DrvGPIO_SetBit(E_GPC, 12);
	DrvGPIO_SetBit(E_GPC, 13);
	DrvGPIO_SetBit(E_GPC, 14);
	DrvGPIO_SetBit(E_GPC, 15);
}

void Init_RGB_LED(){}
	
int main(void){
	
	char TEXT0[16] = "LAB 1";
	char TEXT1[16] = "TASK";
	
	int8_t number;
	UNLOCKREG();
	DrvSYS_Open(50000000);
	
	LOCKREG();
	
	Init_LED();
	Init_RGB_LED();
	init_LCD();
	clear_LCD();
	OpenKeyPad();
	
	
	print_Line(0,TEXT0);
	while(1) {
		
		number = ScanKey();
		if(number != 0) {
			sprintf(TEXT1+8, "%d", number);
			print_Line(1, TEXT1);
		}
		
		switch(number){
			case 1: 
				FirstTask();
				break;
			case 2: 
				SecondTask();
				break;
			case 3: 
				ThirdTask();
				break;
			case 4:
				FourthTask(5);
				break;
			case 5:
				FifthTask();
				break;
			default:
				break;
		}
	}
}