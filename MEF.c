/*
 * MEF.C
 *
 *  Created on: 25-May-2019
 *      Author: Agust�n
 */
#include "Teclado4x4.h"
#include "lcd.h"

char mef (char state, char *timer)
{
    static volatile char iter = 0,
                         areEquals[4] = {0,0,0,0},
                         password[4] = {'2','5','8','0'},
                         newPassword[4] = {'*','*','*','*'};
    char i,
		 button = ' ';
                         

    switch (state)
    {
        case 0: // Closed
            if(KepadScan(&button))
            {
                switch (button)
                {
                    case '0':
                    case '1':
                    case '2':
                    case '3':
                    case '4':
                    case '5':
                    case '6':
                    case '7':
                    case '8':
                    case '9':
                            LCD_pos_xy(0,1); 
                            LCD_write_string("Ingrese clave   ");
                            iter = 0;
                            if (button == password[iter])
                            {
                                areEquals[iter] = 1;
                            }
                            iter++;                               
                            *timer = 5;
                            return 1; //ingreso Contrasena
                        break;

                    case 'D':
                            LCD_pos_xy(0,1); 
                            LCD_write_string("Ingrese clave   ");
                            iter = 0;
                            *timer = 5;
                            return 3; //cambio Contrasena
                        break;
                
                    default:
                            return 0; //Closed
                        break;   
                }
            }
            return 0;
            break;
        
        case 1: //ingreso Contrasena
            if(KepadScan(&button))
            {
                switch (button)
                {
                    case '0':
                    case '1':
                    case '2':
                    case '3':
                    case '4':
                    case '5':
                    case '6':
                    case '7':
                    case '8':
                    case '9':
                            *timer = 5;
                            if (button == password[iter])
                            {
                                areEquals[iter] = 1;
                            }
                            iter++;                            
                            if (iter > 3)
                                {
                                    if (areEquals[0] && areEquals[1] && areEquals[2] && areEquals[3])
                                    {
                                        iter = 0;
                                        LCD_pos_xy(0,1);          			// set cursor to the second column of the second line
                                        LCD_write_string("ABIERTO         ");
                                        *timer = 5;                
                                        return 2; //Abierto
                                    }
                                    else
                                    {
                                        LCD_pos_xy(0,1); 
                                        LCD_write_string("DENEGADO        ");
                                        *timer = 2;      
                                        return 6; //Denegado
                                    } 
                                }
                        break;           
                    default:
                            return 1;
                        break;   
                }
            }

            if (*timer < 0)
                {
                    LCD_pos_xy(0,1); 
                    LCD_write_string("CERRADO         ");
                    areEquals[0]= 0;
                    newPassword[0]= '*';
                    areEquals[1]= 0;
                    newPassword[1]= '*';
                    areEquals[2]= 0;
                    newPassword[2]= '*';
                    areEquals[3]= 0;
                    newPassword[3]= '*';
                    iter = 0;
                    return 0;
                }
                else
                {
                    return 1;
                }
            

        case 2: //Abierto
            if (*timer <= 0)
            {
                LCD_pos_xy(0,1); 
                LCD_write_string("CERRADO         ");
                areEquals[0]= 0;
                newPassword[0]= '*';
                areEquals[1]= 0;
                newPassword[1]= '*';
                areEquals[2]= 0;
                newPassword[2]= '*';
                areEquals[3]= 0;
                newPassword[3]= '*';
                iter = 0;
                return 0;                
            }
            else
            {
                return 2;
            }
            
        
        case 3: //modificar Contrasena
            if(KepadScan(&button))
            {
                switch (button)
                {
                    case '0':
                    case '1':
                    case '2':
                    case '3':
                    case '4':
                    case '5':
                    case '6':
                    case '7':
                    case '8':
                    case '9':
                            *timer = 5;
                            if (button == password[iter])
                            {
                                areEquals[iter] = 1;
                            } 
                            iter++;                           
                            if (iter > 3)
                                {
                                    if (areEquals[0] && areEquals[1] && areEquals[2] && areEquals[3])
                                    {
                                        iter = 0;
                                        LCD_pos_xy(0,1);          			// set cursor to the second column of the second line
                                        LCD_write_string("Nueva Clave     ");
                                        *timer = 5;                
                                        return 4; //Nueva Contrasena
                                    }
                                    else
                                    {
                                        LCD_pos_xy(0,1); 
                                        LCD_write_string("DENEGADO        ");
                                        *timer = 2;      
                                        return 6; //Denegado
                                    } 
                                }
                        break;           
                    default:
                            return 3;
                        break;   
                }
            }

            if (*timer < 0)
                {
                    LCD_pos_xy(0,1); 
                    LCD_write_string("CERRADO         ");
                    areEquals[0]= 0;
                    newPassword[0]= '*';
                    areEquals[1]= 0;
                    newPassword[1]= '*';
                    areEquals[2]= 0;
                    newPassword[2]= '*';
                    areEquals[3]= 0;
                    newPassword[3]= '*';
                    iter = 0;
                    return 0;
                }
                else
                {
                    return 3;
                }
             

        case 4: //nueva Contrasena
            if(KepadScan(&button))
            {
                switch (button)
                {
                    case '0':
                    case '1':
                    case '2':
                    case '3':
                    case '4':
                    case '5':
                    case '6':
                    case '7':
                    case '8':
                    case '9':
                            *timer = 5;
                            newPassword[iter] = button;
                            iter++;
                            if (iter > 3)
                            {
                                for (i = 0; i < 4; i++)
                                {
                                    password[i] = newPassword[i];
                                }
                                iter = 0;
                                LCD_pos_xy(0,1);          			// set cursor to the second column of the second line
                                LCD_write_string("Clave cambiada  ");
                                *timer = 5;                
                                return 5; //claveCambiada
                            }         
                    default:
                            return 4;
                        break;   
                }
            }

            if (*timer < 0)
                {
                    LCD_pos_xy(0,1); 
                    LCD_write_string("CERRADO         ");
                    areEquals[0]= 0;
                    newPassword[0]= '*';
                    areEquals[1]= 0;
                    newPassword[1]= '*';
                    areEquals[2]= 0;
                    newPassword[2]= '*';
                    areEquals[3]= 0;
                    newPassword[3]= '*';
                    iter = 0;
                    return 0;
                }
            else
                {
                    return 4;
                }

        case 5: //claveCambiada
            if (*timer <= 0)
            {
                LCD_pos_xy(0,1); 
                LCD_write_string("CERRADO         ");
                areEquals[0]= 0;
                newPassword[0]= '*';
                areEquals[1]= 0;
                newPassword[1]= '*';
                areEquals[2]= 0;
                newPassword[2]= '*';
                areEquals[3]= 0;
                newPassword[3]= '*';
                iter = 0;
                return 0;                
            }
            else
            {
                return 5;
            } 
        case 6: //DENEGADO
            if (*timer <= 0)
            {
                LCD_pos_xy(0,1); 
                LCD_write_string("CERRADO         ");
                areEquals[0]= 0;
                newPassword[0]= '*';
                areEquals[1]= 0;
                newPassword[1]= '*';
                areEquals[2]= 0;
                newPassword[2]= '*';
                areEquals[3]= 0;
                newPassword[3]= '*';
                iter = 0;
                return 0;                
            }
            else
            {
                return 6;
            }  
        default:
                LCD_pos_xy(0,1); 
                LCD_write_string("Sin Servicio    ");                
                areEquals[0]= 0;
                newPassword[0]= '*';
                areEquals[1]= 0;
                newPassword[1]= '*';
                areEquals[2]= 0;
                newPassword[2]= '*';
                areEquals[3]= 0;
                newPassword[3]= '*';
                iter = 0;
                return 0;
        break;
    }
}
