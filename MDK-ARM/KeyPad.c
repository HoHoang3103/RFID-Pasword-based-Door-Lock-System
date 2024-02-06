#include "KeyPad.h"
const char Keypad_Button_Values[4][4] =  {{'1', '2', '3', 'A'},
																					{'4', '5', '6', 'B'},
																					{'7', '8', '9', 'C'},
																					{'*', '0', '#', 'D'},
                                         };
#define READ_COLUMN_1               GPIO_ReadInputDataBit (GPIOA, KEYPAD_COLUMN_1_PIN)
#define READ_COLUMN_2               GPIO_ReadInputDataBit (GPIOA, KEYPAD_COLUMN_2_PIN) 
#define READ_COLUMN_3               GPIO_ReadInputDataBit (GPIOA, KEYPAD_COLUMN_3_PIN) 
#define READ_COLUMN_4               GPIO_ReadInputDataBit (GPIOA, KEYPAD_COLUMN_4_PIN)    
char KEYPAD_Read(void){
	  char check;
    /*Set ROW_1 LOW and scan all the columns*/
	GPIO_SetBits (GPIOA, KEYPAD_ROW_2_PIN);//SET_ROW_2_HIGH;
	GPIO_SetBits (GPIOA, KEYPAD_ROW_3_PIN);//SET_ROW_3_HIGH;
	GPIO_SetBits (GPIOA, KEYPAD_ROW_4_PIN);//SET_ROW_4_HIGH;
  GPIO_ResetBits (GPIOA, KEYPAD_ROW_1_PIN);//SET_ROW_1_LOW;
    check = Check_Keypad_Column(1);
    if(check)
    	return check;

    /*Set ROW_2 LOW and scan all the columns*/
  GPIO_SetBits (GPIOA, KEYPAD_ROW_1_PIN);// SET_ROW_1_HIGH;
	GPIO_SetBits (GPIOA, KEYPAD_ROW_3_PIN);//SET_ROW_3_HIGH;
	GPIO_SetBits (GPIOA, KEYPAD_ROW_4_PIN);//SET_ROW_4_HIGH;
   GPIO_ResetBits (GPIOA, KEYPAD_ROW_2_PIN);//SET_ROW_2_LOW;
    check = Check_Keypad_Column(2);
    if(check)
    	return check;
		
    /*Set ROW_3 LOW and scan all the columns*/
  GPIO_SetBits (GPIOA, KEYPAD_ROW_1_PIN);//SET_ROW_1_HIGH;
	GPIO_SetBits (GPIOA, KEYPAD_ROW_2_PIN);//SET_ROW_2_HIGH;
	GPIO_SetBits (GPIOA, KEYPAD_ROW_4_PIN);//SET_ROW_4_HIGH;
  GPIO_ResetBits (GPIOA, KEYPAD_ROW_3_PIN);//SET_ROW_3_LOW;
    check = Check_Keypad_Column(3);
    if(check)
    	return check;
    /*Set ROW_4 LOW and scan all the columns*/
   GPIO_SetBits (GPIOA, KEYPAD_ROW_1_PIN);// SET_ROW_1_HIGH;
	GPIO_SetBits (GPIOA, KEYPAD_ROW_2_PIN);//SET_ROW_2_HIGH;
	GPIO_SetBits (GPIOA, KEYPAD_ROW_3_PIN);//SET_ROW_3_HIGH;
   GPIO_ResetBits (GPIOA, KEYPAD_ROW_4_PIN);// SET_ROW_4_LOW;
    check = Check_Keypad_Column(4);
    if(check)
    	return check;
    /*Key not pressed */
    return KEYPAD_NOT_PRESSED;
	
	
}

static char Check_Keypad_Column(uint8_t Row){
	if(!READ_COLUMN_1)                           //If COLUMN_1 is LOW
	{ while(!READ_COLUMN_1){};
		for (int i=50;i>1;i--){
		 if(!READ_COLUMN_1){
			 i=50;
			 while(!READ_COLUMN_1){}; // cho neu chua nha nut
		 }
	 }
		return Keypad_Button_Values[Row-1][0];
	}

	if(!READ_COLUMN_2)                           //If COLUMN_2 is LOW  
	{ while(!READ_COLUMN_2){};
		for (int i=50;i>1;i--){
		 if(!READ_COLUMN_2){
			 i=50;
			 while(!READ_COLUMN_2){}; // cho neu chua nha nut
		 }
}
		return Keypad_Button_Values[Row-1][1];
	}

    if(!READ_COLUMN_3)                           //If COLUMN_3 is LOW
	{ while(!READ_COLUMN_3){};
		for (int i=50;i>1;i--){
		 if(!READ_COLUMN_3){
			 i=50;
			 while(!READ_COLUMN_3){}; // cho neu chua nha nut
		 }
}
		return Keypad_Button_Values[Row-1][2];
	}

	if(!READ_COLUMN_4)                           //If COLUMN_3 is LOW
	{ while(!READ_COLUMN_4){};
		for (int i=50;i>1;i--){
		 if(!READ_COLUMN_4){
			 i=50;
			 while(!READ_COLUMN_4){}; // cho neu chua nha nut
		 }
}
		return Keypad_Button_Values[Row-1][3];
	}

	return KEYPAD_NOT_PRESSED;                   //If NO Key is pressed
}
