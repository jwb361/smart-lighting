#include "test.h"
#include "beep.h"
/******************************************************************************/
/******************************************************************************/
/****************************************************************
功能：
参数：
返回：
说明：
****************************************************************/
void Beep_Init(void)
{
	RCC->APB2ENR|=1<<3;    //使能PORTB时钟
  	GPIOB->CRL&=0XFFFFFFF0; 
	GPIOB->CRL|=0X00000003;//PB0推挽输出 

	GPIOB->ODR|=0x00000001;
}
