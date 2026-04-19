#ifndef NEO_PIXEL_H
#define NEO_PIXEL_H

#include "main.h"
#include <stdint.h>

#define MAX_LED 144
#define USE_BRIGHTNESS 1

extern TIM_HandleTypeDef htim3; 		/*tim channel we are using?*/
extern volatile uint8_t datasentflag; 	/*flag being sent around*/


typedef enum
{
	LED_1 = 0,
	LED_2 = 1,
	LED_3 = 2,
	LED_4 = 3,
	LED_5 = 4,
	LED_6 = 5,
} LED_num;

/*initialize to off*/
void WS2812_Init(void);
/*send data packets*/
void WS2812_Send(void);
/*set up the color data*/
void Set_LED(int LEDnum, int Red, int Green, int Blue);

/*
 * adjust LED_MOD to store LED related data
 * To control the brightness im following a tutorial
 * They used a tangent function to bring some lineraity in the scaling
 * Brightness values are being vary from 0 to 45
 * */
void Set_Brightness(int brightness);
void Party_LED(void);
void Turn_LED_Off(void);
void All_White(void);
void Set_All_To_Scan_Color();
void Set_Ring(int ring, int r, int g, int b);
void Load_Cube(void);
void Set_All_Next_Color(void);
#endif
