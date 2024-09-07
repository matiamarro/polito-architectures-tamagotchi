/*********************************************************************************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:           IRQ_RIT.c
** Last modified Date:  2014-09-25
** Last Version:        V1.00
** Descriptions:        functions to manage T0 and T1 interrupts
** Correlated files:    RIT.h
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
#include "lpc17xx.h"
#include "RIT.h"
#include "../aliens/alien1.h"
#include "../TouchPanel/TouchPanel.h"
#include "../adc/adc.h"

/******************************************************************************
** Function name:		RIT_IRQHandler
**
** Descriptions:		REPETITIVE INTERRUPT TIMER handler
**
** parameters:			None
** Returned value:		None
**
******************************************************************************/

volatile int down=0;
extern char led_value;

void RIT_IRQHandler (void)
{					
	LPC_RIT->RICTRL |= 0x1;	/* clear interrupt flag ------PERCHE' CRASHA SE LO METTO DOPO?*/
	
	ADC_start_conversion();
	
	if(Touch_alien() && stato_alien_vivo()){
		disable_RIT();
		animazione_cuore();
		enable_RIT();	
	}
	
	if(((LPC_GPIO1->FIOPIN & (1<<26)) == 0) && stato_alien_vivo()){	//fraccia giu
	}
	
	if(((LPC_GPIO1->FIOPIN & (1<<27)) == 0) && stato_alien_vivo()){	//fraccia sinistra - satiety
		disable_RIT();
		incrementa_satiety();
		enable_RIT();			
	}
	
	if(((LPC_GPIO1->FIOPIN & (1<<28)) == 0) && stato_alien_vivo()){	//destra - happiness
		disable_RIT();
		incrementa_happiness();
		enable_RIT();		
	}
	
	if((LPC_GPIO1->FIOPIN & (1<<29)) == 0){	//su
	}
	
	if(((LPC_GPIO1->FIOPIN & (1<<25)) == 0)&& (stato_alien_vivo()==0) ){	
		disable_RIT();
		reset_alien();
		enable_RIT();
	}
	
	

  return;
}

/******************************************************************************
**                            End Of File
******************************************************************************/
