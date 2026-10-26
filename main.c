#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "inference.h"
#include "hardware.h"

static double energy_per_work(double joules, double served_work)
{
    if (served_work <= 0.0) return 0.0;
    return joules / served_work;
}

static void print_work_row(const char *name, const WorkAccounting *w, double joules)
{
    printf("  %-22s %9.3f %9.3f %9.3f %8lu %12.4f\n",
           name, w->served_work, w->arrivals, w->dropped_work,
           w->clipped_steps, energy_per_work(joules, w->served_work));
}

int main(int argc, char *argv[])
{
    float max_power_watt = (argc > 1) ? (float)atof(argv[1]) : 15.0f;
    float init_queue = (argc > 2) ? (float)atof(argv[2]) : 0.5f;
    int steps = (argc > 3) ? atoi(argv[3]) : 100;
    float power_cap_pct = (argc > 4) ? (float)(atof(argv[4]) / 100.0) : 1.0f;

    SystemState drl_sys = {init_queue, 0.3f, 0.0f, 0.8f, 0.0f};
    SystemState perf_sys = {init_queue, 0.3f, 0.0f, 0.8f, 0.0f};
    WorkAccounting drl_work;
    WorkAccounting perf_work;
    double drl_energy;
    double perf_energy;
    double savings;
    double drl_epw;
    double perf_epw;
    double normalized_savings;

    if (!(max_power_watt > 0.0f) || steps < 1 || steps > 1000000 ||
        !(power_cap_pct > 0.0f) || power_cap_pct > 1.0f ||
        init_queue < 0.0f || init_queue > 1.0f) {
        fprintf(stderr,
                "Usage: %s [peak_watts] [initial_queue] [steps] [power_cap_percent]\n",
                argv[0]);
        return 2;
    }

    work_accounting_init(&drl_work);
    work_accounting_init(&perf_work);

    printf("=== RESEARCH-ENHANCED DRL CPU SCHEDULER ===\n");
    printf("Target Peak TDP:       %.2f W\n", max_power_watt);
    printf("Dynamic Power Cap:     %.0f%%\n", power_cap_pct * 100.0f);
    printf("Initial Task Backlog:  %.2f\n", init_queue);
    printf("Simulation Timesteps:  %d\n\n", steps);

    srand(42);
    for (int t = 0; t < steps; t++) {
        int action = infer_drl_action(drl_sys.queue_load, drl_sys.temp,
                                      drl_sys.active_core);
        float pwr;
        step_hardware(&drl_sys, action, &pwr, max_power_watt,
                      power_cap_pct, &drl_work);
    }

    srand(42);
    for (int t = 0; t < steps; t++) {
        float pwr;
        step_hardware(&perf_sys, 3, &pwr, max_power_watt, 1.0f, &perf_work);
    }

    drl_energy = drl_sys.total_power;
    perf_energy = perf_sys.total_power;
    savings = perf_energy > 0.0
                  ? ((perf_energy - drl_energy) / perf_energy) * 100.0
                  : 0.0;
    drl_epw = energy_per_work(drl_energy, drl_work.served_work);
    perf_epw = energy_per_work(perf_energy, perf_work.served_work);
    normalized_savings = perf_epw > 0.0
                             ? ((perf_epw - drl_epw) / perf_epw) * 100.0
                             : 0.0;

    printf("Performance Governor Cumulative Energy: %.2f Joules\n", perf_energy);
    printf("DRL C Scheduler Cumulative Energy:       %.2f Joules\n", drl_energy);
    printf("Energy Improvement:                    %.1f%%\n", savings);

    printf("\nWork accounting (simulated work units, identical arrival streams):\n");
    printf("  %-22s %9s %9s %9s %8s %12s\n",
           "Policy", "Served", "Arrived", "Dropped", "Clipped", "J/served");
    print_work_row("Performance governor", &perf_work, perf_energy);
    print_work_row("DRL C scheduler", &drl_work, drl_energy);
    printf("\nnormalized energy improvement (J per served unit): %.1f%%\n",
           normalized_savings);

    if (drl_work.dropped_work > 0.0 || perf_work.dropped_work > 0.0) {
        printf("WARNING: backlog clipping occurred; raw energy improvement is "
               "not a like-for-like comparison.\n");
    }
    if (drl_work.served_work < perf_work.served_work * 0.99) {
        printf("WARNING: DRL served less work than the performance governor "
               "(%.1f%% vs %.1f%%).\n",
               drl_work.arrivals > 0.0
                   ? 100.0 * drl_work.served_work / drl_work.arrivals : 0.0,
               perf_work.arrivals > 0.0
                   ? 100.0 * perf_work.served_work / perf_work.arrivals : 0.0);
    }

    printf("\nAll values are simulated. No CPU frequency is actuated and no "
           "board power is measured.\n");

    return 0;
}
