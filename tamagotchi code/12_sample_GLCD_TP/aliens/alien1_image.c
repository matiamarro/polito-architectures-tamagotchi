#include "../GLCD/GLCD.h"

static const int dim_matrix_alien_a = 210;//190;
static const int dim_matrix_alien_b = 210;//200;
static const int dim_matrix_food_hotdog = 14;
static const int dim_matrix_cuore=27;
static const int dim_matrix_speaker_stopped=18;
static const int dim_matrix_speaker_loud=18;

static const int dim_matrix_food_gelato = 38;

static const int dim_alien_a_w = 6;
static const int dim_alien_a_h = 6;

static int speaker_loud[dim_matrix_speaker_loud][5]={
	{5,0,1,1,Black},
	{6,0,1,1,Black},
	
	{4,1,1,1,Black},
	{5,1,1,1,Black},
	{6,1,1,1,Black},
	
	{8,1,2,1,Black},//
	
	{3,2,1,1,Black},
	{4,2,1,1,Black},
	{5,2,1,1,Black},
	{6,2,1,1,Black},
	
	{9,2,1,1,Black},//
	
	{0,3,7,3,Black},
	
	{10,3,1,3,Black},//
	
	{3,6,4,1,Black},
	{9,6,1,1,Black},//
	
	
	{4,7,3,1,Black},
	{8,7,2,1,Black},//
	
	{5,8,2,1,Black}	
	
	
	
};

static int speaker_stopped[dim_matrix_speaker_stopped][5]={
	{5,0,1,1,Black},
	{6,0,1,1,Black},
	
	{4,1,1,1,Black},
	{5,1,1,1,Black},
	{6,1,1,1,Black},
	
	{8,1,2,1,White},//
	
	{3,2,1,1,Black},
	{4,2,1,1,Black},
	{5,2,1,1,Black},
	{6,2,1,1,Black},
	
	{9,2,1,1,White},//
	
	{0,3,7,3,Black},
	
	{10,3,1,3,White},//
	
	{3,6,4,1,Black},
	{9,6,1,1,White},//
	
	
	{4,7,3,1,Black},
	{8,7,2,1,White},//
	
	{5,8,2,1,Black}	
	
};

static int food_gelato [dim_matrix_food_gelato][5]={
	{4,0,1,1,Yellow_chiaro},
	{4,1,1,1,Yellow_chiaro},
	{2,2,1,1,Yellow_chiaro},
	{3,2,1,1,Yellow_chiaro},
	{4,2,1,1,Yellow_chiaro},
	{2,3,1,1,Yellow_chiaro},
	{3,3,1,1,Yellow_chiaro},
	{4,3,1,1,Yellow_chiaro},
	{0,4,1,1,Yellow_chiaro},
	{1,4,1,1,Yellow_chiaro},
	{2,4,1,1,Yellow_chiaro},
	{3,4,1,1,Yellow_chiaro},
	{4,4,1,1,Yellow_chiaro},
	{0,5,1,1,Yellow_chiaro},
	{1,5,1,1,Yellow_chiaro},
	{2,5,1,1,Yellow_chiaro},
	{3,5,1,1,Yellow_chiaro},
	{4,5,1,1,Yellow_chiaro},//18
	
	{0,6,1,1,Brown},
	{1,6,1,1,Brown},
	{2,6,1,1,Brown},
	{3,6,1,1,Brown},
	{4,6,1,1,Brown},
		{0,7,1,1,Brown},
	{1,7,1,1,Brown},
	{2,7,1,1,Brown},
	{3,7,1,1,Brown},
	{4,7,1,1,Brown},
		{0,8,1,1,Brown},
	{1,8,1,1,Brown},
	{2,8,1,1,Brown},
	{3,8,1,1,Brown},
	{4,8,1,1,Brown},
		{0,8,1,1,Brown},
	{1,8,1,1,Brown},
	{2,8,1,1,Brown},
	{3,8,1,1,Brown},
	{4,8,1,1,Brown},//38	
};
	
static int food_hot_dog [dim_matrix_food_hotdog][5]={
	{1,0,1,1,Yellow_scuro},
	{2,0,1,1,Yellow_scuro},
	{3,0,1,1,Yellow_scuro},
	{4,0,1,1,Yellow_scuro},
	
	{0,1,1,1,Red_chiaro},
	{1,1,1,1,Red_chiaro},
	{2,1,1,1,Red_chiaro},
	{3,1,1,1,Red_chiaro},
	{4,1,1,1,Red_chiaro},
	{5,1,1,1,Red_chiaro},
	
	{1,2,1,1,Yellow_scuro},
	{2,2,1,1,Yellow_scuro},
	{3,2,1,1,Yellow_scuro},
	{4,2,1,1,Yellow_scuro}
};

static int cuore [dim_matrix_cuore][5]={
	{0,1,1,1,Red_chiaro},
	{0,2,1,1,Red_chiaro},
	{0,4,1,1,Red_chiaro},
	{0,5,1,1,Red_chiaro},
	
	
	{1,0,1,1,Red_chiaro},
	{1,1,1,1,Red_chiaro},
	{1,2,1,1,Red_chiaro},
	{1,3,1,1,Red_chiaro},
	{1,4,1,1,Red_chiaro},
	{1,5,1,1,Red_chiaro},
	{1,6,1,1,Red_chiaro},
	
	{2,0,1,1,Red_chiaro},
	{2,1,1,1,Red_chiaro},
	{2,2,1,1,Red_chiaro},
	{2,3,1,1,Red_chiaro},
	{2,4,1,1,Red_chiaro},
	{2,5,1,1,Red_chiaro},
	{2,6,1,1,Red_chiaro},
	
	{3,1,1,1,Red_chiaro},
	{3,2,1,1,Red_chiaro},
	{3,3,1,1,Red_chiaro},
	{3,4,1,1,Red_chiaro},
	{3,5,1,1,Red_chiaro},
	
	{4,2,1,1,Red_chiaro},
	{4,3,1,1,Red_chiaro},
	{4,4,1,1,Red_chiaro},
	
	{5,3,1,1,Red_chiaro}
};


static int iron_alien_a [dim_matrix_alien_a][5] = {
	{2,0,1,1,Black},
	{3,0,1,1,Black},
	{4,0,1,1,Black},
	{5,0,1,1,Black},
	{6,0,1,1,Black},
	{7,0,1,1,Black},
	{8,0,1,1,Black},
	{9,0,1,1,Black}, //8p
	{1,1,1,1,Black},
	{2,1,1,1,Red_scuro},
	{3,1,1,1,Red_scuro},
	{4,1,1,1,Red_scuro},
	{5,1,1,1,Red_chiaro},
	{6,1,1,1,Red_chiaro},
	{7,1,1,1,Red_chiaro},
	{8,1,1,1,Red_chiaro},
	{9,1,1,1,Red_chiaro},
	{10,1,1,1,Black},//18p
	{0,2,1,1,Black},
	{1,2,1,1,Red_scuro},
	{2,2,1,1,Yellow_scuro},
	{3,2,1,1,Yellow_scuro},
	{4,2,1,1,Red_chiaro},
	{5,2,1,1,Red_chiaro},
	{6,2,1,1,Red_chiaro},	
	{7,2,1,1,Yellow_chiaro},
	{8,2,1,1,Yellow_chiaro},
	{9,2,1,1,Red_chiaro},
	{10,2,1,1,Red_chiaro},
	{11,2,1,1,Black},//30p
	
	{0,3,1,1,Black},
	{1,3,1,1,Yellow_scuro},
	{2,3,1,1,Yellow_chiaro},
	{3,3,1,1,Yellow_chiaro},
	{4,3,1,1,Red_chiaro},
	{5,3,1,1,Red_chiaro},
	{6,3,1,1,Red_chiaro},	
	{7,3,1,1,Yellow_chiaro},
	{8,3,1,1,Yellow_chiaro},
	{9,3,1,1,Yellow_chiaro},
	{10,3,1,1,Red_chiaro},
	{11,3,1,1,Black},//42p
	
	{0,4,1,1,Black},
	{1,4,1,1,Yellow_scuro},
	{2,4,1,1,Black},
	{3,4,1,1,Black},
	{4,4,1,1,Yellow_chiaro},
	{5,4,1,1,Yellow_chiaro},
	{6,4,1,1,Yellow_chiaro},	
	{7,4,1,1,Black},
	{8,4,1,1,Black},
	{9,4,1,1,Yellow_chiaro},
	{10,4,1,1,Red_chiaro},
	{11,4,1,1,Black},//54p
	
	{0,5,1,1,Black},
	{1,5,1,1,Yellow_scuro},
	{2,5,1,1,Yellow_scuro},
	{3,5,1,1,Yellow_chiaro},
	{4,5,1,1,Yellow_chiaro},
	{5,5,1,1,Yellow_chiaro},
	{6,5,1,1,Yellow_chiaro},	
	{7,5,1,1,Yellow_chiaro},
	{8,5,1,1,Yellow_chiaro},
	{9,5,1,1,Yellow_chiaro},
	{10,5,1,1,Red_chiaro},
	{11,5,1,1,Black},//66p
	
	{0,6,1,1,Black},
	{1,6,1,1,Red_scuro},
	{2,6,1,1,Yellow_scuro},
	{3,6,1,1,Yellow_chiaro},
	{4,6,1,1,Yellow_chiaro},
	{5,6,1,1,Yellow_chiaro},
	{6,6,1,1,Yellow_chiaro},	
	{7,6,1,1,Yellow_chiaro},
	{8,6,1,1,Yellow_chiaro},
	{9,6,1,1,Red_chiaro},
	{10,6,1,1,Red_chiaro},
	{11,6,1,1,Black},//78p
	
	{0,7,1,1,Black},
	{1,7,1,1,Red_scuro},
	{2,7,1,1,Yellow_scuro},
	{3,7,1,1,Yellow_chiaro},
	{4,7,1,1,Yellow_chiaro},
	{5,7,1,1,Yellow_chiaro},
	{6,7,1,1,Yellow_chiaro},	
	{7,7,1,1,Yellow_chiaro},
	{8,7,1,1,Yellow_chiaro},
	{9,7,1,1,Red_chiaro},
	{10,7,1,1,Red_chiaro},
	{11,7,1,1,Black},//90p

	{0,8,1,1,Black},
	{1,8,1,1,Black},
	{2,8,1,1,Red_scuro},
	{3,8,1,1,Yellow_scuro},
	{4,8,1,1,Yellow_scuro},
	{5,8,1,1,Yellow_scuro},
	{6,8,1,1,Yellow_scuro},	
	{7,8,1,1,Yellow_scuro},
	{8,8,1,1,Red_chiaro},
	{9,8,1,1,Red_chiaro},
	{10,8,1,1,Black},
	{11,8,1,1,Black},//102p
	
	{2,9,1,1,Black},
	{3,9,1,1,Black},
	{4,9,1,1,Black},
	{5,9,1,1,Black},
	{6,9,1,1,Black},
	{7,9,1,1,Black},
	{8,9,1,1,Black},
	{9,9,1,1,Black},//110
	
	{1,10,1,1,Black},
	{2,10,1,1,Red_scuro},
	{3,10,1,1,Red_scuro},
	{4,10,1,1,Red_scuro},
	{5,10,1,1,Red_scuro},
	{6,10,1,1,Red_scuro},
	{7,10,1,1,Red_scuro},
	{8,10,1,1,Red_scuro},
	{9,10,1,1,Red_scuro},
	{10,10,1,1,Black},//120
	
	{0,11,1,1,Black},
	{1,11,1,1,Yellow_chiaro},
	{2,11,1,1,Black},
	{3,11,1,1,Red_chiaro},
	{4,11,1,1,Red_chiaro},
	{5,11,1,1,Cyan},
	{6,11,1,1,Red_chiaro},	
	{7,11,1,1,Red_chiaro},
	{8,11,1,1,Red_chiaro},
	{9,11,1,1,Black},
	{10,11,1,1,Yellow_chiaro},
	{11,11,1,1,Black},//132
	
	{0,12,1,1,Black},
	{1,12,1,1,Yellow_chiaro},
	{2,12,1,1,Black},
	{3,12,1,1,Red_chiaro},
	{4,12,1,1,Red_chiaro},
	{5,12,1,1,Red_chiaro},
	{6,12,1,1,Red_chiaro},	
	{7,12,1,1,Red_chiaro},
	{8,12,1,1,Red_chiaro},
	{9,12,1,1,Black},
	{10,12,1,1,Yellow_chiaro},
	{11,12,1,1,Black},//144
	
	{0,12,1,1,Black},
	{1,12,1,1,Red_chiaro},
	{2,12,1,1,Black},
	{3,12,1,1,Red_chiaro},
	{4,12,1,1,Red_chiaro},
	{5,12,1,1,Red_chiaro},
	{6,12,1,1,Red_chiaro},	
	{7,12,1,1,Red_chiaro},
	{8,12,1,1,Red_chiaro},
	{9,12,1,1,Black},
	{10,12,1,1,Red_chiaro},
	{11,12,1,1,Black},//156
	
	{1,13,1,1,Black},
	{2,13,1,1,Black},
	{3,13,1,1,Black},
	{4,13,1,1,Black},
	{5,13,1,1,Black},
	{6,13,1,1,Black},	
	{7,13,1,1,Black},
	{8,13,1,1,Black},
	{9,13,1,1,Black},
	{10,13,1,1,Black},//166
	
	{2,14,1,1,Black},
	{3,14,1,1,Red_chiaro},
	{4,14,1,1,Yellow_chiaro},
	{5,14,1,1,Red_chiaro},
	{6,14,1,1,Red_chiaro},	
	{7,14,1,1,Yellow_chiaro},
	{8,14,1,1,Red_chiaro},
	{9,14,1,1,Black},//174
	
	{2,15,1,1,Black},
	{3,15,1,1,Red_chiaro},
	{4,15,1,1,Red_chiaro},
	{5,15,1,1,Black},
	{6,15,1,1,Black},	
	{7,15,1,1,Red_chiaro},
	{8,15,1,1,Red_chiaro},
	{9,15,1,1,Black},//182
	
	{2,16,1,1,Black},
	{3,16,1,1,Black},
	{4,16,1,1,Black},
	{5,16,1,1,White},
	{6,16,1,1,White},	
	{7,16,1,1,Black},
	{8,16,1,1,Black},
	{9,16,1,1,Black},//190
	
	
	
	//quelli da cancellare
	{1,9,1,1,White},//
	{0,9,1,1,White},//
	{-1,9,1,1,White},//
	{-2,9,1,1,White},//
	
	{10,9,1,1,White},//
	{11,9,1,1,White},//
	{12,9,1,1,White},//
	{13,9,1,1,White},//
	
	{0,10,1,1,White},//
	{-1,10,1,1,White},//
	{-2,10,1,1,White},//
	{-3,10,1,1,White},//
	
	{11,10,1,1,White},//
	{12,10,1,1,White},//
	{13,10,1,1,White},//
	{14,10,1,1,White},//
	
	{-2,11,1,1,White},//
	{-1,11,1,1,White},//
	
	{12,11,1,1,White},//
	{13,11,1,1,White},//
};


static int iron_alien_b [dim_matrix_alien_b][5] = {
	{2,0,1,1,Black},
	{3,0,1,1,Black},
	{4,0,1,1,Black},
	{5,0,1,1,Black},
	{6,0,1,1,Black},
	{7,0,1,1,Black},
	{8,0,1,1,Black},
	{9,0,1,1,Black}, //8p
	{1,1,1,1,Black},
	{2,1,1,1,Red_scuro},
	{3,1,1,1,Red_scuro},
	{4,1,1,1,Red_scuro},
	{5,1,1,1,Red_chiaro},
	{6,1,1,1,Red_chiaro},
	{7,1,1,1,Red_chiaro},
	{8,1,1,1,Red_chiaro},
	{9,1,1,1,Red_chiaro},
	{10,1,1,1,Black},//18p
	{0,2,1,1,Black},
	{1,2,1,1,Red_scuro},
	{2,2,1,1,Yellow_scuro},
	{3,2,1,1,Yellow_scuro},
	{4,2,1,1,Red_chiaro},
	{5,2,1,1,Red_chiaro},
	{6,2,1,1,Red_chiaro},	
	{7,2,1,1,Yellow_chiaro},
	{8,2,1,1,Yellow_chiaro},
	{9,2,1,1,Red_chiaro},
	{10,2,1,1,Red_chiaro},
	{11,2,1,1,Black},//30p
	
	{0,3,1,1,Black},
	{1,3,1,1,Yellow_scuro},
	{2,3,1,1,Yellow_chiaro},
	{3,3,1,1,Yellow_chiaro},
	{4,3,1,1,Red_chiaro},
	{5,3,1,1,Red_chiaro},
	{6,3,1,1,Red_chiaro},	
	{7,3,1,1,Yellow_chiaro},
	{8,3,1,1,Yellow_chiaro},
	{9,3,1,1,Yellow_chiaro},
	{10,3,1,1,Red_chiaro},
	{11,3,1,1,Black},//42p
	
	{0,4,1,1,Black},
	{1,4,1,1,Yellow_scuro},
	{2,4,1,1,Black},
	{3,4,1,1,Black},
	{4,4,1,1,Yellow_chiaro},
	{5,4,1,1,Yellow_chiaro},
	{6,4,1,1,Yellow_chiaro},	
	{7,4,1,1,Black},
	{8,4,1,1,Black},
	{9,4,1,1,Yellow_chiaro},
	{10,4,1,1,Red_chiaro},
	{11,4,1,1,Black},//54p
	
	{0,5,1,1,Black},
	{1,5,1,1,Yellow_scuro},
	{2,5,1,1,Yellow_scuro},
	{3,5,1,1,Yellow_chiaro},
	{4,5,1,1,Yellow_chiaro},
	{5,5,1,1,Yellow_chiaro},
	{6,5,1,1,Yellow_chiaro},	
	{7,5,1,1,Yellow_chiaro},
	{8,5,1,1,Yellow_chiaro},
	{9,5,1,1,Yellow_chiaro},
	{10,5,1,1,Red_chiaro},
	{11,5,1,1,Black},//66p
	
	{0,6,1,1,Black},
	{1,6,1,1,Red_scuro},
	{2,6,1,1,Yellow_scuro},
	{3,6,1,1,Yellow_chiaro},
	{4,6,1,1,Yellow_chiaro},
	{5,6,1,1,Yellow_chiaro},
	{6,6,1,1,Yellow_chiaro},	
	{7,6,1,1,Yellow_chiaro},
	{8,6,1,1,Yellow_chiaro},
	{9,6,1,1,Red_chiaro},
	{10,6,1,1,Red_chiaro},
	{11,6,1,1,Black},//78p
	
	{0,7,1,1,Black},
	{1,7,1,1,Red_scuro},
	{2,7,1,1,Yellow_scuro},
	{3,7,1,1,Yellow_chiaro},
	{4,7,1,1,Yellow_chiaro},
	{5,7,1,1,Yellow_chiaro},
	{6,7,1,1,Yellow_chiaro},	
	{7,7,1,1,Yellow_chiaro},
	{8,7,1,1,Yellow_chiaro},
	{9,7,1,1,Red_chiaro},
	{10,7,1,1,Red_chiaro},
	{11,7,1,1,Black},//90p

	{0,8,1,1,Black},
	{1,8,1,1,Black},
	{2,8,1,1,Red_scuro},
	{3,8,1,1,Yellow_scuro},
	{4,8,1,1,Yellow_scuro},
	{5,8,1,1,Yellow_scuro},
	{6,8,1,1,Yellow_scuro},	
	{7,8,1,1,Yellow_scuro},
	{8,8,1,1,Red_chiaro},
	{9,8,1,1,Red_chiaro},
	{10,8,1,1,Black},
	{11,8,1,1,Black},//102p
	
	{1,9,1,1,Black},//
	{0,9,1,1,Black},//
	{-1,9,1,1,Black},//
	{-2,9,1,1,Black},//
	
	{2,9,1,1,Black},
	{3,9,1,1,Black},
	{4,9,1,1,Black},
	{5,9,1,1,Black},
	{6,9,1,1,Black},
	{7,9,1,1,Black},
	{8,9,1,1,Black},
	{9,9,1,1,Black},//110
	
	{10,9,1,1,Black},//
	{11,9,1,1,Black},//
	{12,9,1,1,Black},//
	{13,9,1,1,Black},//
	
	{0,10,1,1,Yellow_chiaro},//
	{-1,10,1,1,Yellow_chiaro},//
	{-2,10,1,1,Red_chiaro},//
	{-3,10,1,1,Black},//
	
	{1,10,1,1,Black},
	{2,10,1,1,Red_chiaro},
	{3,10,1,1,Red_chiaro},
	{4,10,1,1,Red_chiaro},
	{5,10,1,1,Red_chiaro},
	{6,10,1,1,Red_chiaro},
	{7,10,1,1,Red_chiaro},
	{8,10,1,1,Red_chiaro},
	{9,10,1,1,Red_chiaro},
	{10,10,1,1,Black},//120
	
	{11,10,1,1,Yellow_chiaro},//
	{12,10,1,1,Yellow_chiaro},//
	{13,10,1,1,Red_chiaro},//
	{14,10,1,1,Black},//
	
	{-2,11,1,1,Black},//
	{-1,11,1,1,Black},//
	
	{0,11,1,1,Black},
	{1,11,1,1,Black},
	{2,11,1,1,Black},
	{3,11,1,1,Red_chiaro},
	{4,11,1,1,Red_chiaro},
	{5,11,1,1,Cyan},
	{6,11,1,1,Red_chiaro},	
	{7,11,1,1,Red_chiaro},
	{8,11,1,1,Red_chiaro},
	{9,11,1,1,Black},
	{10,11,1,1,Black},
	{11,11,1,1,Black},//132
	
	{12,11,1,1,Black},//
	{13,11,1,1,Black},//
	
	{0,12,1,1,White},//cancellato
	{1,12,1,1,White},//cancellato
	{2,12,1,1,Black},
	{3,12,1,1,Red_chiaro},
	{4,12,1,1,Red_chiaro},
	{5,12,1,1,Red_chiaro},
	{6,12,1,1,Red_chiaro},	
	{7,12,1,1,Red_chiaro},
	{8,12,1,1,Red_chiaro},
	{9,12,1,1,Black},
	
	{10,12,1,1,White},//cancellato
	{11,12,1,1,White},//144  //cancellato
	
	{0,12,1,1,White},//cancellato
	{1,12,1,1,White},//cancellato
	{2,12,1,1,Black},
	{3,12,1,1,Red_chiaro},
	{4,12,1,1,Red_chiaro},
	{5,12,1,1,Red_chiaro},
	{6,12,1,1,Red_chiaro},	
	{7,12,1,1,Red_chiaro},
	{8,12,1,1,Red_chiaro},
	{9,12,1,1,Black},
	{10,12,1,1,White},//cancellato
	{11,12,1,1,White},//156//cancellato
	
	{1,13,1,1,White},//cancellato
	{2,13,1,1,Black},
	{3,13,1,1,Black},
	{4,13,1,1,Black},
	{5,13,1,1,Black},
	{6,13,1,1,Black},	
	{7,13,1,1,Black},
	{8,13,1,1,Black},
	{9,13,1,1,Black},
	{10,13,1,1,White},//166//cancellato
	
	{2,14,1,1,Black},
	{3,14,1,1,Red_chiaro},
	{4,14,1,1,Yellow_chiaro},
	{5,14,1,1,Red_chiaro},
	{6,14,1,1,Red_chiaro},	
	{7,14,1,1,Yellow_chiaro},
	{8,14,1,1,Red_chiaro},
	{9,14,1,1,Black},//174
	
	{2,15,1,1,Black},
	{3,15,1,1,Red_chiaro},
	{4,15,1,1,Red_chiaro},
	{5,15,1,1,Black},
	{6,15,1,1,Black},	
	{7,15,1,1,Red_chiaro},
	{8,15,1,1,Red_chiaro},
	{9,15,1,1,Black},//182
	
	{2,16,1,1,Black},
	{3,16,1,1,Black},
	{4,16,1,1,Black},
	{5,16,1,1,White},
	{6,16,1,1,White},	
	{7,16,1,1,Black},
	{8,16,1,1,Black},
	{9,16,1,1,Black},//190
	
};

