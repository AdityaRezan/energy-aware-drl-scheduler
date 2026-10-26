#include <stdlib.h>
#include "hardware.h"

#define ACTION_COUNT 4

static const float POWER_RATIOS[ACTION_COUNT] = {0.08f, 0.20f, 0.48f, 1.00f};
static const float WORK_RATES[ACTION_COUNT] = {0.20f, 0.40f, 0.70f, 1.00f};
static const float TEMP_RISE[ACTION_COUNT] = {0.01f, 0.02f, 0.05f, 0.10f};

static float clamp01(float value)
{
    if (value < 0.0f) return 0.0f;
    if (value > 1.0f) return 1.0f;
    return value;
}

void work_accounting_init(WorkAccounting *accounting)
{
    accounting->arrivals = 0.0;
    accounting->served_work = 0.0;
    accounting->dropped_work = 0.0;
    accounting->clipped_steps = 0;
}

void step_hardware(
    SystemState *sys,
    int action,
    float *pwr,
    float max_power_watt,
    float power_cap_ratio,
    WorkAccounting *accounting)
{
    float calculated_pwr;
    float max_allowed_pwr;
    float arrival;
    float available;
    float served;
    float remainder;
    float lost;

    if (action < 0) action = 0;
    if (action >= ACTION_COUNT) action = ACTION_COUNT - 1;

    if (sys->deadline_slack < 0.20f && sys->queue_load > 0.4f) {
        action = 3;
    }

    calculated_pwr = POWER_RATIOS[action] * max_power_watt;
    max_allowed_pwr = max_power_watt * power_cap_ratio;
    if (calculated_pwr > max_allowed_pwr) {
        calculated_pwr = max_allowed_pwr;
    }

    *pwr = calculated_pwr;
    sys->total_power += *pwr;

    arrival = ((float)rand() / RAND_MAX) * 0.3f + 0.1f;
    if (arrival < 0.0f) arrival = 0.0f;

    available = sys->queue_load + arrival;
    served = WORK_RATES[action] < available ? WORK_RATES[action] : available;
    remainder = available - served;
    lost = remainder > 1.0f ? remainder - 1.0f : 0.0f;

    sys->queue_load = clamp01(remainder);
    sys->deadline_slack = clamp01(sys->deadline_slack + (served - arrival));
    sys->temp = clamp01(sys->temp + TEMP_RISE[action] - 0.02f);
    sys->active_core = (action >= 2) ? 1.0f : 0.0f;

    if (accounting != NULL) {
        accounting->arrivals += arrival;
        accounting->served_work += served;
        accounting->dropped_work += lost;
        if (lost > 0.0f) accounting->clipped_steps += 1;
    }
}
