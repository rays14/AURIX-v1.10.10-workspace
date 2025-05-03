/*
 * cbuff.h
 *
 *  Created on: May 2, 2025
 *      Author: sray
 */
#include "stdint.h"
#include "stdbool.h"
#include "sem.h"

struct cbuff_t {
    struct sem_t sem;
    int32_t *buf; // Buffer
    uint32_t h;   // Head pointer
    uint32_t t;   // Tail pointer
    uint32_t sz;  // Number of items in the queue
};

void cbuff_init(struct cbuff_t *self, int32_t *buf, uint32_t sz);
int32_t cbuff_push(struct cbuff_t *self, int32_t val);
int32_t cbuff_pull(struct cbuff_t *self);
