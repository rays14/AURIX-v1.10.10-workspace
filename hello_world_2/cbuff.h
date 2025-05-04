/*
 * cbuff.h
 *
 *  Created on: May 2, 2025
 *      Author: sray
 */
#ifndef _CBUFF_H_
#define _CBUFF_H_ 1
#include "stdint.h"
#include "stdbool.h"
#include "sem.h"
#include "IfxCpu.h"

struct cbuff_t {
    struct sem_t sem;
    int32_t *buf; // Buffer
    uint32_t sz;  // Size of the above buffer
    uint32_t h;   // Head pointer
    uint32_t t;   // Tail pointer
    uint32_t num; // Number of elements currently in buffer
};

int32_t cbuff_init(struct cbuff_t *self, int32_t *buf, uint32_t sz);
int32_t cbuff_put(struct cbuff_t *self, int32_t val);
int32_t cbuff_get(struct cbuff_t *self, int32_t *val);
#endif
