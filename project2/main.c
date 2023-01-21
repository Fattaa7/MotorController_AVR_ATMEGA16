/*
 * main.c
 *
 *  Created on: Feb 17, 2021
 *      Author: ahmed
 */


#include "ADC.h"
#include "LCD.h"
#include "motor.h"

/*
 * Macro to clear additional numbers in LCD
 */
#define clearUnwantedNumbers()  \
{\
	if(g_channel_data < 1000)\
			{\
\
				LCD_goToRowColumn(0,15);\
				LCD_displayCharacter(' ');\
				if(g_channel_data < 100)\
				{\
					LCD_goToRowColumn(0,14);\
					LCD_displayCharacter(' ');\
					if(g_channel_data < 10)\
					{\
						LCD_goToRowColumn(0,13);\
						LCD_displayCharacter(' ');\
					}\
				}\
			}\
}\

/*
 * ISR for Int1 to toggle the direction of motor
 */
ISR(INT1_vect)
{
	motor_toggleDirection();
}



int main(void)
{
	/*
	 * Initialize Interrupt 1
	 */
	CLEAR_BIT(DDRD,PD3);
	SET_BIT(GICR,INT1);
	SET_BIT(MCUCR,ISC11);
	SET_BIT(MCUCR,ISC10);

	SREG |= (1<<7); /* setting I-bit to 1 */

	LCD_init();
	LCD_displayString("ADC value =");

	ADC_init(AVCC); /* initialize ADC with AVCC */

	motor_init();

	while(1)
	{
		ADC_readChannel(0); /* reading channel0 in PA0 */

		LCD_goToRowColumn(0,12);
		LCD_intgerToString(g_channel_data);

		motor_changeSpeed(g_channel_data/4); /* divided by 4 since Timer0 is 8-bit timer */

		clearUnwantedNumbers();

	}


}
