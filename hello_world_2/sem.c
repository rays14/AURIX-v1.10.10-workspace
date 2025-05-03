/*
 * sem.c
 *
 *  Created on: May 2, 2025
 *      Author: sray
 */
#include "sem.h"

int32_t sem_init(struct sem_t *self) {
    int32_t val = -1;
    if (self) {
        self->val = 1;
        val = 0;
    }
    return val;
}

bool sem_take(struct sem_t *self) {
    bool val = false;
    if (self && (self->val == 1)) {
        self->val = 0;
        val = true;
    }
    return val;
}

void sem_give(struct sem_t *self) {
    if (self) {
        self->val = 1;
    }
}

