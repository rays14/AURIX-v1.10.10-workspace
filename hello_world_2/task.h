/*
 * task.h
 *
 *  Created on: May 1, 2025
 *      Author: sray
 */

#ifndef SRC_TASK_H_
#define SRC_TASK_H_

#include "stdint.h"

#define TICK_PERIOD 256
#define MAX_TASKS   100
typedef enum task_state_t {
    STOPPED = 0,
    STARTED = 2
} task_state_t;
typedef void (*task_ptr_t)(void);
struct task_list_t {
    task_ptr_t task;
    uint32_t period;
    uint32_t offset;
    uint32_t overrun;
    enum task_state_t state;
};
extern uint32_t num_tasks;
extern uint32_t tick_period;
extern uint32_t tick;
extern struct task_list_t task_list[MAX_TASKS];

extern void task_init(void);
extern void task_start(void);
extern void task_add(task_ptr_t tb, uint32_t period, uint32_t offset);
extern void task_exec(void *data);

#endif /* SRC_TASK_H_ */

