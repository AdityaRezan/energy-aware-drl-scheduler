
#ifndef DRL_SCHEDULER_H
#define DRL_SCHEDULER_H

#include <stddef.h>
#include <stdint.h>
#include "task.h"
#include "scheduler.h"

typedef struct {
    double simulated_energy_joules;
    double simulated_power_watts;
    uint64_t elapsed_ticks;
    size_t completed_tasks;
    size_t deadline_misses;
    double total_waiting_time;
    double total_turnaround_time;
} DrlSchedulerMetrics;

int scheduler_run_drl(
    Task *tasks,
    size_t task_count,
    double tick_duration_seconds,
    double max_power_watts,
    double power_cap_ratio,
    DrlSchedulerMetrics *result
);

#endif
