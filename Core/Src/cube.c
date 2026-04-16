#include "cube.h"

#define STEPS_90   400
#define STEPS_180  800

static Motor *g_motors[MOVE_COUNT];

static void Cube_ApplyMove(Motor *m, MoveType type);


static void LED_Helper(uint8_t B, uint8_t R, uint8_t G)
{
    HAL_GPIO_WritePin(LED_BLUE_GPIO_Port,  LED_BLUE_Pin,  B ? GPIO_PIN_SET : GPIO_PIN_RESET);
    HAL_GPIO_WritePin(LED_RED_GPIO_Port,   LED_RED_Pin,   R ? GPIO_PIN_SET : GPIO_PIN_RESET);
    HAL_GPIO_WritePin(LED_GREEN_GPIO_Port, LED_GREEN_Pin, G ? GPIO_PIN_SET : GPIO_PIN_RESET);
}

static void LED_FromMove(CubeMove move)
{
    switch (move)
    {
        case MOVE_R: LED_Helper(1,0,0); break; // blue
        case MOVE_U: LED_Helper(0,1,0); break; // red
        case MOVE_F: LED_Helper(0,0,1); break; // green
        case MOVE_L: LED_Helper(1,1,0); break; // blue + red
        case MOVE_D: LED_Helper(1,1,1); break; // all
        case MOVE_B: LED_Helper(0,1,1); break; // red + green
        default:     LED_Helper(0,0,0); break;
    }
}


void Cube_Init(Motor* m1, Motor* m2, Motor* m3, Motor* m4, Motor* m5, Motor* m6){
	if (!m1 || !m2 || !m3 || !m4 || !m5 || !m6) return;

	g_motors[MOVE_R] = m1;
    g_motors[MOVE_U] = m2;
    g_motors[MOVE_F] = m3;
    g_motors[MOVE_L] = m4;
    g_motors[MOVE_D] = m5;
    g_motors[MOVE_B] = m6;

}

static void Cube_ApplyMove(Motor *m, MoveType type)
{
    if (!m) return;

    uint32_t steps = STEPS_90;

    switch (type)
    {
    case MOVE_NORMAL:
        m->DIR = MOTOR_DIR_CCW;
        steps = STEPS_90;
        break;

    case MOVE_PRIME:
        m->DIR = MOTOR_DIR_CW;
        steps = STEPS_90;
        break;

    case MOVE_DOUBLE:
        m->DIR = MOTOR_DIR_CW;
        steps = STEPS_180;
        break;
    }

    Motor_RunMove(m, steps);
}

void Cube_Move(CubeMove move, MoveType type)
{
    if (move >= MOVE_COUNT) return;

    Motor *m = g_motors[move];
    LED_FromMove(move);
    Cube_ApplyMove(m, type);

    LED_Helper(0,0,0);
}

void Cube_Execute(const CubeMove *moves,
                  const MoveType *types,
                  uint32_t length)
{
    for (uint32_t i = 0; i < length; i++)
    {
        Cube_Move(moves[i], types[i]);
//        HAL_Delay(100); // optional spacing
    }
}
