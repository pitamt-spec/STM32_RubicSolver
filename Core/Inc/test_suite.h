#ifndef TESTSUITE_H
#define TESTSUITE_H

#include "main.h"

#include "motor.h"
#include <stdint.h>

void TestSuite_Init(Motor *mmotor1, Motor *mmotor2, Motor *mmotor3, Motor *mmotor4, Motor *mmotor5, Motor *mmotor6);
/*Run through all motors once*/
//void TestSuite_RunOnce(void);
//void Basic_Solve(void);
void TestSuite_RunLoop(void);

#endif
