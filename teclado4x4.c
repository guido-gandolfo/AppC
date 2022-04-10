/******************************************************************************

Programa para leer teclado Matricial de NxM

Conexion al Teclado:

	COL1 ->	KEYPAD_PORT_Pin4
	COL2 ->	KEYPAD_PORT_Pin5
	COL3 ->	KEYPAD_PORT_Pin6
	COL4 -> KEYPAD_PORT_Pin7

	ROW1 ->	KEYPAD_PORT_Pin0
	ROW2 -> KEYPAD_PORT_Pin1
	ROW3 ->	KEYPAD_PORT_Pin2
	ROW4 -> KEYPAD_PORT_Pin3
	
*******************************************/

#include "Teclado4x4.h"
#include <derivative.h>


int teclaPresionada()
{
	unsigned char aux;
	PTBDD=0x0F;
	PTBPE=0xF0;

	PTBD=0xFE;
	aux = ~PTBD;
	
	if(aux&0x10) return '1';
	if(aux&0x20) return '2';
	if(aux&0x40) return '3';
	if(aux&0x80) return 'A';
	PTBD=0xFD;
	aux = ~PTBD;
	if(aux&0x10) return '4';
	if(aux&0x20) return '5';
	if(aux&0x40) return '6';
	if(aux&0x80) return 'B';
	PTBD=0xFB;
	aux = ~PTBD;
	if(aux&0x10) return '7';
	if(aux&0x20) return '8';
	if(aux&0x40) return '9';
	if(aux&0x80) return 'C';
	PTBD=0xF7;
	aux = ~PTBD;
	if(aux&0x10) return '*';
	if(aux&0x20) return '0';
	if(aux&0x40) return '#';
	if(aux&0x80) return 'D';
	
	return 0XFF;//Indica tecla No presionada
}

/********************************************************
FUNCION PARA ESCANEAR UN TECLADO MATRICIAL Y DEVOLVER LA 
TECLA PRESIONADA UNA SOLA VEZ. TIENE DOBLE VERIFICACION Y
MEMORIZA LA ULTIMA TECLA PRESIONADA
DEVUELVE: 
0 -> NO HAY NUEVA TECLA PRESIONADA
1 -> HAY NUEVA TECLA PRESIONADA Y ES *pkey


********************************************************/
char KepadScan (char *pkey) 
{
 static char Old_key;
 char Key, Last_valid_key=0xFF;       
 
 Key= (char )teclaPresionada();

 if(Key==0xFF) {   //NO_DATA
 	Old_key=0xFF;
	Last_valid_key=0xFF;
	return 0;
	}
 if(Key==Old_key) { //2da verificaci�n
 	if(Key!=Last_valid_key){ //evita m�ltiple detecci�n
		*pkey=Key;
		Last_valid_key=Key;
		return 1;
	}
 }
 Old_key=Key; //1era verificaci�n
 return 0;
}

