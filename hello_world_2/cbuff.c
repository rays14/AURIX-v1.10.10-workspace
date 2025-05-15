/*
 * cbuff.c
 *
 *  Created on: May 2, 2025
 *      Author: sray
 */
#include "cbuff.h"
static void cbuff_interrupt_disable() {
    IfxCpu_disableInterrupts();
}

static void cbuff_interrupt_enable() {
    IfxCpu_enableInterrupts();
}
int32_t cbuff_init(struct cbuff_t *self, int32_t *buf, uint32_t sz) {
    int32_t status = -1;
    if (self && buf && sz) {
        status = sem_init(&self->sem);
        if (status == 0) {
            self->buf = buf;
            self->sz = sz;
            self->h = 0;
            self->t = 0;
            self->num = 0;
        }
    }
    return status;
}

int32_t cbuff_put(struct cbuff_t *self, int32_t val) {
    int32_t status = -1;
    if (self) {
        bool succ = sem_take(&self->sem);
        if (succ == true) {
            if (self->num < (self->sz - 1)) {
                self->buf[self->h] = val;
                self->h = (self->h + 1) % self->sz;
                self->num++;
                status = 0;
            }
            sem_give(&self->sem);
        }
    }
    return status;
}

int32_t cbuff_get(struct cbuff_t *self, int32_t *val) {
    int32_t status = -1;
    if (self) {
        bool succ = sem_take(&self->sem);
        if (succ == true) {
            if (self->num > 0) {
                *val = self->buf[self->t];
                self->t = (self->t + 1) % self->sz;
                self->num--;
                status = 0;
            }
            sem_give(&self->sem);
        }
    }
    return status;
}


