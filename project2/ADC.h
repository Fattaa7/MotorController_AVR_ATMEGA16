/*
 * ADC.h
 *
 *  Created on: Feb 16, 2021
 *      Author: ahmed
 */

#ifndef ADC_H_
#define ADC_H_

#include "common_macros.h"
#include "micro_config.h"
#include "std_types.h"
#include <avr/interrupt.h>


/******************* Configurations *********************/

#define HIGH_PRESENT /* sets ADLAR to 1 and ADC value occupies the higher part of the register -- undef for lower part of the register */
#define INT_MODE /* undef for polling mode */

#define ADC_FREQ 0b11 /* ADC prescaler = 8 */

#define AREF 0
#define AVCC 0b01

/******************* Function Prototypes ********************/

void ADC_init(uint8 ref_mode);

#ifdef INT_MODE
extern volatile uint16 g_channel_data;
void ADC_readChannel(uint8 ADC_channel);
#else
uint16 ADC_readChannel(uint8 ADC_channel);
#endif



#endif /* ADC_H_ */
