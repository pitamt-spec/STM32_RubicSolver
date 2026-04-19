#include "cube.h"

#define STEPS_90   400 // TODO remove?
#define STEPS_180  800 //TODO remove?

#define STEPS_190	844
#define STEPS_100	444
#define STEPS_10	44
#define STEPS_15	66
#define MAX_CUBE_MOVES 64 // Prevent garbage bs


static Motor *g_motors[MOVE_COUNT];

//TODO: I highkey dont know what the size should be
//MELISSA: lets start with 24??
static CubeMove moves[MAX_CUBE_MOVES];
static MoveType types[MAX_CUBE_MOVES];
static uint32_t g_move_count = 0;

static void Cube_ApplyMove(Motor *m, MoveType type);

static void LED_Helper(uint8_t B, uint8_t R, uint8_t G) // TODO remove after debugging
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

//	g_motors[MOVE_R] = m1;
//    g_motors[MOVE_U] = m2;
//    g_motors[MOVE_F] = m3;
//    g_motors[MOVE_L] = m4;
//    g_motors[MOVE_D] = m5;
//    g_motors[MOVE_B] = m6;

    g_motors[MOVE_F] = m1;
    g_motors[MOVE_L] = m2;
    g_motors[MOVE_U] = m3;
    g_motors[MOVE_B] = m4;
    g_motors[MOVE_D] = m5;
    g_motors[MOVE_R] = m6;

}

/* MELISSA: made cube move 100 then back 10 for 90 deg, and 190 and back 10 for 180 deg */
static void Cube_ApplyMove(Motor *m, MoveType type)
{
    if (!m) return;
    HAL_GPIO_WritePin(STPR_EN_GPIO_Port, STPR_EN_Pin, GPIO_PIN_RESET);
    switch (type)
    {
    case MOVE_NORMAL:
        m->DIR = MOTOR_DIR_CCW;
        Motor_RunMove(m, STEPS_100);
        m->DIR = MOTOR_DIR_CW;
//        Motor_RunMove(m, (m->ID != MOTOR_4) ? STEPS_10 : STEPS_15);
        Motor_RunMove(m, STEPS_10);
        break;

    case MOVE_PRIME:
        m->DIR = MOTOR_DIR_CW;
        Motor_RunMove(m, STEPS_100);
		m->DIR = MOTOR_DIR_CCW;
		Motor_RunMove(m, STEPS_10);
        break;

    case MOVE_DOUBLE:
        m->DIR = MOTOR_DIR_CW;
        Motor_RunMove(m, STEPS_190);
        m->DIR = MOTOR_DIR_CCW;
        Motor_RunMove(m, STEPS_10);
        break;
    }
    HAL_GPIO_WritePin(STPR_EN_GPIO_Port, STPR_EN_Pin, GPIO_PIN_SET);
}

void Cube_Move(CubeMove move, MoveType type)
{
    if (move >= MOVE_COUNT) return;

    Motor *m = g_motors[move];
    LED_FromMove(move);
    Cube_ApplyMove(m, type);

    LED_Helper(0,0,0);
}

void Cube_Execute(void)
{
	if (g_move_count == 0) return; // this should be bad i think
    for (uint32_t i = 0; i <  g_move_count; i++)
    {
        Cube_Move(moves[i], types[i]);
    }
}

void Cube_Execute_Reverse(void)
{
    for (int i = g_move_count - 1; i >= 0; i--)
    {
        MoveType inv;

        if (types[i] == MOVE_NORMAL) inv = MOVE_PRIME;
        else if (types[i] == MOVE_PRIME) inv = MOVE_NORMAL;
        else inv = MOVE_DOUBLE;

        Cube_Move(moves[i], inv);
    }
}

void String_To_Moves(const char *str)
{
    uint32_t idx = 0;   // index into moves/types
    uint32_t i = 0;     // index into string
    g_move_count = 0; 	// reset this piece of shit

    while (str[i] != '\0' && idx < MAX_CUBE_MOVES)
    {
        CubeMove move;
        MoveType type = MOVE_NORMAL;

        // 1. Parse move
        switch (str[i])
        {
            case 'R':
            	move = MOVE_R;
            	type = MOVE_NORMAL;
            	break;
            case 'U':
            	move = MOVE_U;
            	type = MOVE_NORMAL;
            	break;
            case 'F':
            	move = MOVE_F;
            	type = MOVE_NORMAL;
            	break;
            case 'L':
            	move = MOVE_L;
            	type = MOVE_NORMAL;
            	break;
            case 'D':
            	move = MOVE_D;
            	type = MOVE_NORMAL;
            	break;
            case 'B':
            	move = MOVE_B;
            	type = MOVE_NORMAL;
            	break;

            case 'r':
            	move = MOVE_R;
            	type = MOVE_PRIME;
            	break;
            case 'u':
            	move = MOVE_U;
            	type = MOVE_PRIME;
            break;
            case 'f':
            	move = MOVE_F;
            	type = MOVE_PRIME;
            	break;
            case 'l':
            	move = MOVE_L;
            	type = MOVE_PRIME;
            	break;
            case 'd':
            	move = MOVE_D;
            	type = MOVE_PRIME;
            	break;
            case 'b':
            	move = MOVE_B;
            	type = MOVE_PRIME;
            	break;

            default:
            	// If we get here didn't we fuck up the string???
                i++;
                printf("WE FUCKED UP");
                continue;
        }


        // Store
        moves[idx] = move;
        types[idx] = type;
        idx++;
        i++;
    }
    g_move_count = idx;
}

/*Monte claro algo*/
void monte_carlo_shuffle(uint32_t k)
{
    if (k > MAX_CUBE_MOVES) {
        k = MAX_CUBE_MOVES;
    }

    g_move_count = 0;

    for (uint32_t i = 0; i < k; i++)
    {
        CubeMove move = (CubeMove)(rand() % MOVE_COUNT);

        int r = rand() % 2;
        MoveType type;
        if (r == 0) type = MOVE_NORMAL;
        else type = MOVE_PRIME;

        moves[i] = move;
        types[i] = type;
        g_move_count++;
    }
}

void shuffle_cube(void){
	monte_carlo_shuffle(25);
	Cube_Execute();
}

/*Step-by-Step Helpers*/
uint32_t Cube_GetMoveCount(void) {
    return g_move_count;
}

CubeMove Cube_GetMoveAt(uint32_t idx) {
    if (idx >= g_move_count) return MOVE_COUNT;
    return moves[idx];
}

MoveType Cube_GetMoveTypeAt(uint32_t idx) {
    if (idx >= g_move_count) return MOVE_NORMAL;
    return types[idx];
}

void StepByStep_RunForward(uint32_t idx) {
    CubeMove move = Cube_GetMoveAt(idx);
    MoveType type = Cube_GetMoveTypeAt(idx);
    Cube_Move(move, type);
}

void StepByStep_RunBackward(uint32_t idx) {
    CubeMove move = Cube_GetMoveAt(idx);
    MoveType type = Cube_GetMoveTypeAt(idx);

    MoveType inv;
    if (type == MOVE_NORMAL) inv = MOVE_PRIME;
    else if (type == MOVE_PRIME) inv = MOVE_NORMAL;
    else inv = MOVE_DOUBLE;

    Cube_Move(move, inv);
}

/*Start patterns*/
void Cube_Execute_String(const char *str)
{
    String_To_Moves(str);
    Cube_Execute();
}

void Flower_Pattern(void)
{
	const char *pattern = "RBUUlbRlfBLBDDlfUUDD";
	Cube_Execute_String(pattern);
}
void Dot_Pattern(void){
	const char *pattern = "URlFbUdl";
	Cube_Execute_String(pattern);
}

void Bird_Pattern(void){
	 const char *pattern = "UFFRRUULLUBBUULLDLLFFUURRBB";
	 Cube_Execute_String(pattern);
}

void Fish_Pattern(void){
	const char *pattern = "fULDFRlUFFUUBBDDBdrB";
	Cube_Execute_String(pattern);
}


void Cross_Pattern(void){
	const char *pattern = "DRRLLuDLLFFUUDDFFRRu";
	Cube_Execute_String(pattern);
}

void Chess_Pattern(void){
	const char *pattern = "RRllFFBBUUDD";
	Cube_Execute_String(pattern);
}

