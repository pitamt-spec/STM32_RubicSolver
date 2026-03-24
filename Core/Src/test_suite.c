#include "test_suite.h"
#include "motor.h"
#include "Neo_Pixel.h"

#define TEST_STEPS_90_DEG   	50
#define TEST_STEPS_180_DEG   	180

static Motor* motor1 = NULL;
static Motor* motor2 = NULL;
static void LED_Helper(uint8_t B, uint8_t R, uint8_t G);
static void LED_On(const Motor *mmotor);
static void Test_Motor(Motor *mmotor, uint32_t steps);


//just make sure all the lights are off
void TestSuite_Init(Motor *mmotor1, Motor *mmotor2)
{
	if (mmotor1 == NULL || mmotor2 == NULL) return;
	motor1 = mmotor1;
	motor2 = mmotor2;

	LED_Helper(0,0,0); /* Don't mix up LED and the WS2812 please*/
	WS2812_Init(); /* Clear the ring*/
}

static void LED_Helper(uint8_t B, uint8_t R, uint8_t G)
{
	HAL_GPIO_WritePin(LED_BLUE_GPIO_Port, 	LED_BLUE_Pin, B ? GPIO_PIN_SET : GPIO_PIN_RESET);
	HAL_GPIO_WritePin(LED_RED_GPIO_Port, 	LED_RED_Pin, R ? GPIO_PIN_SET : GPIO_PIN_RESET);
	HAL_GPIO_WritePin(LED_GREEN_GPIO_Port,	LED_GREEN_Pin, G ? GPIO_PIN_SET : GPIO_PIN_RESET);
}
static void LED_On(const Motor *mmotor){
	/*
	 * Adjust debug lights as needed
	 * motor1 is blue
	 * motor2 is red
	 * */
	if (mmotor == NULL) return;

	switch (mmotor->ID)
	{
	case MOTOR_1:
		LED_Helper(1,0,0);
		break;
	case MOTOR_2:
		LED_Helper(0,1,0);
		break;
	default:
		/*should not end up here*/
		break;
	}

}


// below is code to IN THEORY make a blue light flicker
//static void LED_Blue_Blink(uint32_t delay_ms, uint32_t count)
//{
//    for (uint32_t i = 0; i < count; i++)
//    {
//        LED_Blue_On();
//        HAL_Delay(delay_ms);
//        LED_Blue_Off();
//        HAL_Delay(delay_ms);
//    }
//}



static void Test_Motor(Motor* mmotor, uint32_t steps)
{
	if (mmotor == NULL) return;
	LED_On(mmotor);
	Motor_RunMove(mmotor, steps);
	LED_Helper(0,0,0);
}

void Test_Motor_RunOnce(void)
{
	if (motor1 == NULL || motor2 == NULL) return;
	motor1->DIR = MOTOR_DIR_CW;
	Test_Motor(motor1, TEST_STEPS_90_DEG);
	HAL_Delay(1000);

	motor1->DIR = MOTOR_DIR_CCW;
	Test_Motor(motor1, TEST_STEPS_90_DEG);
	HAL_Delay(1000);

	motor2->DIR = MOTOR_DIR_CW;
	Test_Motor(motor2, TEST_STEPS_90_DEG);
	HAL_Delay(1000);

	motor2->DIR = MOTOR_DIR_CCW;
	Test_Motor(motor2, TEST_STEPS_90_DEG);
	HAL_Delay(1000);
}

/*
 *Setting diff colors to the LEDs
 *Increase the birghtness every 50 ms
 *and decreasing brightness
 * */
void Test_WS2812_RunOnce(void)
{
	Set_LED(0, 255, 0, 0);
	Set_LED(1, 0, 255, 0);
	Set_LED(2, 0, 0, 255);

	Set_LED(3, 46, 89, 128);

	Set_LED(4, 156, 233, 100);
	Set_LED(5, 102, 0, 235);
	Set_LED(6, 47, 38, 77);

	Set_LED(7, 255, 200, 0);

	for (int i=0; i<46;i++)
	{
		Set_Brightness(i);
		WS2812_Send();
		HAL_Delay(50);
	}

	for (int i=45;i>=0; i--)
	{
		Set_Brightness(i);
		WS2812_Send();
		HAL_Delay(50);
	}

}

/*Can add more TestSuite stuff if you want */
void TestSuite_RunLoop(void)
{
	//Test_Motor_RunOnce();
	Test_WS2812_RunOnce();
}
