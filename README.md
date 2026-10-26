# Energy-Aware Adaptive CPU Scheduling for Heterogeneous Multicore Edge Devices Using Deep Reinforcement Learning

**Course project - final submission**

Repository: https://github.com/AdityaRezan/energy-aware-drl-scheduler

## Team

| Name | Registration No. | Email |
|---|---|---|
| Aditya Rajeshwar Karn | 24BEL0087 | aditya.rajeshwar2024@vitstudent.ac.in |
| Yuvraj Singh | 24BEL0057 | yuvraj.singh2024@vitstudent.ac.in |
| Aditya Singh | 24BEL0008 | aditya.singh2024c@vitstudent.ac.in |
| Atharva Sivaraman | 24BEL0082 | atharva.sivaraman2024@vitstudent.ac.in |
| Yash Jain | 24BEL0035 | yash.jain2024a@vitstudent.ac.in |

Full contributor details and the editable contribution matrix are in [TEAM.md](TEAM.md).

## What this project is

An experimental, software-only study of whether Proximal Policy Optimization (PPO) can
make defensible adaptive scheduling decisions in a simulated heterogeneous-core edge
environment. The repository contains a Gymnasium environment, a PPO training script,
two saved model archives, a pure-C inference path, a C task-level scheduler with FCFS
and Round-Robin baselines, a set of C and Python tests, and a Streamlit dashboard.

All power, temperature, service rate, and workload values in this repository are
**simulated model constants**. The program does not change CPU affinity, does not
actuate DVFS, does not read a power meter, and does not replace the operating-system
scheduler. No claim of measured hardware energy savings is made.

## What changed in the final revision

The imported prototype had three concrete gaps. All three are addressed here.

1. **The C test suite could not be built.** `infer_drl_action` and `step_hardware`
   lived inside `main.c`, which also defined `main()`. Every test that linked against
   it failed with a duplicate-symbol error. Inference is now in `inference.c` and the
   hardware model in `hardware.c`, so `make test` builds and runs all seven C tests.
2. **The headline energy number was not a like-for-like comparison.** The original
   engine clipped the backlog at 1.0 without counting the discarded work, so a policy
   that simply served less work looked more efficient. `hardware.c` now records
   arrivals, served work, dropped work, and clipping events. `main.c` prints energy
   per unit of served work and warns when served work is unequal.
3. **The Python-C parity check was Windows-only and pointed at the wrong binary.**
   `test_policy_parity.py` now accepts a model path as an argument and runs
   `./test_inference` on any platform. A `make parity` target was added.

Also added: a working `Makefile` with `test`, `benchmark`, `parity`, `python-check`,
`dashboard`, and `clean` targets; `benchmark_equal_work.py` for multi-profile
re-measurement with bootstrap confidence intervals; a `LICENSE`; a CI workflow;
the final 38-page literature review in `docs/`; and machine-readable results in
`results/`.

Source comments and emoji were removed from the inherited code. Design rationale and
usage documentation live here and in `docs/` instead.

## Quick start

Requirements: Python 3.10-3.12, GCC (or MinGW on Windows), and `make`.

```bash
git clone https://github.com/AdityaRezan/energy-aware-drl-scheduler.git
cd energy-aware-drl-scheduler
python -m venv .venv
source .venv/bin/activate          # Windows: .venv\Scripts\activate
pip install -r requirements.txt

make                              # build ./scheduler
make test                         # build and run all C tests
make benchmark                    # run the simulator and policy comparison
python benchmark_equal_work.py    # 10 hardware/queue/cap profiles + 95% CIs
make parity                       # Python vs C action agreement (needs stable-baselines3)
streamlit run app.py              # interactive dashboard
```

The C engine can also be invoked directly:

```bash
./scheduler 15 0.5 100 100
```

Arguments are `peak_watts initial_queue steps power_cap_percent`.

## Repository guide

| File | Purpose |
|---|---|
| `edge_env.py` | Five-feature Gymnasium scheduling environment |
| `train_model.py` | PPO training with a fixed seed |
| `evaluate_model.py` | Multi-seed evaluation against fixed-action baselines |
| `compare_adaptive_policies.py` | PPO versus fixed and rule-based heuristics |
| `diagnose_policy.py`, `trace_policy.py`, `inspect_policy_grid.py` | Policy diagnostics |
| `export_weights.py` | Export the actor network to `weights.h` |
| `inference.c` / `inference.h` | C forward pass over the exported actor |
| `hardware.c` / `hardware.h` | Simulated power, thermal, workload, and work accounting |
| `main.c` | Command-line benchmark with normalized energy metrics |
| `scheduler.c`, `task_queue.c`, `drl_scheduler.c` | C task-level schedulers and baselines |
| `test_*.c` | Seven native C tests |
| `test_policy_parity.py` | Python-C action agreement over 1,000 observations |
| `benchmark_equal_work.py` | Equal-work re-measurement harness |
| `app.py` | Streamlit dashboard |
| `docs/` | Final literature review (PDF and editable DOCX) |
| `results/` | Machine-readable benchmark output |

## Evaluation method and current results

Both policies receive the **same pseudorandom arrival stream** (`srand(42)` before
each run). Work is accounted explicitly: `served = min(action_service_rate, queue +
arrival)` and any remainder above the queue capacity is recorded as dropped. Energy
is `sum(power_ratio[action] x peak_watts x tick_duration)`. The comparison metric is
**joules per unit of served work**, not raw cumulative joules.

For the default profile (15 W, initial queue 0.5, 100 steps, 100% cap):

| Policy | Simulated energy | Served work | Dropped work | J per served unit |
|---|---:|---:|---:|---:|
| Performance governor | 1500.00 J | 26.306 | 0.000 | 57.0215 |
| DRL C scheduler | 199.20 J | 26.199 | 0.000 | 7.6034 |

Across 20 profiles (`python benchmark_equal_work.py --profiles 20 --steps 200`):
raw improvement 86.702% (95% CI 86.675-86.729), normalized improvement 86.698%
(95% CI 86.671-86.725), DRL/baseline served-work ratio 0.99967, zero dropped work.
See `results/equal_work_benchmark.json`.

**Interpretation.** Served work is now equal, so the earlier "unequal work" objection
is resolved. The remaining ~87% gap is still an artefact of the fixed power ratios
assigned to actions (0.08 for action 0 versus 1.00 for action 3). It is a property of
the model constants, not an empirical measurement of processor energy. Any submission
must describe it that way.

## Claim boundaries

Supported by this repository:

- A reproducible PPO training and evaluation pipeline in simulation.
- A pure-C inference path with a parity test against the exported actor.
- A task-level C scheduler with FCFS and Round-Robin baselines and passing tests.
- Honest, work-normalized accounting of simulated energy.

Not supported by this repository:

- Measured board energy, thermal sensing, or hardware efficiency claims.
- CPU frequency or affinity actuation on a real operating system.
- Hard real-time guarantees or deadline adherence under all workloads.
- Equivalence between the C `weights.h` actor and the `ppo_edge_scheduler_trained.zip`
  archive. Run `make parity` with the archive that `export_weights.py` consumed.

## Citation

If you use this repository, cite it together with the accompanying review:

```bibtex
@misc{energyAwareDrlScheduler2026,
  title  = {Energy-Aware Adaptive CPU Scheduling for Heterogeneous Multicore
            Edge Devices Using Deep Reinforcement Learning},
  author = {Karn, Aditya Rajeshwar and Singh, Yuvraj and Singh, Aditya and
            Sivaraman, Atharva and Jain, Yash},
  year   = {2026},
  url    = {https://github.com/AdityaRezan/energy-aware-drl-scheduler}
}
```

## License

MIT. See [LICENSE](LICENSE).
