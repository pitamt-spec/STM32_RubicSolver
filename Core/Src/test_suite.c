#include "test_suite.h"
#include "motor.h"

#define TEST_STEPS_90_DEG   	199
#define TEST_STEPS_180_DEG   	180

static Motor* motor1 = NULL;
static Motor* motor2 = NULL;
static Motor* motor3 = NULL;
static Motor* motor4 = NULL;
static Motor* motor5 = NULL;
static Motor* motor6 = NULL;

static void LED_Helper(uint8_t B, uint8_t R, uint8_t G);
static void LED_On(const Motor *mmotor);
static void Test_Motor(Motor *mmotor, uint32_t steps);


//just make sure all the lights are off
void TestSuite_Init(Motor *mmotor1, Motor *mmotor2, Motor *mmotor3, Motor *mmotor4, Motor *mmotor5, Motor *mmotor6)
{
	if (mmotor1 == NULL || mmotor2 == NULL || mmotor3 == NULL || mmotor4 == NULL || mmotor5 == NULL || mmotor6 == NULL) return;
	motor1 = mmotor1;
	motor2 = mmotor2;
	motor3 = mmotor3;
	motor4 = mmotor4;
	motor5 = mmotor5;
	motor6 = mmotor6;

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
	 * motor3 is green
	 * motor4 is blue & red
	 * motor5 is blue & red & green
	 * motor5 is red & green
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
	case MOTOR_3:
		LED_Helper(0,0,1);
		break;
	case MOTOR_4:
		LED_Helper(1,1,0);
		break;
	case MOTOR_5:
		LED_Helper(1,1,1);
		break;
	case MOTOR_6:
		LED_Helper(0,1,1);
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
	if (motor1 == NULL || motor2 == NULL || motor3 == NULL || motor4 == NULL || motor5 == NULL || motor6 == NULL) return;

	/*Start Motor 1*/
	motor1->DIR = MOTOR_DIR_CW;
	Test_Motor(motor1, TEST_STEPS_90_DEG);
	HAL_Delay(500);

	motor1->DIR = MOTOR_DIR_CCW;
	Test_Motor(motor1, TEST_STEPS_90_DEG);
	HAL_Delay(500);

	/*Start motor 2*/
	motor2->DIR = MOTOR_DIR_CW;
	Test_Motor(motor2, TEST_STEPS_90_DEG);
	HAL_Delay(500);

	motor2->DIR = MOTOR_DIR_CCW;
	Test_Motor(motor2, TEST_STEPS_90_DEG);
	HAL_Delay(500);

	/*Start motor 3*/
	motor3->DIR = MOTOR_DIR_CW;
	Test_Motor(motor3, TEST_STEPS_90_DEG);
	HAL_Delay(500);

	motor3->DIR = MOTOR_DIR_CCW;
	Test_Motor(motor3, TEST_STEPS_90_DEG);
	HAL_Delay(500);

	/*Start motor 4*/
	motor4->DIR = MOTOR_DIR_CW;
	Test_Motor(motor4, TEST_STEPS_90_DEG);
	HAL_Delay(500);

	motor4->DIR = MOTOR_DIR_CCW;
	Test_Motor(motor4, TEST_STEPS_90_DEG);
	HAL_Delay(500);

	/*Start motor 5*/
	motor5->DIR = MOTOR_DIR_CW;
	Test_Motor(motor5, TEST_STEPS_90_DEG);
	HAL_Delay(500);

	motor5->DIR = MOTOR_DIR_CCW;
	Test_Motor(motor5, TEST_STEPS_90_DEG);
	HAL_Delay(500);

	/*Start motor 6*/
	motor6->DIR = MOTOR_DIR_CW;
	Test_Motor(motor6, TEST_STEPS_90_DEG);
	HAL_Delay(500);

	motor6->DIR = MOTOR_DIR_CCW;
	Test_Motor(motor6, TEST_STEPS_90_DEG);
	HAL_Delay(500);



}

/*Can add more TestSuite stuff if you want */
void TestSuite_RunLoop(void)
{
    TestSuite_RunOnce();
}
