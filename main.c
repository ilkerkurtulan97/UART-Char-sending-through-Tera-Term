//APB1 bit 17	:USART2
//USART connected to PA2

#include "stm32f4xx.h"

void USART2_Init(void);
void USART_write(int ch);
void delayMs(int delay);

int main(void)
{
	USART2_Init();
	while(1){
		
		USART_write('Y');
		USART_write('i');
		delayMs(10);
	}
	
	
}

void USART2_Init(void){
	
	RCC->APB1ENR	|= 0x20000;
	RCC->AHB1ENR	|= 1;
	
	GPIOA->AFR[0]	= 0x0700; // Writing 0 because USART is connected to Low register which is 0
	GPIOA->MODER	|= 0x0020; //SET PA2 alternate function
	
	USART2->BRR	= 0x0683; //9600 @16MHZ Baudrate
	USART2->CR1	=	0x0008;	// Enable Tx
	USART2->CR1	|=	0x2000;
	
}

void USART_write(int ch){
	
	// Wait while TX buffer is empty
	while(!(USART2->SR & 0x0080)){}
		USART2->DR = (ch & 0xFF);
		
}

void delayMs(int delay)
{
	
	int i;
	
	for(;delay>0;delay--)
	{
		for(i=0;i<3195;i++);
	}

}