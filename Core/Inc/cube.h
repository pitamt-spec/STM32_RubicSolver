#ifndef CUBE_H
#define CUBE_H
#include "main.h"
#include <stdint.h>
#include "motor.h"

typedef enum
{
    MOVE_R,
    MOVE_U,
    MOVE_F,
    MOVE_L,
    MOVE_D,
    MOVE_B,
    MOVE_COUNT
} CubeMove;

typedef enum
{
    MOVE_NORMAL,   // R
    MOVE_PRIME,    // R'
    MOVE_DOUBLE    // R2
} MoveType;

// Init with your 6 motors
void Cube_Init(Motor *m1, Motor *m2, Motor *m3,
               Motor *m4, Motor *m5, Motor *m6);

// Perform a single move
void Cube_Move(CubeMove move, MoveType type);

// run a sequence
void Cube_Execute();

// Philosopically this parses
void String_To_Moves(const char *str);

// Public API to do move sequence
void Cube_Execute_String(const char *str);


#endif
