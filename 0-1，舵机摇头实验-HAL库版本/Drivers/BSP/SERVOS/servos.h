#ifndef __SERVOS_H
#define __SERVOS_H

#include "./SYSTEM/sys/sys.h"

void servos_pwm_chy_init(uint16_t arr, uint16_t psc);
void servos_tune(uint16_t angles);

#endif
