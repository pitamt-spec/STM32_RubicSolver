#include "motor.h"

/*---------pins---------------------------- */
//static TIM_HandleTypeDef *motor_tim = NULL; // technically this will always be 4

volatile uint32_t step_count = 0;
volatile uint32_t step_target = 0;
volatile uint8_t stepper_done = 0;

void Motor_Init(TIM_HandleTypeDef *htim_pwm, Motor *mmotor, MotorId id)
{
	if (mmotor == NULL) return;
    mmotor->clk = htim_pwm; /*By design we know the channel and timer it is*/

    mmotor->ID = id;

    mmotor->DIR = MOTOR_DIR_CW; /*value for the sake of having a value*/
}

static void Mux_Select(uint8_t s2, uint8_t s1, uint8_t s0)
{
    HAL_GPIO_WritePin(DEMUX_S0_GPIO_Port, DEMUX_S0_Pin, s0 ? GPIO_PIN_SET : GPIO_PIN_RESET);
    HAL_GPIO_WritePin(DEMUX_S1_GPIO_Port, DEMUX_S1_Pin, s1 ? GPIO_PIN_SET : GPIO_PIN_RESET);
    HAL_GPIO_WritePin(DEMUX_S2_GPIO_Port, DEMUX_S2_Pin, s2 ? GPIO_PIN_SET : GPIO_PIN_RESET);
}

void Motor_Select(const Motor *mmotor)
{
	if (mmotor == NULL) return;
    switch (mmotor->ID){
    	case MOTOR_1:
    		Mux_Select(0,0,0);
    		break;
    	case MOTOR_2:
    		Mux_Select(0,0,1);
    		break;
    	/*extend as i test more motors*/
    	default:
    		/*Error state*/
    		break;
    /*extend in theory as i add motors 2-5*/
    }
}


void Motor_SetDirection(const Motor *mmotor)
{
	if (mmotor == NULL) return;
	// MELISSA CHANGED THIS
	// it used to be HAL_GPIO_WritePin(STEPPER_DIR_PORT, STEPPER_DIR_PIN, .....
	HAL_GPIO_WritePin(STPR_D1_GPIO_Port, STPR_D1_Pin,
						(mmotor->DIR == MOTOR_DIR_CCW) ? GPIO_PIN_SET : GPIO_PIN_RESET);
}

void Motor_SendSteps_Blocking(Motor *mmotor, uint32_t steps)
{
	if (mmotor == NULL || mmotor->clk == NULL || steps == 0) return;

	/*set up our global interrupt logic*/
    step_count = 0;
    step_target = steps;
    stepper_done = 0;
    __HAL_TIM_SET_COUNTER(mmotor->clk, 0);
    __HAL_TIM_CLEAR_FLAG(mmotor->clk, TIM_FLAG_UPDATE);

    /*start our timer*/
    HAL_TIM_Base_Start_IT(mmotor->clk);
    HAL_TIM_PWM_Start(mmotor->clk, TIM_CHANNEL_1);

    /*
     * Force the CPU to handle stepper to finish
     * Should consider recovering from going past 50/100 steps
     * For future hygine i should add a timeout var
     * if timeout hits then we recover somehow
     * */
    while (!stepper_done){}
    /* stop the timer */
    HAL_TIM_PWM_Stop(mmotor->clk, TIM_CHANNEL_1);
    HAL_TIM_Base_Stop_IT(mmotor->clk);
}

// also realized that we need two more demuxes??//
void Motor_RunMove(Motor *mmotor, uint32_t steps)
{
	if (mmotor == NULL || mmotor->clk == NULL || steps == 0U) return;

    //Motor_DisableAll();
    Motor_Select(mmotor);
    Motor_SetDirection(mmotor);
    /*
     * Assume we are not going to mux dir and en
     * Propose to just have the singal sent to all motors at all times
     * None would advance without a step anyhow
     */
    Motor_SendSteps_Blocking(mmotor,steps);
    //Motor_DisableAll();
}


/*The interupt that counts up to fifity.*/
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if (htim->Instance == TIM4)
	{
	    step_count++;
	    if (step_count >= step_target)
	        stepper_done = 1;
	}
}

/* All motors share TIM4 for step generation.
 * Motor selection is handled by the mux.
 */



/*Wire enable to voltage*/
//void Motor_EnableSelected(void)
//{
//    HAL_GPIO_WritePin(STPR_EN_port, STEPPER_EN_pin, GPIO_PIN_RESET);
//}

//void Motor_DisableAll(void)
//{
//    HAL_GPIO_WritePin(STPR_EN_port, STEPPER_EN_pin, GPIO_PIN_SET);
//}
