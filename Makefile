CC ?= gcc
CFLAGS ?= -O2 -Wall -std=c99
LDLIBS ?= -lm
CORE = scheduler.c task_queue.c drl_scheduler.c inference.c
TEST_SRCS = $(wildcard test_*.c)
TEST_BINS = $(TEST_SRCS:.c=)
BINARIES = scheduler $(TEST_BINS) compare_all_policies compare_policies

.PHONY: all test benchmark dashboard parity python-check clean

all: scheduler

scheduler: main.c inference.c hardware.c inference.h hardware.h weights.h
	$(CC) $(CFLAGS) main.c inference.c hardware.c -o $@ $(LDLIBS)

$(TEST_BINS): %: %.c $(CORE) weights.h
	$(CC) $(CFLAGS) $< $(CORE) -o $@ $(LDLIBS)

compare_all_policies: compare_all_policies.c $(CORE) weights.h
	$(CC) $(CFLAGS) $< $(CORE) -o $@ $(LDLIBS)

compare_policies: compare_policies.c $(CORE) weights.h
	$(CC) $(CFLAGS) $< $(CORE) -o $@ $(LDLIBS)

test: $(TEST_BINS)
	@set -e; for t in $(TEST_BINS); do \
		printf '%-28s' "$$t"; \
		if ./$$t > /tmp/$$t.log 2>&1; then tail -1 /tmp/$$t.log; \
		else echo "FAILED"; cat /tmp/$$t.log; exit 1; fi; \
	done
	@echo "All C tests passed."

benchmark: scheduler compare_all_policies
	./scheduler 15 0.5 100 100
	@echo
	./compare_all_policies

parity: test_inference
	python3 test_policy_parity.py

python-check:
	python3 -m compileall -q .

dashboard: scheduler
	streamlit run app.py

clean:
	rm -f $(BINARIES)
	rm -rf __pycache__
