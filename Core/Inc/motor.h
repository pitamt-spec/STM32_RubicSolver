#ifndef MOTOR_H
#define MOTOR_H

#include "main.h"
#include <stdint.h>

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
    MOTOR_2 = 2
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

	TIM_HandleTypeDef *clk;
	/*Should probably add the channel info too*/
	/*
	 * Moved these to a global bc we run one motor at a time
	 * volatile uint32_t step_count;
	 * volative uint32_t step_target;
	 * volatile uint8_t = stepper_done;
	 *
	 * */
} Motor;



void Motor_Init(TIM_HandleTypeDef *htim_pwm, Motor *mmotor, MotorId id);
void Motor_Select(const Motor *mmotor);
void Motor_SetDirection(const Motor *mmotor);
void Motor_SendSteps_Blocking(Motor *mmotor, uint32_t steps);
void Motor_RunMove(Motor *mmotor, uint32_t steps);

#endif
