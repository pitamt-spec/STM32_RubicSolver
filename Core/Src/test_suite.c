#include "test_suite.h"
#include "motor.h"

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

	LED_Helper(0,0,0);
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

void TestSuite_RunOnce(void)
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

/*Can add more TestSuite stuff if you want */
void TestSuite_RunLoop(void)
{
    TestSuite_RunOnce();
}
