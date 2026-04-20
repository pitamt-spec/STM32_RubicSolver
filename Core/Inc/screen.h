/*
 * screen.h
 *
 *  Created on: Apr 14, 2026
 *      Author: mjbarbat
 */

#ifndef INC_SCREEN_H_
#define INC_SCREEN_H_

#include "main.h"
#include "test_suite.h"
#include "cube.h"
#include "NeoPixel.h"
#include "z_touch_XPT2046.h"
#include <stdint.h>


typedef enum
{
    NORMAL = 0,
    FAST = 1,
	SUPER_FAST = 2,
	PARTY = 3,
	INV = 4
} SolveMode;
extern char kociemba_string[64];
extern uint8_t rx_kociemba[64];
extern volatile uint8_t solve_ready_flag;
extern uint8_t tx_start[];
extern UART_HandleTypeDef huart2;
extern uint8_t step_by_step_state;
extern uint8_t total_moves;
extern uint8_t current_move;
extern volatile SolveMode g_solve_mode;
extern volatile int SPEED;



void camera_processing_helper();
void camera_processing_display();

void cube_solving_helper(uint8_t speed);

void solve_reshuffle_display();
void solve_mode_display();
void solve_mode_touch();

void step_by_step_solver();
void step_by_step_start_display();
void step_by_step_main_display();
void step_by_step_done_display();
void step_by_step_touch();


void test_mode_display();
void test_mode_touch();

void default_pattern_buttons();
void pattern_mode_display();
void pattern_mode_touch();

void manual_display();
void manual_mode_touch();

#endif /* INC_SCREEN_H_ */
