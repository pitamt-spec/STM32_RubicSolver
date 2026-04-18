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

extern char kociemba_string[64];
extern uint8_t rx_kociemba[64];
extern uint8_t solve_ready_flag;
extern uint8_t tx_start[];
extern UART_HandleTypeDef huart2;

typedef enum
{
    NORMAL = 0,
    FAST = 1,
	SUPER_FAST = 2,
	PARTY = 3,
	INV = 4
} SolveMode;

void camera_processing_helper();
void camera_processing_display();

void cube_solving_helper(uint8_t speed);

void solve_reshuffle_display();
void solve_mode_display();
void solve_mode_touch();


void test_mode_display();
void test_mode_touch();

void default_pattern_buttons();
void pattern_mode_display();
void pattern_mode_touch();

void manual_display();
void manual_mode_touch();

#endif /* INC_SCREEN_H_ */
