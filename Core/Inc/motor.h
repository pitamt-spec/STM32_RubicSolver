#ifndef MOTOR_H
#define MOTOR_H

#include "main.h"
#include <stdint.h>



extern volatile uint32_t step_count; 	/*count up steps*/
extern volatile uint32_t step_target;	/*target step for our ISR*/
extern volatile uint8_t stepper_done;	/*might be a useful flag for our program*/

typedef enum
{
    MOTOR_1 = 1,
    MOTOR_2 = 2,
	MOTOR_3 = 3,
	MOTOR_4 = 4,
	MOTOR_5 = 5,
	MOTOR_6 = 6
} MotorId;

typedef enum
{
    MOTOR_DIR_CW = 0,
    MOTOR_DIR_CCW = 1
} MotorDirection;

/*
 * One handle per physical motor.
 * Just traits that describes our motors
 * */
typedef struct
{
	MotorId ID; /* what motor is it from 0-5 */
	MotorDirection DIR; /* what direction motor goes*/

	TIM_HandleTypeDef *clk; /*Motor clk*/

} Motor;


/*Initilize a motor object*/
void Motor_Init(TIM_HandleTypeDef *htim_pwm, Motor *mmotor, MotorId id);
/*manage enable pins*/
void Motor_Select(const Motor *mmotor);
/*alterante directions as needed*/
void Motor_SetDirection(const Motor *mmotor);
/*meat of the code. Starts the pulse trains*/
void Motor_SendSteps_Blocking(Motor *mmotor, uint32_t steps);
/*the main function for motor to configure the cube to move*/
void Motor_RunMove(Motor *mmotor, uint32_t steps);
/*Select what LED to turn on*/
void Motor_LED_On(const Motor *mmotr);
#endif
