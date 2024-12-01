/*
 * IC_Tester.c
 *
 * Created: 11/24/2024 5:36:18 PM
 * Author : mo ali
 */ 

#include "main.h"
#include "ff.h"
#include "diskio.h"
// UART baud rate definition
#define F_CPU 16000000UL
#define BAUD 9600
#define MYUBRR F_CPU/16/BAUD-1

// Prototypes
void UART_Init(unsigned int ubrr);
void UART_SendByte(unsigned char data);
void UART_SendString(const char *str);
void SPI_Init(void);
uint8_t SPI_Transmit(uint8_t data);
char buffer[128];

// FATFS objects
FATFS fs;      // File system object
FIL fil;       // File object
FRESULT fr;
MOD_Pattern pattern = {.input_pins_size = 0 ,.input_pins = {0}};
IC_INFO ic ;
// spi 
void Get_Info(IC_INFO *ic_obj);									// get name ,Discretion and number of pins 
void Get_Pattern(char *pattern,uint8_t *End_Patterns_Flag);		// Get patterns one by one and if the patterns end set the "End_Patterns_Flag"

// lcd 
void show_String(char *name_of_IC);
uint8_t new_ic = 0;

int main(void)
{
    /* Replace with your application code */
    while (1) 
    {
		Get_Info(&ic);			
		while(1){
			Get_Pattern(&pattern_str,&new_ic);
			if (!new_ic){
				pattern_handling(pattern_str);
				
				if (ic.pins == 14 || ic.pins == 16)
					test_14_16pin();
				else if (ic.pins == 24)
					test_24pin();
				else {
					not_founded();
					break;
				}
				
				for (int i = 0 ; i < pattern.input_pins_size ; i++){
					if (!(	((pattern.logic>> pattern.input_pins[i]) & 0x01 )   == ((concat>> pattern.input_pins[i]) & 0x01) )){
						flag = 0 ;
						DDRA = 0x00;
						DDRB = 0x00;
						DDRC = 0x00;
						break;
					}
				}
			}
			if (flag){
				show_String(ic.Name);
			}
			else {
				flag = 1 ;
			}
		}
    }
}


// this function provide Direction ,logic of each pin and the position of input pins
void pattern_handling(char *pattern_string){
	uint8_t i ;
	uint8_t size = sizeof(pattern_string)/sizeof(char);
	for(i = 0 ; i < size ; i++){
		position = (1 << i);
		if (pattern_str[i] == 'L' || pattern_str[i] == 'H'){
			pattern.input_pins[pattern.input_pins_size] = i;
			pattern.input_pins_size++;
			pattern.Direction &= ~(position);
			pattern.logic = (pattern_str[i] == 'L') ? pattern.logic & ~position : pattern.logic | position;
		}
		else {
			if (pattern_str[i] == '0' || pattern_str[i] == 'G'){
				pattern.Direction |= position;
				pattern.logic &= ~(position);
			}
			else if (pattern_str[i] == '1' || pattern_str[i] == 'V'){
				pattern.Direction |= position;
				pattern.logic |= position;
			}
		}
	}
}


void test_14_16pin(void){
	DDRA = pattern.Direction ;
	DDRB = (pattern.Direction >> 8);
	PORTA = pattern.logic;
	PORTB = (pattern.logic >> 8);
	
	concat = PINA + (PINB << 8) ;
}
void test_24pin(void)
{
	DDRA = pattern.Direction ;
	DDRB = (pattern.Direction >> 8);
	DDRC = (pattern.Direction >> 16);
	PORTA = pattern.logic;
	PORTB = (pattern.logic >> 8);
	PORTB = (pattern.logic >> 16);
	
	concat = PINA + (PINB << 8) + (PINC << 16) ;
}
void not_founded(void){
	
}

// SPI
void Get_Info(IC_INFO *ic){
	
}

void Get_Pattern(char *pattern,uint8_t *End_Patterns_Flag)
{
	
}

void show_String(char *name_of_IC){
	
}
void UART_Init(unsigned int ubrr)
{
	UBRRH = (unsigned char)(ubrr >> 8);
	UBRRL = (unsigned char)ubrr;
	UCSRB = (1 << RXEN) | (1 << TXEN);  // Enable receiver and transmitter
	UCSRC = (1 << URSEL) | (3 << UCSZ0);  // 8 data bits, 1 stop bit
}

// UART send a byte
void UART_SendByte(unsigned char data)
{
	while (!(UCSRA & (1 << UDRE)));  // Wait until the buffer is empty
	UDR = data;
}

// UART send a string
void UART_SendString(const char *str)
{
	while (*str)
	{
		UART_SendByte(*str++);
	}
}

// SPI initialization
void SPI_Init(void)
{
	DDRB |= (1 << PORTB4) | (1 << PORTB5) | (1 << PORTB7);  // Set SS, MOSI, SCK as output
	DDRB &= ~(1 << PORTB6);  // Set MISO as input
	SPCR = (1 << SPE) | (1 << MSTR) | (1 << SPR0);  // Enable SPI, Master, set clock rate f/16
}

// SPI transmit data
uint8_t SPI_Transmit(uint8_t data)
{
	SPDR = data;  // Load data into SPI data register
	while (!(SPSR & (1 << SPIF)));  // Wait until transmission complete
	return SPDR;  // Return received data
}