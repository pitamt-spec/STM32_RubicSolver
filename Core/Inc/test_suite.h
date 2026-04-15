#ifndef TEST_SUITE_H
#define TEST_SUITE_H

#include "main.h"

#include "motor.h"
#include <stdint.h>

void TestSuite_Init(Motor *mmotor1, Motor *mmotor2);
void Test_Motor_RunOnce(void);
void Test_WS2812_RunOnce(void);
void TestSuite_RunLoop(void);

#endif
