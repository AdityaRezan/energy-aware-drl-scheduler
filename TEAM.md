# Project Team

**Project:** Energy-Aware Adaptive CPU Scheduling for Heterogeneous Multicore Edge
Devices Using Deep Reinforcement Learning

**Repository:** https://github.com/AdityaRezan/energy-aware-drl-scheduler

| # | Name | Registration No. | Email |
|---|---|---|---|
| 1 | Aditya Rajeshwar Karn | 24BEL0087 | aditya.rajeshwar2024@vitstudent.ac.in |
| 2 | Yuvraj Singh | 24BEL0057 | yuvraj.singh2024@vitstudent.ac.in |
| 3 | Aditya Singh | 24BEL0008 | aditya.singh2024c@vitstudent.ac.in |
| 4 | Atharva Sivaraman | 24BEL0082 | atharva.sivaraman2024@vitstudent.ac.in |
| 5 | Yash Jain | 24BEL0035 | yash.jain2024a@vitstudent.ac.in |

## Contribution matrix

The table below is a **proposed** division of work for the final submission. Each
member should confirm or edit their row before the document is submitted, so that the
record matches what actually happened.

| Area | Lead | Scope |
|---|---|---|
| Reinforcement learning environment and training | Aditya Rajeshwar Karn | `edge_env.py`, `train_model.py`, seed and hyperparameter control |
| C inference and weight export | Yuvraj Singh | `inference.c`, `weights.h`, `export_weights.py`, parity testing |
| Baseline schedulers and native test suite | Aditya Singh | `scheduler.c`, `task_queue.c`, `test_*.c`, `Makefile` |
| Evaluation, benchmarking and statistics | Atharva Sivaraman | `benchmark_equal_work.py`, `results/`, equal-work accounting |
| Literature review and documentation | Yash Jain | `docs/`, `README.md`, claim boundaries and references |

## Detailed division of work

The page-by-page allocation of the 38-page literature review, code ownership, peer-review
pairs, presentation slots and the sign-off declaration are recorded in
[CONTRIBUTION.md](CONTRIBUTION.md) and in the printable
[Division of Work](docs/Division_of_Work.pdf) document (editable
[DOCX](docs/Division_of_Work.docx)). Section 28 of the review summarises the functional
areas; Section 28.5 lists the part-to-member mapping.

| Part | Pages | Author |
|---|---|---|
| I | 1-8 | Aditya Rajeshwar Karn |
| II | 9-15 | Yuvraj Singh |
| III | 16-22 | Aditya Singh |
| IV | 23-29 | Atharva Sivaraman |
| V | 30-35 | Yash Jain |
| VI | 36-38 | Shared, five annotated references verified per member |

Each member should confirm their row and sign the declaration before submission. If the
actual division differed, edit `CONTRIBUTION.md`, `TEAM.md` and Section 28.2 of the
review together so all three records agree.

## Governance notes

- All five members have read and approved the final literature review.
- Simulation constants and all reported figures are documented in `README.md` and
  reproduced by `make benchmark` and `python benchmark_equal_work.py`.
- No external hardware measurement, third-party dataset, or human-subject data is
  used in this project.
- The work is original to this team except for the openly licensed libraries listed
  in `requirements.txt` and the works cited in the literature review.
