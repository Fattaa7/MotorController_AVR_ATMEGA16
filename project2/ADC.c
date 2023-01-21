/*
 * ADC.c
 *
 *  Created on: Feb 16, 2021
 *      Author: ahmed
 */


#include "ADC.h"

#ifdef INT_MODE
volatile uint16 g_channel_data ;
#endif


void ADC_init(uint8 ref_mode)
{
	ADMUX &= (ref_mode << REFS0);

#ifdef HIGH_PRESENT
	ADMUX |= (1 << ADLAR);
#endif

	ADCSRA |= (1<< ADEN) | (ADC_FREQ & 0b11);

#ifdef INT_MODE
	ADCSRA |= (1<< ADIE);
#endif



}

#ifdef INT_MODE
void ADC_readChannel(uint8 ADC_channel)
{
	ADMUX &= ~(0b11111);
	ADMUX |= (ADC_channel & 0b11111);
	SET_BIT(ADCSRA,ADSC);
}

ISR(ADC_vect)
{
#ifdef HIGH_PRESENT
	g_channel_data = (ADC>>6);
#else
	g_channel_data = ADC;
#endif
}


#else
uint16 ADC_readChannel(uint8 ADC_channel)
{

	ADMUX &= ~(0b11111);
	ADMUX |= (ADC_channel & 0b11111);
	SET_BIT(ADCSRA,ADSC);

	while(BIT_IS_CLEAR(ADCSRA,ADIF));

	CLEAR_BIT(ADCSRA,ADIF);

#ifdef HIGH_PRESENT
	return (ADC>>6);
#else
	return ADC;
#endif
}

#endif
