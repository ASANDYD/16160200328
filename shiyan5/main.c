#include "LPC11XX.H"
unsigned int status;
void LedInit(void)
{
	LPC_SYSCON->SYSAHBCLKCTRL |=(1<<16);
	LPC_IOCON->PIO2_0 &=~0x07;
	LPC_IOCON->PIO2_0 |=0x00;
	LPC_IOCON->PIO2_1 &=~0x07;
	LPC_IOCON->PIO2_1 |=0x00;
	LPC_SYSCON->SYSAHBCLKCTRL &=~(1<<16);
	LPC_SYSCON->SYSAHBCLKCTRL |=(1<<6);
	LPC_GPIO2->DIR |=(1<<0);
	LPC_GPIO2->DATA |=(1<<0);
	LPC_GPIO2->DIR |=(1<<1);
	LPC_GPIO2->DATA |=(1<<1);
}
void PIONT1_TRQHandler()
{
	if((LPC_GPIO3->MIS&(1<<0))==(1<<1))
	{
		
		LPC_GPIO2->DATA=0xFF;
	}

}
void SysTickInit(void)
{
	SysTick->CTRL&=~(1<<2);
	SysTick->LOAD=12499999;
	SysTick->VAL=0;
	SysTick->CTRL|=((1<<1)|(1<<0));
	NVIC_EnableIRQ(SysTick_IRQn);
}
void SysTick_Handler(void)
{
	status=LPC_GPIO2->DATA;
	LPC_GPIO2->DATA=~status;
}


int main(void)
{
	LedInit();
	SysTickInit();
	while(1)
	{
		
	}
}


