/*
 * main.h
 *
 * Created: 11/24/2024 6:00:50 PM
 *  Author: mo ali
 */ 


#ifndef MAIN_H_
#define MAIN_H_

#include "IC_data.h"

void pattern_handling(char *pattern_string);
void test_14_16pin(void);
void test_24pin(void);
void not_founded(void);

// input from file
char *Name ;
char *text ;
uint8_t Number_of_pins ;
char *pattern_str = "00000HG0HH000V";




// used in pattern_handling
int position ;

// used to concatenate PINA ,PINB and PINC together
uint16_t concat ;

//
uint8_t flag = 1 ;




#endif /* MAIN_H_ */