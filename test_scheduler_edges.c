
#include <assert.h>
#include <stdio.h>
#include "scheduler.h"

int main(void)
{

    scheduler_init();
    assert(scheduler_run_fcfs(NULL, 0) == 0);

    const SchedulerMetrics *m = scheduler_get_metrics();
    assert(m->completed_tasks == 0);
    assert(m->current_tick == 0);

    scheduler_init();
    assert(scheduler_run_round_robin(NULL, 0, 0) == -1);

    Task late_task[] = {
        {1, 5, 0, 2.0, 1, 20, 0, 0, TASK_READY}
    };

    scheduler_init();
    assert(scheduler_run_fcfs(late_task, 1) == 0);

    m = scheduler_get_metrics();
    assert(m->completed_tasks == 1);
    assert(m->current_tick == 7);
    assert(m->total_waiting_time == 0.0);
    assert(m->total_turnaround_time == 2.0);

    Task deadline_task[] = {
        {1, 0, 0, 3.0, 1, 2, 0, 0, TASK_READY}
    };

    scheduler_init();
    assert(scheduler_run_fcfs(deadline_task, 1) == 0);

    m = scheduler_get_metrics();
    assert(m->completed_tasks == 1);
    assert(m->deadline_misses == 1);

    Task duplicate_tasks[] = {
        {1, 0, 0, 2.0, 1, 10, 0, 0, TASK_READY},
        {1, 0, 0, 1.0, 1, 10, 0, 0, TASK_READY}
    };

    scheduler_init();
    assert(scheduler_run_fcfs(duplicate_tasks, 2) == -1);

    puts("PASS: Scheduler edge-case tests");
    return 0;
}
