#ifndef NEO_PIXEL_H
#define NEO_PIXEL_H

#include "main.h"
#include <stdint.h>

#define MAX_LED 24
#define USE_BRIGHTNESS 1

extern TIM_HandleTypeDef htim3; 		/*tim channel we are using?*/
extern volatile uint8_t datasentflag; 	/*flag being sent around*/

/*initalize to off*/
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


#endif
