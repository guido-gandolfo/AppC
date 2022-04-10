#ifndef Teclado4x4

	#define Teclado4x4

	//Configuracion de puerto para teclado.
	//*******************************
	#define KEYPAD_PORT PTBD	
	#define KEYPAD_DDR 	PTBDD	
	#define KEYPAD_PIN 	PTBD	
	//*******************************

	int teclaPresionada(void);		// Lee tecla presionada del Teclado
	char KepadScan (char *pkey);
	
#endif
