/*
 * sem.c
 *
 *  Created on: May 2, 2025
 *      Author: sray
 */
#include "sem.h"

static void sem_interrupt_disable() {
    IfxCpu_disableInterrupts();
}

static void sem_interrupts_enable() {
    IfxCpu_enableInterrupts();
}
int32_t sem_init(struct sem_t *self) {
    int32_t status = -1;
    if (self) {
        self->val = 1;
        status = 0;
    }
    return status;
}

int32_t sem_take(struct sem_t *self) {
    int32_t status = -1;
    if (self && (self->val > 0)) {
        // We dont need to do this because this
        // a priority based preemptive system
        sem_interrupt_disable();
        self->val = 0;
        status = 0;
        sem_interrupts_enable();
    }
    return status;
}

void sem_give(struct sem_t *self) {
    if (self) {
        // We dont need to do this because this
        // a priority based preemptive system
        sem_interrupt_disable();
        self->val = 1;
        sem_interrupts_enable();
    }
}

