#include <assert.h>
#include <stdio.h>
#include "task_queue.h"

int main(void)
{
    TaskQueue queue;
    Task task1 = {1, 0, 5.0, 1, 0, TASK_READY};
    Task task2 = {2, 1, 3.0, 2, 0, TASK_READY};
    Task task3 = {3, 2, 1.0, 1, 0, TASK_READY};

    task_queue_init(&queue);

    assert(task_queue_is_empty(&queue));
    assert(task_queue_dequeue(&queue) == NULL);

    assert(task_queue_enqueue(&queue, &task1));
    assert(task_queue_enqueue(&queue, &task2));
    assert(task_queue_enqueue(&queue, &task3));

    assert(task_queue_size(&queue) == 3);
    assert(task_queue_dequeue(&queue) == &task1);
    assert(task_queue_dequeue(&queue) == &task2);
    assert(task_queue_dequeue(&queue) == &task3);

    assert(task_queue_is_empty(&queue));

    assert(!task_queue_enqueue(&queue, NULL));

    {
        static Task storage[TASK_QUEUE_CAPACITY];
        size_t i;

        task_queue_init(&queue);

        for (i = 0; i < TASK_QUEUE_CAPACITY; i++) {
            storage[i].id = (uint32_t)i;
            assert(task_queue_enqueue(&queue, &storage[i]));
        }

        assert(task_queue_is_full(&queue));
        assert(!task_queue_enqueue(&queue, &task1));
        assert(task_queue_size(&queue) == TASK_QUEUE_CAPACITY);

        for (i = 0; i < TASK_QUEUE_CAPACITY; i++) {
            Task *task = task_queue_dequeue(&queue);
            assert(task == &storage[i]);
        }

        assert(task_queue_is_empty(&queue));
    }

    {
        Task a = {101, 0, 1.0, 1, 0, TASK_READY};
        Task b = {102, 0, 1.0, 1, 0, TASK_READY};
        Task c = {103, 0, 1.0, 1, 0, TASK_READY};

        task_queue_init(&queue);

        assert(task_queue_enqueue(&queue, &a));
        assert(task_queue_enqueue(&queue, &b));
        assert(task_queue_dequeue(&queue) == &a);

        assert(task_queue_enqueue(&queue, &c));
        assert(task_queue_dequeue(&queue) == &b);
        assert(task_queue_dequeue(&queue) == &c);
        assert(task_queue_is_empty(&queue));
    }

    printf("PASS: task queue tests\n");
    return 0;
}
