/****************************************Copyright (c)****************************************************
**                                      
**                                 http://www.powermcu.com
**
**--------------File Info---------------------------------------------------------------------------------
** File name:               main.c
** Descriptions:            The GLCD application function
**
**--------------------------------------------------------------------------------------------------------
** Created by:              AVRman
** Created date:            2010-11-7
** Version:                 v1.0
** Descriptions:            The original version
**
**--------------------------------------------------------------------------------------------------------
** Modified by:             Paolo Bernardi
** Modified date:           03/01/2020
** Version:                 v2.0
** Descriptions:            basic program for LCD and Touch Panel teaching
**
*********************************************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "LPC17xx.h"
#include "GLCD/GLCD.h" 
#include "timer/timer.h"
#include "joystick/joystick.h"
#include "RIT/RIT.h"
#include "aliens/alien1.h"
#include "TouchPanel/TouchPanel.h"
#include "adc/adc.h"

#define SIMULATOR 1

#ifdef SIMULATOR
extern uint8_t ScaleFlag; // <- ScaleFlag needs to visible in order for the emulator to find the symbol (can be placed also inside system_LPC17xx.h but since it is RO, it needs more work)
#endif

static int tempo_animazione=25000000;

int main(void)
{
  SystemInit();  												/* System Initialization (i.e., PLL)  */
	
	joystick_init();											/* Joystick Initialization            */
	
	LCD_Initialization();
	
	TP_Init();
	TouchPanel_Calibrate();
	
	LPC_SC->PCONP |= 1<<22; //TIMER2
	LPC_SC->PCONP |= 1<<23; //TIMER3
	
	init_RIT(0x3312D0);									/* RIT Initialization 50 msec       */
	enable_RIT();	
  NVIC_SetPriority(RIT_IRQn,1);	
	
	
	init_timer(0,tempo_animazione);
	
	//init_timer(1,50000000);
	
	NVIC_SetPriority(TIMER0_IRQn,2);
	
	ADC_init();
	LPC_PINCON->PINSEL1 |= (1<<21);
	LPC_PINCON->PINSEL1 &= ~(1<<20);
	LPC_GPIO0->FIODIR |= (1<<26);

	reset_alien();				
	
  while (1)	
  {
		//__ASM("wfi");
  }
}

/*********************************************************************************************************
      END FILE
*********************************************************************************************************/
