/*
 * screen.c
 *
 *  Created on: Apr 14, 2026
 *      Author: mjbarbat
 */
#include "screen.h"
#include "test_suite.h"
#include "cube.h"


// helper function for camera processing
// used by solve_mode_touch() and step_by_step_touch()
void camera_processing_helper(){
	// reset (faster than Displ_CLS)
	Displ_FillArea(20, 50, 280, 100, BLACK);
	Displ_FillArea(20, 160, 280, 100, BLACK);
	Displ_FillArea(20, 270, 280, 100, BLACK);

	Displ_FillArea(20, 380, 280, 100, DDD_WHITE);
	Displ_WString(45, 420, "Scanning Cube", Font24, 1, WHITE, DDD_WHITE);
	// TODO TODO turn on 3 LEDs
	// TODO TODO Camera 1 processing goes here
	// TODO TODO turn off 3 leds, turn on the other 3 LEDs
	// TODO TODO camera processing goes hereto
	// TODO TODO turn off 3 leds
}

void cube_solving_helper(uint8_t speed){
	Displ_FillArea(20, 380, 280, 100, DDD_WHITE);
	Displ_WString(45, 420, "Solving Cube!", Font24, 1, WHITE, DDD_WHITE);
	if(speed == PARTY){
		// TODO TODO turn party lights on
		// TODO TODO run solving alg on normal speed (0)
		// TODO TODO turn party lights off
	}
	// TODO TODO call solve function with kociemba alg (speed input is int 0-2)
	// TODO TODO check for solved state??
}

// Display for last state of solve mode. Gives option to reshuffle
void solve_reshuffle_display(){
	Displ_FillArea(20, 380, 280, 100, D_GREEN);
	Displ_WString(90, 420, "RESHUFFLE", Font24, 1, WHITE, D_GREEN);

	// TODO add total moves
	// TODO add timer to show time it took to solve
}

// Display menu for solve mode (1)
void solve_mode_display(){
	// Title
	Displ_WString(70, 10, "Solve Mode", Font24, 1, WHITE, BLACK); // X=10, Y=10

	// --- Normal ---
	Displ_FillArea(20, 50, 280, 100, D_RED);        // X=20, Y=50, Width=280, Height=100
	Displ_WString(115, 90, "Normal", Font20, 1, WHITE, D_RED);

	// --- Fast ---
	Displ_FillArea(20, 160, 280, 100, D_RED);        // X=20, Y=160, Width=280, Height=100
	Displ_WString(130, 200, "Fast", Font20, 1, WHITE, D_RED);

	// --- Super Fast ---
	Displ_FillArea(20, 270, 280, 100, D_RED);        // X=20, Y=160, Width=280, Height=100
	Displ_WString(95, 310, "Super Fast", Font20, 1, WHITE, D_RED);

	// --- Party! ---
	Displ_FillArea(20, 380, 280, 100, D_RED);        // X=20, Y=160, Width=280, Height=100
	Displ_WString(115, 420, "P", Font24, 1, RED, DDDD_WHITE);
	Displ_WString(130, 420, "A", Font24, 1, ORANGE, DDDD_WHITE);
	Displ_WString(145, 420, "R", Font24, 1, YELLOW, DDDD_WHITE);
	Displ_WString(160, 420, "T", Font24, 1, GREEN, DDDD_WHITE);
	Displ_WString(175, 420, "Y", Font24, 1, BLUE, DDDD_WHITE);
	Displ_WString(190, 420, "!", Font24, 1, MAGENTA, DDDD_WHITE);
}

// Poll for touch for solve mode (1)
void solve_mode_touch(){
	uint16_t x = 0;
	uint16_t y = 0;
	uint8_t isTouch = 0;
	SolveMode mode = INV; // default mode

	// Get touch data
	Touch_GetXYtouch(&x, &y, &isTouch);

	if (isTouch) {
		//printf("Touch at X: %d, Y: %d\r\n", x, y); //For debugging

		// Check NORMAL
		if (solve_state == 0 && x >= 370 && x <= 650 && y >= 330 && y <= 430) {
			Displ_FillArea(20, 50, 280, 100, RED);
			Displ_WString(115, 90, "Normal", Font20, 1, WHITE, RED);
			mode = NORMAL;
			Touch_WaitForUntouch(1000); // debounce (remove once we add motor code?)
		}

		// Check FAST
		else if (solve_state == 0 && x >= 370 && x <= 650 && y >= 215 && y <= 315) {
			Displ_FillArea(20, 160, 280, 100, RED);
			Displ_WString(130, 200, "Fast", Font20, 1, WHITE, RED);
			mode = FAST;
			Touch_WaitForUntouch(1000); // debounce (remove once we add motor code?)
		}

		// Check SUPER FAST
		else if (solve_state == 0 && x >= 370 && x <= 650 && y >= 105 && y <= 205) {
			Displ_FillArea(20, 270, 280, 100, RED);
			Displ_WString(95, 310, "Super Fast", Font20, 1, WHITE, RED);
			mode = SUPER_FAST;
			Touch_WaitForUntouch(1000); // debounce (remove once we add motor code?)
		}

		// Check PARTY
		else if (solve_state == 0 && x >= 370 && x <= 650 && y >= 0 && y <= 95) {
			// --- Party! ---
			Displ_FillArea(20, 380, 280, 100, DDDD_WHITE);
			Displ_WString(115, 420, "P", Font24, 1, RED, DDDD_WHITE);
			Displ_WString(130, 420, "A", Font24, 1, ORANGE, DDDD_WHITE);
			Displ_WString(145, 420, "R", Font24, 1, YELLOW, DDDD_WHITE);
			Displ_WString(160, 420, "T", Font24, 1, GREEN, DDDD_WHITE);
			Displ_WString(175, 420, "Y", Font24, 1, BLUE, DDDD_WHITE);
			Displ_WString(190, 420, "!", Font24, 1, MAGENTA, DDDD_WHITE);
			mode = PARTY;
			Touch_WaitForUntouch(1000); // debounce (remove once we add motor code?)
		}

		// Check RESHUFFLE
		else if (solve_state == 1 && x >= 370 && x <= 650 && y >= 0 && y <= 95) {
			 Displ_FillArea(20, 380, 280, 100, GREEN);
			 Displ_WString(90, 420, "RESHUFFLE", Font24, 1, WHITE, GREEN);
			 //TODO TODO reshuffle alg
			 mode = INV;
			 solve_mode_display();
		 }

		// TODO add small delay?
		// start solving cube
		if(mode != INV){
			solve_state = 1;
			camera_processing_helper();
			cube_solving_helper(mode);
			solve_reshuffle_display();
		}
	}
}


// Display menu for test mode (2)
void test_mode_display(){
	// Title
	Displ_WString(10, 10, "TEST MODE", Font24, 1, WHITE, BLACK); // X=10, Y=10

	// --- Algorithm 1 ---
	Displ_FillArea(10, 50, 280, 120, DD_GREEN);        // X=10, Y=50, Width=280, Height=120
	Displ_WString(70, 100, "ALGORITHM 1", Font20, 1, WHITE, DD_GREEN);

	// --- Algorithm 2 ---
	Displ_FillArea(10, 180, 280, 120, DD_GREEN);        // X=10, Y=180, Width=280, Height=120
	Displ_WString(70, 230, "ALGORITHM 2", Font20, 1, WHITE, DD_GREEN);

	// --- Algorithm 3 ---
	Displ_FillArea(10, 310, 280, 120, DD_GREEN);        // X=10, Y=310, Width=280, Height=120
	Displ_WString(70, 360, "ALGORITHM 3", Font20, 1, WHITE, DD_GREEN);
}

// Poll for touch for test mode (2)
void test_mode_touch(){
	uint16_t x = 0;
	uint16_t y = 0;
	uint8_t isTouch = 0;

	// Get touch data
	Touch_GetXYtouch(&x, &y, &isTouch);

	if (isTouch) {
		//printf("Touch at X: %d, Y: %d\r\n", x, y); //For debugging

		// CHECK ALG 1
		if (x >= 370 && x <= 635 && y >= 310 && y <= 420) {
			Displ_FillArea(10, 50, 280, 120, D_GREEN);
			Displ_WString(70, 100, "ALGORITHM 1", Font20, 1, WHITE, D_GREEN);
			//TODO TODO ADD ALG CODE HERE
			Set_All_Next_Color();
			Touch_WaitForUntouch(1000); // debounce (remove once we add motor code?)
			Displ_FillArea(10, 50, 280, 120, DD_GREEN);
			Displ_WString(70, 100, "ALGORITHM 1", Font20, 1, WHITE, DD_GREEN);
		}

		// CHECK ALG 2
		else if (x >= 370 && x <= 635 && y >= 180 && y <= 295) {
			Displ_FillArea(10, 180, 280, 120, D_GREEN);
			Displ_WString(70, 230, "ALGORITHM 2", Font20, 1, WHITE, D_GREEN);
			//TODO TODO ADD ALG CODE HERE
			Turn_LED_Off();
			Touch_WaitForUntouch(1000); // debounce (remove once we add motor code?)
			Displ_FillArea(10, 180, 280, 120, DD_GREEN);
			Displ_WString(70, 230, "ALGORITHM 2", Font20, 1, WHITE, DD_GREEN);
		}

		// CHECK ALG 3
		else if (x >= 370 && x <= 635 && y >= 45 && y <= 170) {
			Displ_FillArea(10, 310, 280, 120, D_GREEN);        // X=10, Y=310, Width=280, Height=120
			Displ_WString(70, 360, "ALGORITHM 3", Font20, 1, WHITE, D_GREEN);
			//TODO TODO ADD ALG CODE HERE
			All_White();
			Touch_WaitForUntouch(1000); // debounce (remove once we add motor code?)
			Displ_FillArea(10, 310, 280, 120, DD_GREEN);        // X=10, Y=310, Width=280, Height=120
			Displ_WString(70, 360, "ALGORITHM 3", Font20, 1, WHITE, DD_GREEN);
		}
	}
}

// used by pattern_mode_display and reset
void default_pattern_buttons(){
	// Flowers
	Displ_FillArea(10, 50, 140, 120, DD_CYAN);        // X=10, Y=50, Width=140, Height=120
	Displ_WString(35, 100, "Flowers", Font20, 1, WHITE, DD_CYAN);

	// Dots
	Displ_FillArea(160, 50, 140, 120, DD_CYAN);        // X=160, Y=50, Width=140, Height=120
	Displ_WString(200, 100, "Dots", Font20, 1, WHITE, DD_CYAN);

	// Birds
	Displ_FillArea(10, 180, 140, 120, DD_CYAN);        // X=10, Y=50, Width=140, Height=120
	Displ_WString(45, 230, "Birds", Font20, 1, WHITE, DD_CYAN);

	// Fish
	Displ_FillArea(160, 180, 140, 120, DD_CYAN);        // X=160, Y=50, Width=140, Height=120
	Displ_WString(200, 230, "Fish", Font20, 1, WHITE, DD_CYAN);

	// Crosses
	Displ_FillArea(10, 310, 140, 120, DD_CYAN);        // X=10, Y=50, Width=140, Height=120
	Displ_WString(35, 360, "Crosses", Font20, 1, WHITE, DD_CYAN);

	// Chess
	Displ_FillArea(160, 310, 140, 120, DD_CYAN);        // X=160, Y=50, Width=140, Height=120
	Displ_WString(195, 360, "Chess", Font20, 1, WHITE, DD_CYAN);
}

// Display menu for pretty patterns (3)
void pattern_mode_display(){
	// Title
	Displ_WString(20, 10, "Pretty Patterns!", Font24, 1, WHITE, BLACK); // X=10, Y=10

	default_pattern_buttons();
}

// Poll for touch for test mode (3)
void pattern_mode_touch(){
	uint16_t x = 0;
	uint16_t y = 0;
	uint8_t isTouch = 0;

	// Get touch data
	Touch_GetXYtouch(&x, &y, &isTouch);

	if (isTouch) {
//		printf("Touch at X: %d, Y: %d\r\n", x, y); //For debugging
//		printf("State: %d \r\n", pretty_pattern_selected);

		// Check Flowers
		if (!pretty_pattern_selected && x >= 370 && x <= 490 && y >= 310 && y <= 410) {
			pretty_pattern_selected = 1;
			Displ_FillArea(10, 50, 140, 120, D_CYAN);
			Displ_WString(35, 100, "Flowers", Font20, 1, WHITE, D_CYAN);

			//make other boxes grey
			Displ_FillArea(160, 50, 140, 120, DD_WHITE);
			Displ_FillArea(10, 180, 140, 120, DD_WHITE);
			Displ_FillArea(160, 180, 140, 120, DD_WHITE);
			Displ_FillArea(10, 310, 140, 120, DD_WHITE);
			Displ_FillArea(160, 310, 140, 120, DD_WHITE);

			// TODO TODO ALGORITHM CODE GOES HERE
			// R B U2 L' B R L' F' B L B D2 L' F' U2 D2
			Flower_Pattern();
			// reset button appears
			Displ_FillArea(10, 440, 290, 30, D_GREEN);
			Displ_WString(130, 450, "RESET", Font16, 1, WHITE, D_GREEN);
		}

		// Check Dots
		else if (!pretty_pattern_selected && x >= 570 && x <= 680 && y >= 310 && y <= 410) {
			pretty_pattern_selected = 1;
			Displ_FillArea(160, 50, 140, 120, D_CYAN);
			Displ_WString(200, 100, "Dots", Font20, 1, WHITE, D_CYAN);

			//make other boxes grey
			Displ_FillArea(10, 50, 140, 120, DD_WHITE);
			Displ_FillArea(10, 180, 140, 120, DD_WHITE);
			Displ_FillArea(160, 180, 140, 120, DD_WHITE);
			Displ_FillArea(10, 310, 140, 120, DD_WHITE);
			Displ_FillArea(160, 310, 140, 120, DD_WHITE);

			// TODO TODO ALGORITHM CODE GOES HERE
			// U R L' F B' U D' L'
			Dot_Pattern();
			// reset button appears
			Displ_FillArea(10, 440, 290, 30, D_GREEN);
			Displ_WString(130, 450, "RESET", Font16, 1, WHITE, D_GREEN);
		}

		// Check Birds
		else if (!pretty_pattern_selected && x >= 370 && x <= 490 && y >= 180 && y <= 300) {
			pretty_pattern_selected = 1;
			Displ_FillArea(10, 180, 140, 120, D_CYAN);
			Displ_WString(45, 230, "Birds", Font20, 1, WHITE, D_CYAN);

			//make other boxes grey
			Displ_FillArea(10, 50, 140, 120, DD_WHITE);
			Displ_FillArea(160, 50, 140, 120, DD_WHITE);
			Displ_FillArea(160, 180, 140, 120, DD_WHITE);
			Displ_FillArea(10, 310, 140, 120, DD_WHITE);
			Displ_FillArea(160, 310, 140, 120, DD_WHITE);

			// TODO TODO ALGORITHM CODE GOES HERE
			// U F2 R2 U2 L2 U B2 U2 L2 D L2 F2 U2 R2 B2
			Bird_Pattern();
			// reset button appears
			Displ_FillArea(10, 440, 290, 30, D_GREEN);
			Displ_WString(130, 450, "RESET", Font16, 1, WHITE, D_GREEN);
		}

		// Check Fish
		else if (!pretty_pattern_selected && x >= 570 && x <= 680 && y >= 180 && y <= 300) {
			pretty_pattern_selected = 1;
			Displ_FillArea(160, 180, 140, 120, D_CYAN);
			Displ_WString(200, 230, "Fish", Font20, 1, WHITE, D_CYAN);

			//make other boxes grey
			Displ_FillArea(10, 50, 140, 120, DD_WHITE);
			Displ_FillArea(160, 50, 140, 120, DD_WHITE);
			Displ_FillArea(10, 180, 140, 120, DD_WHITE);
			Displ_FillArea(10, 310, 140, 120, DD_WHITE);
			Displ_FillArea(160, 310, 140, 120, DD_WHITE);

			// TODO TODO ALGORITHM CODE GOES HERE
			// F' U L D F R L' U F2 U2B2 D2 B D' R' B
			Fish_Pattern();
			// reset button appears
			Displ_FillArea(10, 440, 290, 30, D_GREEN);
			Displ_WString(130, 450, "RESET", Font16, 1, WHITE, D_GREEN);
		}

		// Check Crosses
		else if (!pretty_pattern_selected && x >= 370 && x <= 490 && y >= 50 && y <= 170) {
			pretty_pattern_selected = 1;
			Displ_FillArea(10, 310, 140, 120, D_CYAN);
			Displ_WString(35, 360, "Crosses", Font20, 1, WHITE, D_CYAN);

			//make other boxes grey
			Displ_FillArea(10, 50, 140, 120, DD_WHITE);
			Displ_FillArea(160, 50, 140, 120, DD_WHITE);
			Displ_FillArea(10, 180, 140, 120, DD_WHITE);
			Displ_FillArea(160, 180, 140, 120, DD_WHITE);
			Displ_FillArea(160, 310, 140, 120, DD_WHITE);

			// TODO TODO ALGORITHM CODE GOES HERE
			// D R2 L2 U' D L2 F2 U2 D2 F2 R2 U'
			Cross_Pattern();
			// reset button appears
			Displ_FillArea(10, 440, 290, 30, D_GREEN);
			Displ_WString(130, 450, "RESET", Font16, 1, WHITE, D_GREEN);
		}

		// Check Chess
		else if (!pretty_pattern_selected && x >= 570 && x <= 680 && y >= 50 && y <= 170) {
			pretty_pattern_selected = 1;
			Displ_FillArea(160, 310, 140, 120, D_CYAN);
			Displ_WString(195, 360, "Chess", Font20, 1, WHITE, D_CYAN);

			//make other boxes grey
			Displ_FillArea(10, 50, 140, 120, DD_WHITE);
			Displ_FillArea(160, 50, 140, 120, DD_WHITE);
			Displ_FillArea(10, 180, 140, 120, DD_WHITE);
			Displ_FillArea(160, 180, 140, 120, DD_WHITE);
			Displ_FillArea(10, 310, 140, 120, DD_WHITE);

			// TODO TODO ALGORITHM CODE GOES HERE
			// R L' F2 B2 U2 D2 R L'
			Chess_Pattern();
			// reset button appears
			Displ_FillArea(10, 440, 290, 30, D_GREEN);
			Displ_WString(130, 450, "RESET", Font16, 1, WHITE, D_GREEN);
		}

		// check RESET
		else if(pretty_pattern_selected && x >= 370 && x <= 650 && y >= 0 && y <= 310) {
			pretty_pattern_selected = 0;
			Displ_FillArea(10, 440, 290, 30, GREEN);
			Displ_WString(130, 450, "RESET", Font16, 1, WHITE, GREEN);

			//TODO TODO RESET ALG GOES HERE
			// idea for implementing reset:
			// store last pattern as global var (enum). have function for each pattern.
			//call function here based on last_pattern values
			Cube_Execute_Reverse(); /*Might work might not work; Fuck around and find out*/
			//reset screen
			default_pattern_buttons();
			Displ_FillArea(10, 440, 290, 30, BLACK);
		}
	}

}

// Display menu for manual mode (4)
void manual_display(){
	// Title
	Displ_WString(10, 10, "Manual Control", Font24, 1, WHITE, BLACK); // X=10, Y=10

	// --- Row 1: FRONT FACE ---
	Displ_FillArea(10, 50, 140, 60, D_MAGENTA);        // X=10, Y=50, Width=140, Height=60
	Displ_WString(70, 70, "F", Font20, 1, WHITE, D_MAGENTA);

	Displ_FillArea(160, 50, 140, 60, D_MAGENTA);       // X=160, Y=50, Width=140, Height=60
	Displ_WString(220, 70, "F'", Font20, 1, WHITE, D_MAGENTA);

	// --- Row 2: RIGHT FACE ---
	Displ_FillArea(10, 120, 140, 60, D_MAGENTA);        // X=10, Y=120, Width=140, Height=60
	Displ_WString(70, 140, "R", Font20, 1, WHITE, D_MAGENTA);

	Displ_FillArea(160, 120, 140, 60, D_MAGENTA);       // X=160, Y=120, Width=140, Height=60
	Displ_WString(220, 140, "R'", Font20, 1, WHITE, D_MAGENTA);

	// --- Row 3: UP FACE ---
	Displ_FillArea(10, 190, 140, 60, D_MAGENTA);        // X=10, Y=190, Width=140, Height=60
	Displ_WString(70, 210, "U", Font20, 1, WHITE, D_MAGENTA);

	Displ_FillArea(160, 190, 140, 60, D_MAGENTA);       // X=160, Y=190, Width=140, Height=60
	Displ_WString(220, 210, "U'", Font20, 1, WHITE, D_MAGENTA);

	// --- Row 4: BACK FACE ---
	Displ_FillArea(10, 260, 140, 60, D_MAGENTA);        // X=10, Y=260, Width=140, Height=60
	Displ_WString(70, 280, "B", Font20, 1, WHITE, D_MAGENTA);

	Displ_FillArea(160, 260, 140, 60, D_MAGENTA);       // X=160, Y=260, Width=140, Height=60
	Displ_WString(220, 280, "B'", Font20, 1, WHITE, D_MAGENTA);

	// --- Row 5: LEFT FACE ---
	Displ_FillArea(10, 330, 140, 60, D_MAGENTA);        // X=10, Y=330, Width=140, Height=60
	Displ_WString(70, 350, "L", Font20, 1, WHITE, D_MAGENTA);

	Displ_FillArea(160, 330, 140, 60, D_MAGENTA);       // X=160, Y=330, Width=140, Height=60
	Displ_WString(220, 350, "L'", Font20, 1, WHITE, D_MAGENTA);

	// --- Row 5: DOWN FACE ---
	Displ_FillArea(10, 400, 140, 60, D_MAGENTA);        // X=10, Y=400, Width=140, Height=60
	Displ_WString(70, 420, "D", Font20, 1, WHITE, D_MAGENTA);

	Displ_FillArea(160, 400, 140, 60, D_MAGENTA);       // X=160, Y=400, Width=140, Height=60
	Displ_WString(220, 420, "D'", Font20, 1, WHITE, D_MAGENTA);


}

// Poll for touch for manual mode (4)
void manual_mode_touch(){
	uint16_t x = 0;
	uint16_t y = 0;
	uint8_t isTouch = 0;

	// Get touch data
	Touch_GetXYtouch(&x, &y, &isTouch);

	if (isTouch) {
		// printf("Touch at X: %d, Y: %d\r\n", x, y); //For debugging

		// CHECK F
		if (x >= 370 && x <= 500 && y >= 370 && y <= 435) {
			Displ_FillArea(10, 50, 140, 60, MAGENTA);
			Displ_WString(70, 70, "F", Font20, 1, WHITE, MAGENTA);
			//TODO TODO ADD MOTOR CODE HERE
			Cube_Move(MOVE_F, MOVE_NORMAL);
			Touch_WaitForUntouch(1000); // debounce (remove once we add motor code?)
			Displ_FillArea(10, 50, 140, 60, D_MAGENTA);
			Displ_WString(70, 70, "F", Font20, 1, WHITE, D_MAGENTA);
		}

		// CHECK F'
		else if (x >= 510 && x <= 650 && y >= 370 && y <= 435) {
			Displ_FillArea(160, 50, 140, 60, MAGENTA);
			Displ_WString(220, 70, "F'", Font20, 1, WHITE, MAGENTA);
			//TODO TODO ADD MOTOR CODE HERE
			Cube_Move(MOVE_F, MOVE_PRIME);
			Touch_WaitForUntouch(1000); // debounce (remove once we add motor code?)
			Displ_FillArea(160, 50, 140, 60, D_MAGENTA);
			Displ_WString(220, 70, "F'", Font20, 1, WHITE, D_MAGENTA);
		}

		// CHECK R
		else if (x >= 370 && x <= 500 && y >= 290 && y <= 355) {
			Displ_FillArea(10, 120, 140, 60, MAGENTA);
			Displ_WString(70, 140, "R", Font20, 1, WHITE, MAGENTA);
			//TODO TODO ADD MOTOR CODE HERE
			Cube_Move(MOVE_R, MOVE_NORMAL);
			Touch_WaitForUntouch(1000); // debounce (remove once we add motor code?)
			Displ_FillArea(10, 120, 140, 60, D_MAGENTA);
			Displ_WString(70, 140, "R", Font20, 1, WHITE, D_MAGENTA);
		}

		// CHECK R'
		else if (x >= 510 && x <= 650 && y >= 290 && y <= 355) {
			Displ_FillArea(160, 120, 140, 60, MAGENTA);       // X=160, Y=120, Width=140, Height=60
			Displ_WString(220, 140, "R'", Font20, 1, WHITE, MAGENTA);
			//TODO TODO ADD MOTOR CODE HERE
			Cube_Move(MOVE_R, MOVE_PRIME);
			Touch_WaitForUntouch(1000); // debounce (remove once we add motor code?)
			Displ_FillArea(160, 120, 140, 60, D_MAGENTA);
			Displ_WString(220, 140, "R'", Font20, 1, WHITE, D_MAGENTA);
		}

		// CHECK U
		else if (x >= 390 && x <= 500 && y >= 220 && y <= 280) {
			Displ_FillArea(10, 190, 140, 60, MAGENTA);
			Displ_WString(70, 210, "U", Font20, 1, WHITE, MAGENTA);
			//TODO TODO ADD MOTOR CODE HERE
			Cube_Move(MOVE_U, MOVE_NORMAL);
			Touch_WaitForUntouch(1000); // debounce (remove once we add motor code?)
			Displ_FillArea(10, 190, 140, 60, D_MAGENTA);
			Displ_WString(70, 210, "U", Font20, 1, WHITE, D_MAGENTA);
		}

		// CHECK U'
		else if (x >= 510 && x <= 650 && y >= 220 && y <= 280) {
			Displ_FillArea(160, 190, 140, 60, MAGENTA);
			Displ_WString(220, 210, "U'", Font20, 1, WHITE, MAGENTA);
			//TODO TODO ADD MOTOR CODE HERE
			Cube_Move(MOVE_U, MOVE_PRIME);
			Touch_WaitForUntouch(1000); // debounce (remove once we add motor code?)
			Displ_FillArea(160, 190, 140, 60, D_MAGENTA);
			Displ_WString(220, 210, "U'", Font20, 1, WHITE, D_MAGENTA);
		}

		// CHECK B
		else if (x >= 390 && x <= 500 && y >= 150 && y <= 210) {
			Displ_FillArea(10, 260, 140, 60, MAGENTA);
			Displ_WString(70, 280, "B", Font20, 1, WHITE, MAGENTA);
			//TODO TODO ADD MOTOR CODE HERE
			Cube_Move(MOVE_B, MOVE_NORMAL);
			Touch_WaitForUntouch(1000); // debounce (remove once we add motor code?)
			Displ_FillArea(10, 260, 140, 60, D_MAGENTA);
			Displ_WString(70, 280, "B", Font20, 1, WHITE, D_MAGENTA);
		}

		// CHECK B'
		else if (x >= 510 && x <= 650 && y >= 150 && y <= 210) {
			Displ_FillArea(160, 260, 140, 60, MAGENTA);
			Displ_WString(220, 280, "B'", Font20, 1, WHITE, MAGENTA);
			//TODO TODO ADD MOTOR CODE HERE
			Cube_Move(MOVE_B, MOVE_PRIME);
			Touch_WaitForUntouch(1000); // debounce (remove once we add motor code?)
			Displ_FillArea(160, 260, 140, 60, D_MAGENTA);
			Displ_WString(220, 280, "B'", Font20, 1, WHITE, D_MAGENTA);
		}

		// CHECK L
		else if (x >= 390 && x <= 500 && y >= 85 && y <= 145) {
			Displ_FillArea(10, 330, 140, 60, MAGENTA);
			Displ_WString(70, 350, "L", Font20, 1, WHITE, MAGENTA);
			//TODO TODO ADD MOTOR CODE HERE
			Cube_Move(MOVE_L, MOVE_NORMAL);
			Touch_WaitForUntouch(1000); // debounce (remove once we add motor code?)
			Displ_FillArea(10, 330, 140, 60, D_MAGENTA);
			Displ_WString(70, 350, "L", Font20, 1, WHITE, D_MAGENTA);
		}

		// CHECK L'
		else if (x >= 510 && x <= 650 && y >= 85 && y <= 145) {
			Displ_FillArea(160, 330, 140, 60, MAGENTA);
			Displ_WString(220, 350, "L'", Font20, 1, WHITE, MAGENTA);
			//TODO TODO ADD MOTOR CODE HERE
			Cube_Move(MOVE_L, MOVE_PRIME);
			Touch_WaitForUntouch(1000); // debounce (remove once we add motor code?)
			Displ_FillArea(160, 330, 140, 60, D_MAGENTA);
			Displ_WString(220, 350, "L'", Font20, 1, WHITE, D_MAGENTA);
		}

		// CHECK D
		else if (x >= 390 && x <= 500 && y >= 15 && y <= 75) {
			Displ_FillArea(10, 400, 140, 60, MAGENTA);
			Displ_WString(70, 420, "D", Font20, 1, WHITE, MAGENTA);
			//TODO TODO ADD MOTOR CODE HERE
			Cube_Move(MOVE_D, MOVE_NORMAL);
			Touch_WaitForUntouch(1000); // debounce (remove once we add motor code?)
			Displ_FillArea(10, 400, 140, 60, D_MAGENTA);
			Displ_WString(70, 420, "D", Font20, 1, WHITE, D_MAGENTA);
		}

		// CHECK D'
		else if (x >= 510 && x <= 650 && y >= 15 && y <= 75) {
			Displ_FillArea(160, 400, 140, 60, MAGENTA);
			Displ_WString(220, 420, "D'", Font20, 1, WHITE, MAGENTA);
			//TODO TODO ADD MOTOR CODE HERE
			Cube_Move(MOVE_D, MOVE_PRIME);
			Touch_WaitForUntouch(1000); // debounce (remove once we add motor code?)
			Displ_FillArea(160, 400, 140, 60, D_MAGENTA);
			Displ_WString(220, 420, "D'", Font20, 1, WHITE, D_MAGENTA);
		}
	}

}
