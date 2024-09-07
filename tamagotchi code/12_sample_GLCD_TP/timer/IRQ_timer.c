/*********************************************************************************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:           IRQ_timer.c
** Last modified Date:  2014-09-25
** Last Version:        V1.00
** Descriptions:        functions to manage T0 and T1 interrupts
** Correlated files:    timer.h
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
#include <string.h>
#include "lpc17xx.h"
#include "timer.h"
#include "../GLCD/GLCD.h" 
#include "../TouchPanel/TouchPanel.h"
#include "../aliens/alien1.h"



uint16_t SinTable[45] =                                       /* ÕýÏÒ±í                       */
{
    410, 467, 523, 576, 627, 673, 714, 749, 778,
    799, 813, 819, 817, 807, 789, 764, 732, 694, 
    650, 602, 550, 495, 438, 381, 324, 270, 217,
    169, 125, 87 , 55 , 30 , 12 , 2  , 0  , 6  ,   
    20 , 41 , 70 , 105, 146, 193, 243, 297, 353
};

float volume_level[20]={0,0.1,0.2,0.3,0.4,0.5,0.6,0.7,0.8,0.9,1,1.1,1.2,1.3,1.4,1.5,1.6,1.7,1.8,1.9};

static int count_tempo_salute=1;
volatile int level=0;

void TIMER0_IRQHandler (void)
{
	 //if((LPC_TIM0->IR & 1)==0){ //MR0
	 //LPC_TIM0->IR &= ~(1);
	if(stato_alien_vivo()){
		disable_timer(0);
		
	  LPC_TIM0->IR &= 1;			/* clear interrupt flag */
		
	  incrementa_tempo_vita();
		animazione_costante();
		
		if(count_tempo_salute==5){
			count_tempo_salute=1;
			decrementa_happiness();
			decrementa_satiety();
		}
		else count_tempo_salute++;

		enable_timer(0);
	}

	LPC_TIM0->IR = 1;
  return;
}


/******************************************************************************
** Function name:		Timer1_IRQHandler
**
** Descriptions:		Timer/Counter 1 interrupt handler
**
** parameters:			None
** Returned value:		None
**
******************************************************************************/
void TIMER1_IRQHandler (void)
{
	
	
  static int sineticks=0;
	/* DAC management */	
	static int currentValue; 
	currentValue = SinTable[sineticks];
	currentValue -= 410;
	currentValue /= 1;
	currentValue += 410;
	currentValue = currentValue*volume_level[level];
	LPC_DAC->DACR = currentValue <<6;
	sineticks++;
	if(sineticks==45) sineticks=0;

	LPC_TIM1->IR = 1;			/* clear interrupt flag */
  
  return;
}

void TIMER2_IRQHandler (void)
{	
	disable_timer(1);
  LPC_TIM2->IR = 1;			/* clear interrupt flag */
  return;
}

void TIMER3_IRQHandler (void)
{
  LPC_TIM3->IR = 1;			/* clear interrupt flag */
  return;
}
/******************************************************************************
**                            End Of File
******************************************************************************/
