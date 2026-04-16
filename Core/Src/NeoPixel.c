#include "NeoPixel.h"
#include <math.h>

#define PI 3.14159265


/*Data*/
uint8_t LED_Data[MAX_LED][4];
uint8_t LED_Mod[MAX_LED][4];
int offset = 0;

/* 24 bits per LED + reset pulse buffer*/
uint16_t pwmData[(24 * MAX_LED) + 50];

volatile uint8_t datasentflag = 0;
extern TIM_HandleTypeDef htim3;

#define NEO_0 22
#define NEO_1 44

//FPF
//#define NEO_0 26
//#define NEO_1 53

/*Set everything up to zero*/
void WS2812_Init(void)
{
    for (int i = 0; i < MAX_LED; i++)
    {
        Set_LED(i, 0, 0, 0);
    }
    WS2812_Send();
}

void Turn_LED_Off(void)
{
    for (int i = 0; i < MAX_LED; i++)
    {
        Set_LED(i, 0, 0, 0);
    }
    Set_Brightness(20);
    WS2812_Send();
}

void Set_Ring(int ring, int r, int g, int b)
{
	for(int i = 0; i < 24; ++i)
	{
		Set_LED(24 * ring + i, r,g,b);
	}

}

void Load_Cube(void)
{
	Set_Ring(0,255,50,0); // O
	Set_Ring(1,0,255,0); // G
	Set_Ring(2,255,0,0); // R
	Set_Ring(3, 255,255,255); // W
	Set_Ring(4,0,0,255);
	Set_Ring(5,255,130, 0); // B - > Yellow
	Set_Brightness(20);
	WS2812_Send();
}
/*
 * 0 < LEDnum <= MAX_LED
 * */
void Set_LED (int LEDnum, int Red, int Green, int Blue)
{
	if (LEDnum < 0 || LEDnum >= MAX_LED) return;
    LED_Data[LEDnum][0] = LEDnum;
    LED_Data[LEDnum][1] = Green;
    LED_Data[LEDnum][2] = Red;
    LED_Data[LEDnum][3] = Blue;
}

void All_White(void)
{
	for(int i = 0; i < 6; ++i)
	{
		Set_Ring(i,255,255,255);
	}
	Set_Brightness(20);
	WS2812_Send();
}

void Party_LED(void)
{
	/*Party colors*/
	uint8_t partyColors[24][3] = {
	    {255,   0,   0},   // red
	    {255,  64,   0},
	    {255, 128,   0},
	    {255, 191,   0},
	    {255, 255,   0},   // yellow
	    {191, 255,   0},
	    {128, 255,   0},
	    { 64, 255,   0},
	    {  0, 255,   0},   // green
	    {  0, 255,  64},
	    {  0, 255, 128},
	    {  0, 255, 191},
	    {  0, 255, 255},   // cyan
	    {  0, 191, 255},
	    {  0, 128, 255},
	    {  0,  64, 255},
	    {  0,   0, 255},   // blue
	    { 64,   0, 255},
	    {128,   0, 255},
	    {191,   0, 255},
	    {255,   0, 255},   // magenta
	    {255,   0, 191},
	    {255,   0, 128},
	    {255,   0,  64}
	};

    for(int fran = 0; fran < 6; ++fran)
    {
        for (int i = 0; i < 24; ++i)
        {
            int shifted = (i + offset) % 24;

            Set_LED(fran * 24 + i,
                    partyColors[shifted][0],
                    partyColors[shifted][1],
                    partyColors[shifted][2]);
        }
    }

    Set_Brightness(20);
    WS2812_Send();
    offset = (offset + 1) % 24;
}

/*
 * Set up brightness
 *
 **/

void Set_Brightness (int brightness)
{
#if USE_BRIGHTNESS

    if (brightness > 44) brightness = 44;
    if (brightness < 1) brightness = 1;

    for (int i = 0; i < MAX_LED; i++)
    {
        LED_Mod[i][0] = LED_Data[i][0];

        for (int j = 1; j < 4; j++)
        {
//        	float angle = (90 - brightness) * PI / 180;
//          LED_Mod[i][j] = (LED_Data[i][j]) / tan(angle);
        	float angle = (90.0f - brightness) * PI / 180.0f;
        	LED_Mod[i][j] = (uint8_t)((float)LED_Data[i][j] / tanf(angle));

        }
    }

#endif
}

/*
 * SEND DATA
 * Added green, red, and blue for debugging help
 * we have a 4 MHz clock so to step down to 800 kHz we need to
 * PSC = 0, ARR = 4 (rem STM does +1)
 * */
void WS2812_Send(void)
{
    uint32_t indx = 0;

    for (int i = 0; i < MAX_LED; i++)
    {

#if USE_BRIGHTNESS
        uint8_t green = LED_Mod[i][1];
        uint8_t red   = LED_Mod[i][2];
        uint8_t blue  = LED_Mod[i][3];
#else
        uint8_t green = LED_Data[i][1];
        uint8_t red   = LED_Data[i][2];
        uint8_t blue  = LED_Data[i][3];
#endif

        uint32_t color = (green << 16) | (red << 8) | blue; /*build color from green red blue*/

        for (int bit = 23; bit >= 0; bit--)
        {
            if (color & (1 << bit))
            {
                pwmData[indx] = NEO_1;   /* HIGH longer → 1 */
            }
            else
            {
                pwmData[indx] = NEO_0;   /* HIGH shorter → 0 */
            }
            indx++;
        }
    }

    /*
     * reset pulse (LOW for >50us)
     * Calibration might be needed
     * */
    for (int i = 0; i < 50; i++)
    {
        pwmData[indx++] = 0;
    }

    // start DMA
    HAL_TIM_PWM_Start_DMA(&htim3, TIM_CHANNEL_3, (uint32_t *)pwmData, indx);
    while(!datasentflag){};
    datasentflag = 0;
}

/*Call Back*/
/*For milestone one we use PC8*/
void HAL_TIM_PWM_PulseFinishedCallback(TIM_HandleTypeDef *htim)
{
    if (htim->Instance == TIM3)
    {
        HAL_TIM_PWM_Stop_DMA(&htim3, TIM_CHANNEL_3);
        datasentflag = 1;
    }
}
