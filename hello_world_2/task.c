/*
 * task.c
 *
 *  Created on: May 1, 2025
 *      Author: sray
 */
#include "IfxCpu.h"
#include "task.h"
uint32_t num_tasks;
uint32_t tick_period;
uint32_t tick;
struct task_list_t task_list[MAX_TASKS];
static void task_interrupt_disable() {
    IfxCpu_disableInterrupts();
}
static void task_interrupt_enable() {
    IfxCpu_enableInterrupts();
}
void task_init(void) {
    num_tasks   = 0;
    tick_period = TICK_PERIOD;
    tick        = 0;
}
void task_start(void) {

}
void task_add(task_ptr_t tb, uint32_t period, uint32_t offset) {
    if (tb && (num_tasks < MAX_TASKS) && (period < TICK_PERIOD) && (offset < TICK_PERIOD)) {
        struct task_list_t *tp = &task_list[num_tasks];
        tp->task   = tb;
        tp->period = period;
        tp->offset = offset;
        tp->state  = STOPPED;
        tp->overrun = 0;
        num_tasks++;
    }
    // TODO: Sort the tasks so the fastest tasks are stacked
    // earlier in the task list and slower tasks later in
    // array.
}
void task_exec(void *data) {
    // Not a reentrant procedure.
    static uint32_t tick = 0;
    static uint32_t time_mod;
    // Turn off interrupts.
    task_interrupt_disable();
    tick = (tick + 1) % tick_period;
    for (uint32_t i = 0; i < num_tasks; i++) {
        struct task_list_t *tp = &task_list[i];
        time_mod = ((tick + tp->offset) % (tp->period));
        if ((STARTED == tp->state) && (0 == time_mod)) {
            tp->overrun++;
            goto task_exec_exit;
        } else if (0 == time_mod) {
            tp->state = STARTED;
            task_interrupt_enable();
            //task_interrupt_nesting_enable();  // Pushes stuff onto stack
            if (tp->task) {
                tp->task();
            }
            //task_interrupt_nesting_disable(); // Pops stuff off the stack
            task_interrupt_disable();
            tp->state = STOPPED;
        }
    }
task_exec_exit:
    task_interrupt_enable();
}
