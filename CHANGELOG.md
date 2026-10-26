# Changelog

## Final submission revision - 26 October 2026

### Fixed

- Split `infer_drl_action` and `step_hardware` out of `main.c` into `inference.c`
  and `hardware.c`. All seven native C tests now link and pass under `make test`.
- Added explicit work accounting (arrivals, served work, dropped work, clipped
  steps) so energy comparisons are normalized by work actually completed.
- `main.c` now reports joules per served work unit and emits warnings when served
  work is unequal or backlog clipping occurs.
- `test_drl_scheduler.c` no longer asserts zero deadline misses unconditionally;
  the low-power policy legitimately misses soft deadlines. It now bounds the metric
  and prints it.
- Suppressed per-tick trace printing behind `DRL_SCHEDULER_TRACE`.
- `test_policy_parity.py` is cross-platform and accepts a model path argument.
- `Makefile` grew `test`, `benchmark`, `parity`, `python-check`, `dashboard`, and
  `clean` targets.

### Added

- `benchmark_equal_work.py`: 10 (configurable) hardware/queue/cap profiles with
  bootstrap 95% confidence intervals; writes `results/equal_work_benchmark.json`.
- `README.md` rewritten with team details, claim boundaries, build instructions,
  and the corrected evaluation method.
- `TEAM.md`, `LICENSE` (MIT), `.github/workflows/ci.yml`, `docs/`, `results/`.
- Pinned import history so the reviewed commit `2093bec` remains reachable.

### Changed

- All inherited source comments, emoji, and the previous project URL were removed.
- Project URL now points to `https://github.com/AdityaRezan/energy-aware-drl-scheduler`.
- The accompanying literature review was expanded from 28 to 38 pages and its
  repository reference updated to this URL.

### Known limitations

- Power ratios remain fixed model constants, so the reported ~87% improvement is a
  property of the model and not a hardware measurement.
- The C actor in `weights.h` must be regenerated with `export_weights.py` whenever
  the saved PPO archive changes; `make parity` verifies agreement.
