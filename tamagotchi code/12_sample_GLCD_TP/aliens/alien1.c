#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "alien1.h"
#include "alien1_image.c"
#include "../GLCD/GLCD.h"
#include "LPC17xx.h"
#include "../timer/timer.h"
#include "../music/music.h"

#define max_happiness 5
#define max_satiety 5

#define RIT_SEMIMINIMA 8
#define RIT_MINIMA 16
#define RIT_INTERA 32

#define UPTICKS 1

NOTE song[] = 
{
	// 1
	{b3, time_croma},
	{d3, time_semicroma},
	{d3, time_semicroma},
	{d4, time_croma},
	{a3, time_croma},
	{pause, time_semicroma},
	{a3b, time_semicroma},
	{pause, time_semicroma},
	{g3, time_croma},
	{f3, time_semicroma*2},
	{d3, time_semicroma},
	{f3, time_semicroma},
	{g3, time_semicroma},
	// 2
	{c3, time_semicroma},
	{c3, time_semicroma},
	{d4, time_croma},
	{a3, time_croma},
	{pause, time_semicroma},
	{a3b, time_semicroma},
	{pause, time_semicroma},
	{g3, time_croma},
	{f3, time_semicroma*2},
	{d3, time_semicroma},
	{f3, time_semicroma},
	{g3, time_semicroma},
	// 3
	{c3b, time_semicroma},
	{c3b, time_semicroma},
	{d4, time_croma},
	{a3, time_croma},
	{pause, time_semicroma},
	{a3b, time_semicroma},
	{pause, time_semicroma},
	{g3, time_croma},
	{f3, time_semicroma*2},
	{d3, time_semicroma},
	{f3, time_semicroma},
	{g3, time_semicroma},
	// 4
	{a2b, time_semicroma},
	{a2b, time_semicroma},
	{d4, time_croma},
	{a3, time_croma},
	{pause, time_semicroma},
	{a3b, time_semicroma},
	{pause, time_semicroma},
	{g3, time_croma},
	{f3, time_semicroma*2},
	{d3, time_semicroma},
	{f3, time_semicroma},
	{g3, time_semicroma},
	// 5
	
};


static int centro_alien_x=80;
static int centro_alien_y=140;

static int centro_food_hotdog_x=20;
static int centro_food_hotdog_y=190;

static int centro_food_gelato_x=190;
static int centro_food_gelato_y=183;
	

static int count_happiness=5; 
static int count_satiety=5;
static int count_tempo_vita=0;

static int stato_animazione_cont=0;

static int stato_alien_life=0;

volatile int begin_level=1;

void reset_alien(){
	
	stato_alien_life=1;
	count_happiness=max_happiness;
	count_satiety=max_satiety;
	count_tempo_vita=0;
	GUI_Text(95, 280, (uint8_t *) "Reset", White, White);
	GUI_Text(centro_alien_x, centro_alien_y, (uint8_t *) "GAME OVER", White, White);
	GUI_Text(25, 40, (uint8_t *) "happiness", Black, White);
	GUI_Text(150, 40, (uint8_t *) "satiety", Black, White);
	draw_selection_food(Black,White,Black,White);
	animazione_happiness();
	animazione_satiety();	
	
	NVIC_EnableIRQ(TIMER0_IRQn);
	enable_timer(0);
}

int stato_alien_vivo(){
	return stato_alien_life;	
}
void draw_selection_food(uint16_t t1, uint16_t s1, uint16_t t2, uint16_t s2){
	GUI_Text(30, 280, (uint8_t *) "meal", t1, s1);
	GUI_Text(170, 280, (uint8_t *) "snack", t2, s2);
}

void decrementa_happiness(){	
	if(stato_alien_life){
	count_happiness--;
	if(count_happiness<=0){
		NVIC_DisableIRQ(TIMER0_IRQn);
		disable_timer(0);
		animazione_happiness();
		stato_alien_life=0;
		animazione_finevita();
	}
	else animazione_happiness();
  }
}
void decrementa_satiety(){
	if(stato_alien_life){
	count_satiety--;
	if(count_satiety<=0){
		NVIC_DisableIRQ(TIMER0_IRQn);
		disable_timer(0);
		animazione_satiety();
		stato_alien_life=0;
		animazione_finevita();
	}
	else animazione_satiety();
  }
}
void incrementa_happiness(){
	draw_selection_food(Black,White,Cyan,Red);
	animazione_snack(centro_food_gelato_x,centro_food_gelato_y);
	if(count_happiness<max_happiness){
		
		count_happiness++;
		animazione_happiness();
		
	}
	
	draw_selection_food(Black,White,Black,White);
}
void incrementa_satiety(){
	draw_selection_food(Cyan,Red,Black,White);
	animazione_meal(centro_food_hotdog_x,centro_food_hotdog_y);
	if(count_satiety<max_satiety){
		
		count_satiety++;
		animazione_satiety();
		
		}
	
		draw_selection_food(Black,White,Black,White);
}
void incrementa_tempo_vita(){
	
	int hours,minutes,secs;
	char buffer[20];
	count_tempo_vita ++;
	hours=count_tempo_vita / 3600;
  minutes = (count_tempo_vita % 3600) / 60;
  secs = count_tempo_vita % 60;
	
  sprintf(buffer, "Age %02d:%02d:%02d", hours, minutes, secs);
	
	GUI_Text(70, 16, (uint8_t *) buffer, Cyan, Red);
	
}

void animazione_happiness(){
	int i,x0=25,y0=60,w=11,h=20,s=3;

	for(i=0;i<count_happiness;i++){
		LCD_DrawRectangle(x0+((s+w)*i),y0,w,h,Black);
	}
	for(;i<max_happiness;i++){
		LCD_DrawRectangle(x0+((s+w)*i),y0,w,h,White);
	}	
}
void animazione_satiety(){
	int i,x0=142,y0=60,w=11,h=20,s=3;
	
	for(i=0;i<count_satiety;i++){
		LCD_DrawRectangle(x0+((s+w)*i),y0,w,h,Black);
	}
	for(;i<max_satiety;i++){
		LCD_DrawRectangle(x0+((s+w)*i),y0,w,h,White);
	}	
}

void animazione_meal(int px, int py){
	int i=0,j=0;
	NOTE vetn[3]={{g4,time_semicroma},{b4,time_semicroma},{g4,time_semicroma}};
	playNote(song[2]);
	for(j=0;j<3;j++){
		LCD_DrawRectangle(0,centro_alien_y,220,110,White);
		draw_alien_a(centro_alien_x-(j*22),centro_alien_y);
		for(i=0;i<dim_matrix_food_hotdog;i++){
			LCD_DrawRectangle(px+(food_hot_dog[i][0]*dim_alien_a_w),py+(food_hot_dog[i][1]*dim_alien_a_h),
			(food_hot_dog[i][2]*dim_alien_a_w),(food_hot_dog[i][3]*dim_alien_a_h),food_hot_dog[i][4]);
		}
	}
	playNotes(vetn,3);
	LCD_DrawRectangle(0,centro_alien_y,220,110,White);
	
	
}
void animazione_snack(int px, int py){
	
	int i=0,w=3,h=3,j=0;
	NOTE vetn[3]={{g4,time_semicroma},{b4,time_semicroma},{g4,time_semicroma}};
	playNote(song[2]);
	for(j=0;j<3;j++){
		LCD_DrawRectangle(0,centro_alien_y,220,110,White);
		draw_alien_a(centro_alien_x+(j*22),centro_alien_y);
		for(i=0;i<dim_matrix_food_gelato;i++){
			LCD_DrawRectangle(px+(food_gelato[i][0]*w),py+(food_gelato[i][1]*h),
			(food_gelato[i][2]*w),(food_gelato[i][3]*h),food_gelato[i][4]);
		}
	}
	playNotes(vetn,3);
	LCD_DrawRectangle(0,centro_alien_y,220,110,White);
	
}
void animazione_finevita(){
	int j=0;
	NOTE vetn[]={{b3,time_semicroma},{a3,time_semicroma},{g3,time_semicroma},
	{f3,time_semicroma},{e3,time_semicroma},{d3,time_semicroma},{c3,time_semicroma}};
	draw_selection_food(White,White,White,White);
	for(j=1;j<3;j++){
		LCD_DrawRectangle(0,centro_alien_y-20,230,150,White);
		draw_alien_a(centro_alien_x-(j*27),centro_alien_y);
		
	}
	LCD_DrawRectangle(0,centro_alien_y,220,110,White);
	GUI_Text(centro_alien_x, centro_alien_y, (uint8_t *) "GAME OVER", Cyan, Red);
	
	playNotes(vetn,7);
	
	GUI_Text(95, 280, (uint8_t *) "Reset", Black, White);
}
void animazione_costante(){
	if(stato_animazione_cont){
		stato_animazione_cont=0;
		
		//immagine 1
		draw_alien_a(centro_alien_x,centro_alien_y);
	}
	else{
		stato_animazione_cont=1;
		
		//immagine 2
		draw_alien_b(centro_alien_x,centro_alien_y);
	}
}
void draw_alien_a(int px, int py){
	int i=0;
	for(i=0;i<dim_matrix_alien_a;i++){
		LCD_DrawRectangle(px+(iron_alien_a[i][0]*dim_alien_a_w),py+(iron_alien_a[i][1]*dim_alien_a_h),
		(iron_alien_a[i][2]*dim_alien_a_w),(iron_alien_a[i][3]*dim_alien_a_h),iron_alien_a[i][4]);
	}
}
void draw_alien_b(int px, int py){
	int i=0;
	for(i=0;i<dim_matrix_alien_b;i++){
		LCD_DrawRectangle(px+(iron_alien_b[i][0]*dim_alien_a_w),py+(iron_alien_b[i][1]*dim_alien_a_h),
		(iron_alien_b[i][2]*dim_alien_a_w),(iron_alien_b[i][3]*dim_alien_a_h),iron_alien_b[i][4]);
	}
}

void animazione_cuore(){
	
	int i,j,count=0;
	int const dim=3;
	int px[dim]={150,10,80};
	int py[dim] = {130,120,110};
	int scale[dim]= {6,9,3};
	NOTE vetn[]={{c4,time_semicroma},{e4,time_semicroma},{d4,time_semicroma},
	{f4,time_semicroma},{g4,time_semicroma},{a4,time_semicroma},{b4,time_semicroma},{c4,time_semicroma}};
	//srand(time(NULL));
	for(j=0;j<dim;j++){
		
		for(i=0;i<dim_matrix_cuore;i++){
			LCD_DrawRectangle(px[j]+(cuore[i][1]*scale[j]),py[j]+(cuore[i][0]*scale[j]),
			(cuore[i][2]*scale[j]),(cuore[i][3]*scale[j]),cuore[i][4]);
			count=0;
			do{
				count++;
			}while(count<300000);//500000
		}
		playNote(vetn[j]);
		count=0;
		do{
			count++;
		}while(count<900000);//10000000);
		
	}
	playNotes(vetn,8);
	if(count_happiness<max_happiness)count_happiness++;
	animazione_happiness();
	//cancella
	LCD_DrawRectangle(0,100,220,130,White);
}

void stampa(int x,int y){
	char buffer[20];
	
  sprintf(buffer, "X: %02d   Y:%02d", x, y);
	GUI_Text(70, 16, (uint8_t *) buffer, Cyan, Red);
}

void draw_speaker_stopped(){
	int i,px=2,py=2;
	int scale=2;
	
	for(i=0;i<dim_matrix_speaker_stopped;i++){
			LCD_DrawRectangle(px+(speaker_stopped[i][0]*scale),py+(speaker_stopped[i][1]*scale),
			(speaker_stopped[i][2]*scale),(speaker_stopped[i][3]*scale),speaker_stopped[i][4]);
		}
}

void draw_speaker_loud(){
	int i,px=2,py=2;
	int scale=2;
	
	for(i=0;i<dim_matrix_speaker_loud;i++){
			LCD_DrawRectangle(px+(speaker_loud[i][0]*scale),py+(speaker_loud[i][1]*scale),
			(speaker_loud[i][2]*scale),(speaker_loud[i][3]*scale),speaker_loud[i][4]);
		}
}


