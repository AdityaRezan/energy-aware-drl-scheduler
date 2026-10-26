#ifndef HARDWARE_H
#define HARDWARE_H

typedef struct {
    float queue_load;
    float temp;
    float active_core;
    float deadline_slack;
    float total_power;
} SystemState;

typedef struct {
    double arrivals;
    double served_work;
    double dropped_work;
    unsigned long clipped_steps;
} WorkAccounting;

void work_accounting_init(WorkAccounting *accounting);

void step_hardware(
    SystemState *sys,
    int action,
    float *pwr,
    float max_power_watt,
    float power_cap_ratio,
    WorkAccounting *accounting
);

#endif
