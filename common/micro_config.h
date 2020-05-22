/*********************************************************************************************************************************
 *  Filename: micro_config.h
 *
 *  Description: file containing all libraries of AVR
 *
 *  Created on: Dec 27, 2019
 *
 *  Author: Shabrawy
 ********************************************************************************************************************************/

#ifndef MICRO_CONFIG_H_
#define MICRO_CONFIG_H_

#ifdef F_CPU
#undef F_CPU
#define F_CPU 8000000U /*since it didn't change when I created project in eclipse config*/
#endif


#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#endif /* MICRO_CONFIG_H_ */
