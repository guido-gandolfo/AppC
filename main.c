#include <hidef.h> /* for EnableInterrupts macro */
#include "derivative.h" /* include peripheral declarations */
#include "MEF.h"
#include "lcd.h"
#include "reloj.h"

#ifdef __cplusplus
extern "C"
#endif


void MCU_init(void); /* Device initialization function declaration */
extern volatile char FLAG_temp;
extern volatile char FLAG_reloj;


void main(void) 
{
  volatile char state = 0;
  char timer = 0;
  MCU_init();	/* call Device Initialization */
  /* include your code here */
  LCD_init(DISPLAY_8X5|_2_LINES,DISPLAY_ON|CURSOR_OFF|CURSOR_NOBLINK);
  LCD_pos_xy(0,1); 
  LCD_write_string("CERRADO         ");

  for(;;)
  {
    state = mef(state, &timer);

    if (FLAG_reloj && timer > 0)
    {
      timer--;
      FLAG_temp = 0;
    }

    if(FLAG_reloj == 1)
		{
			reloj();
			FLAG_reloj=0;
		}
     __RESET_WATCHDOG(); /*By default COP is disabled with device init. When enabling, also reset the watchdog. */
  } /* loop forever */
  /* please make sure that you never leave main */
}
