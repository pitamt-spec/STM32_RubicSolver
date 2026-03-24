#ifndef TESTSUITE_H
#define TESTSUITE_H

#include "main.h"

#include "motor.h"
#include <stdint.h>

void TestSuite_Init(Motor *mmotor1, Motor *mmotor2);
void TestSuite_RunOnce(void);
void TestSuite_RunLoop(void);

#endif
