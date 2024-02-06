#include "stm32f10x.h"
#include "GPIO.h"
#include "KeyPad.h"
#include "LCD.h"
#include "Timer.h"
#include "stdio.h"
#include "RFID.h"
#include "SPI.h"
#include<stdlib.h>
#include<string.h>


char PASS[4]="123A";
char ID[5] = {0xB1, 0x77, 0x97, 0x1D, 0x4C};
uint8_t a=0;
uint8_t CardID[5];
char szBuff[100];

int main(void){
	GPIO_config();
	TIMER_Configuration();
	I2C_LCD_Configuration();
	HD44780_Init(2);
	HD44780_Clear();
	TM_MFRC522_Init();
	while (1) {
		GPIO_ResetBits (GPIOA,GPIO_Pin_10); // buzzer off
		HD44780_Clear();
		 HD44780_SetCursor (3,0);
		 HD44780_PrintStr ("BTL TKHTN");
		 Delay_Ms(500);
		 HD44780_SetCursor (0,1);
		 HD44780_PrintStr ("Door Lock System");
		 Delay_Ms(1500);
		 HD44780_Clear();
		 HD44780_SetCursor (0,0);
	   HD44780_PrintStr ("Choose Mode Open");
		 Delay_Ms(1500);
		 HD44780_Clear();
		 HD44780_SetCursor (0,0);
		 HD44780_PrintStr ("1.Enter PassWord");
		 HD44780_SetCursor (0,1);
		 HD44780_PrintStr ("2.Scan Your Card");
		char pass[4];
		char key= KEYPAD_NOT_PRESSED;
		while(key == KEYPAD_NOT_PRESSED){
			key = KEYPAD_Read();
		}
		if( key == '1'){ 
			char dem = '2';
			while(1){
			HD44780_Clear();
			HD44780_SetCursor (0,0);
			HD44780_PrintStr ("Enter PassWord");
			HD44780_SetCursor (4,1);
			HD44780_PrintStr ("_ _ _ _");
			for (int i=0;i<4;i++){
				HD44780_SetCursor (4+i*2,1);
				key= KEYPAD_NOT_PRESSED;
				while( key == KEYPAD_NOT_PRESSED){
					key = KEYPAD_Read();
				}
				pass[i] = key;
				HD44780_PrintSpecialChar(key);
				Delay_Ms(200);
				HD44780_SetCursor (4+i*2,1);
				HD44780_PrintSpecialChar('*');
			}
			Delay_Ms(500);
			a=0;
			for (int j=0;j<4;j++){
				if( pass[j] == PASS[j])
					a++;
			}
			HD44780_Clear();
			HD44780_SetCursor (0,0);
			 if ( a == 4){
				 HD44780_PrintStr ("Correct Pass");
				 GPIO_SetBits (GPIOA,GPIO_Pin_10); // buzzer on
				 Delay_Ms(200);
				 GPIO_ResetBits (GPIOA,GPIO_Pin_10); // buzzer on
				 Delay_Ms(200);
				 GPIO_SetBits (GPIOA,GPIO_Pin_10); // buzzer on
				 Delay_Ms(200);
				 GPIO_ResetBits (GPIOA,GPIO_Pin_10); // buzzer on
				 Delay_Ms(1000);
				 HD44780_Clear();
			   HD44780_SetCursor (0,0);
				 HD44780_PrintStr ("Door opening...");
				 GPIO_SetBits (GPIOA,GPIO_Pin_8); // IN1 motor
				 GPIO_ResetBits (GPIOA,GPIO_Pin_9); // IN2 motor
				 Delay_Ms(3000);
				 HD44780_Clear();
			   HD44780_SetCursor (0,0);
				 HD44780_PrintStr ("Welcome Back !");
				 GPIO_ResetBits (GPIOA,GPIO_Pin_8); // IN1 motor
				 GPIO_ResetBits (GPIOA,GPIO_Pin_9); // IN2 motor
				 Delay_Ms(2000);
				 HD44780_Clear();
				 HD44780_SetCursor (0,0);
				 HD44780_PrintStr ("Door closing...");
				 GPIO_ResetBits (GPIOA,GPIO_Pin_8); // IN1 motor
				 GPIO_SetBits (GPIOA,GPIO_Pin_9); // IN2 motor
				 Delay_Ms(3000);
				 GPIO_ResetBits (GPIOA,GPIO_Pin_9); // stop
				 break;
			 }
			 else{
				  if ( dem == '0'){
						GPIO_SetBits (GPIOA,GPIO_Pin_10); // buzzer on
					  HD44780_Clear();
						HD44780_SetCursor (0,0);
						HD44780_PrintStr ("Try again in:");
						Delay_Ms(500);
					 for (int k=10;k>0;k--){
						 if(k>9){
							 uint8_t x=k/10;
							 uint8_t y=k%10;
							HD44780_SetCursor (13,0);
							HD44780_PrintSpecialChar(x+48);
							HD44780_SetCursor (14,0);
							HD44780_PrintSpecialChar(y+48);
							 HD44780_SetCursor (15,0);
							HD44780_PrintSpecialChar('s');
							Delay_Ms(1000);
						 }
						 else{
						 HD44780_SetCursor (13,0);
					  	HD44780_PrintSpecialChar(' ');
						 HD44780_SetCursor (14,0);
						 HD44780_PrintSpecialChar(k+48);
						 HD44780_SetCursor (15,0);
						 HD44780_PrintSpecialChar('s');
						 Delay_Ms(1000);
						 if(k ==1) 
							 GPIO_ResetBits (GPIOA,GPIO_Pin_10); // buzzer off
					 }
						}
					break;
				 }
					else{
				 HD44780_PrintStr ("Incorrect Pass");
					HD44780_SetCursor (0,1);
					HD44780_PrintSpecialChar(dem);
					HD44780_SetCursor (2,1);
				  HD44780_PrintStr ("time left");
				  Delay_Ms(1000);
				 dem--;}
				 
				 }
			 }
		 }
		else if( key == '2') {
			char dem1 = '2';
			while(1){
			HD44780_Clear();
			HD44780_SetCursor (0,0);
			HD44780_PrintStr ("Scan your card");
		 	while (TM_MFRC522_Check(CardID) != MI_OK);
				sprintf(szBuff, "ID:%02X%02X%02X%02X%02X", CardID[0], CardID[1], CardID[2], CardID[3], CardID[4]);
		 HD44780_SetCursor (0,1);
				HD44780_PrintStr(szBuff);
			Delay_Ms(200);
			  for(int i=3;i<13;i++){
				HD44780_SetCursor (i,1);
				HD44780_PrintSpecialChar('*');
				Delay_Ms(50);
			}
			HD44780_Clear();
			HD44780_SetCursor (0,0);
			uint8_t check = 0;
			for( int i=0;i<5;i++){ 
				if(CardID[i] == ID[i])
					check++;
			}
			if (check == 5){
				HD44780_PrintStr("Correct ID"); 
					GPIO_SetBits (GPIOA,GPIO_Pin_10); // buzzer on
				 Delay_Ms(200);
				 GPIO_ResetBits (GPIOA,GPIO_Pin_10); // buzzer on
				 Delay_Ms(200);
				 GPIO_SetBits (GPIOA,GPIO_Pin_10); // buzzer on
				 Delay_Ms(200);
				 GPIO_ResetBits (GPIOA,GPIO_Pin_10); // buzzer on
				Delay_Ms(1000);
				HD44780_Clear();
				HD44780_SetCursor (0,0);
				HD44780_PrintStr ("Door opening...");
				 GPIO_SetBits (GPIOA,GPIO_Pin_8); // IN1 motor
				 GPIO_ResetBits (GPIOA,GPIO_Pin_9); // IN2 motor
				 Delay_Ms(3000);
				HD44780_Clear();
				HD44780_PrintStr ("Welcome Back !");
				 GPIO_ResetBits (GPIOA,GPIO_Pin_8); // IN1 motor
				 GPIO_ResetBits (GPIOA,GPIO_Pin_9); // IN2 motor
				 Delay_Ms(2000);
				HD44780_Clear();
				 HD44780_SetCursor (0,0);
				 HD44780_PrintStr ("Door closing...");
				 GPIO_ResetBits (GPIOA,GPIO_Pin_8); // IN1 motor
				 GPIO_SetBits (GPIOA,GPIO_Pin_9); // IN2 motor
				 Delay_Ms(3000);
				 GPIO_ResetBits (GPIOA,GPIO_Pin_9); // stop
				break;
			}
			else{
				if ( dem1 == '0'){
						GPIO_SetBits (GPIOA,GPIO_Pin_10); // buzzer on
					  HD44780_Clear();
						HD44780_SetCursor (0,0);
						HD44780_PrintStr ("Try again in:");
						Delay_Ms(500);
					 for (int k=10;k>0;k--){ 
						  if(k>9){
							 uint8_t x=k/10;
							 uint8_t y=k%10;
							HD44780_SetCursor (13,0);
							HD44780_PrintSpecialChar(x+48);
							HD44780_SetCursor (14,0);
							HD44780_PrintSpecialChar(y+48);
							 HD44780_SetCursor (15,0);
							HD44780_PrintSpecialChar('s');
							Delay_Ms(1000);
						 }
						 else{
						 HD44780_SetCursor (13,0);
					  	HD44780_PrintSpecialChar(' ');
						 HD44780_SetCursor (14,0);
						 HD44780_PrintSpecialChar(k+48);
						 HD44780_SetCursor (15,0);
						 HD44780_PrintSpecialChar('s');
						 Delay_Ms(1000);
						 if(k ==1) 
							 GPIO_ResetBits (GPIOA,GPIO_Pin_10); // buzzer off
					 }
						}
					break;
				 }
				else{
				HD44780_PrintStr ("Incorrect ID");
			    HD44780_SetCursor (0,1);
					HD44780_PrintSpecialChar(dem1);
					HD44780_SetCursor (2,1);
				  HD44780_PrintStr ("time scan left");
				  Delay_Ms(1500);
				 dem1--;
				}
			 }
			}
	}
}
			
}

		

			
			

