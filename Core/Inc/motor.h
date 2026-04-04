#ifndef MOTOR_H
#define MOTOR_H

#include "main.h"
#include <stdint.h>

/*
 * TODO: Set up a helper function for acceleration profile
 *           - Will probably be similar to the lab dimming
 *           - We have the clk info so just adjust ARR from observation
 *           - Test code and iterate
 * */


/*
 * 	needs to be an extern to share to our ISR*/
/*	Need to refactor this to standarize
 *	but for testing i need to lock in
 **/
extern volatile uint32_t step_count; 	/*count up steps*/
extern volatile uint32_t step_target;	/*target step (50 or 100) for our ISR*/
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
	/*Technically I should consider channels too*/
	/*Should probably add the channel info too*/
	/*
	 * Moved these to a global bc we run one motor at a time
	 * volatile uint32_t step_count;
	 * volative uint32_t step_target;
	 * volatile uint8_t = stepper_done;
	 *
	 * */
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

#endif
