#include "lcd.h" 

void reloj(void){
	static char seg= 0,
				min= 0,
				hour= 0;
	static char cadena[]="00:00:00        ";
	
	if(++seg>59){
		seg= 0;
		if (++min>59){
			min= 0;
			if (++hour>23){
				hour= 0;
			}
		}
	}
	cadena[0]= hour/10+'0';
	cadena[1]= hour%10+'0';
	cadena[3]= min/10+'0';
	cadena[4]= min%10+'0';
	cadena[6]= seg/10+'0';
	cadena[7]= seg%10+'0'; 
	
	LCD_pos_xy(0,0);          			// set cursor to the second column of the second line
	LCD_write_string(cadena);
	
}
