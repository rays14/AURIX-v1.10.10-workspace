/*
 * sem.h
 *
 *  Created on: May 2, 2025
 *      Author: sray
 */
#ifndef _SEM_
#define _SEM_ 1
#include "stdint.h"
#include "stdbool.h"
#include "IfxCpu.h"

struct sem_t {
    uint8_t val;
};

int32_t sem_init(struct sem_t *self);
int32_t sem_take(struct sem_t *self);
void sem_give(struct sem_t *self);

#endif
