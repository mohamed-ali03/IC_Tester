/*
 * IC_data.h
 *
 * Created: 11/24/2024 6:01:12 PM
 *  Author: mo ali
 */ 


#ifndef IC_DATA_H_
#define IC_DATA_H_

#include "STD_Library.h"

typedef struct {
	char *Name ;
	char *text ;
	uint8_t pins ;
}IC_INFO;


// after triggering pattern_handling
typedef struct{
	uint32_t Direction ;
	uint32_t logic;
	uint8_t input_pins[12] ;  //maximum number of pins that act as input in the these families (74xxx, 40xxx,45xxx) is 12
	uint8_t input_pins_size  ;
}MOD_Pattern;

#endif /* IC_DATA_H_ */