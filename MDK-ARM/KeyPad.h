#ifndef KEYPAD
#define KEYPAD

#include "stm32f10x.h"

	#define KEYPAD_NOT_PRESSED			'\0'

/* Row 1 default */

#define KEYPAD_ROW_1_PIN			  GPIO_Pin_4

/* Row 2 default */

#define KEYPAD_ROW_2_PIN			  GPIO_Pin_5

/* Row 3 default */

#define KEYPAD_ROW_3_PIN			  GPIO_Pin_6
/* Row 4 default */

#define KEYPAD_ROW_4_PIN			  GPIO_Pin_7

/* Columns ~ INPUT */
/* Column 1 default */

#define KEYPAD_COLUMN_1_PIN			GPIO_Pin_0

/* Column 2 default */

#define KEYPAD_COLUMN_2_PIN			GPIO_Pin_1

/* Column 3 default */

#define KEYPAD_COLUMN_3_PIN			GPIO_Pin_2

/* Column 4 default */

#define KEYPAD_COLUMN_4_PIN			GPIO_Pin_3

char KEYPAD_Read(void);
static char Check_Keypad_Column(uint8_t Row);



#endif
