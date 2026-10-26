# Division of Work

**Project:** Energy-Aware Adaptive CPU Scheduling for Heterogeneous Multicore Edge Devices Using Deep Reinforcement Learning  
**Final submission:** 26 October 2026  
**Repository:** https://github.com/AdityaRezan/energy-aware-drl-scheduler  
**Companion document:** `docs/Energy_Aware_CPU_Scheduling_Final_38_Pages.pdf` (Section 28 gives the functional summary; this file gives the detailed allocation).

## 1. Team roster

| # | Name | Registration No. | Institutional email | Primary role |
|---|---|---|---|---|
| 1 | Aditya Rajeshwar Karn | 24BEL0087 | aditya.rajeshwar2024@vitstudent.ac.in | Team lead - environment, training and final integration |
| 2 | Yuvraj Singh | 24BEL0057 | yuvraj.singh2024@vitstudent.ac.in | C inference, weight export and parity evidence |
| 3 | Aditya Singh | 24BEL0008 | aditya.singh2024c@vitstudent.ac.in | Native schedulers, C engine and the test suite |
| 4 | Atharva Sivaraman | 24BEL0082 | atharva.sivaraman2024@vitstudent.ac.in | Evaluation, statistics, reproducibility and CI |
| 5 | Yash Jain | 24BEL0035 | yash.jain2024a@vitstudent.ac.in | Documentation, dashboard and document editor |

## 2. Division of the 38-page literature review

Five contiguous parts aligned with section boundaries. One author and one internal reviewer per part; pages 36-38 are shared.

| Part | Author | Pages | Sections | Pp. | Scope |
|---|---|---|---|---:|---|
| I | Aditya Rajeshwar Karn | 1-8 | Front matter (title, abstract, contents); Sections 1-6 | 8 | Review scope, problem framing, energy semantics, hardware realism, and the 2020-2022 foundations |
| II | Yuvraj Singh | 9-15 | Sections 7-13 | 7 | Runtime power learning, thermal-aware DRL, temporal governors, DAG scheduling, multi-deadline DVFS and invocation economics |
| III | Aditya Singh | 16-22 | Sections 14-20 | 7 | Joint heterogeneous control, partial observability, HiDVFS, repository architecture, implemented state/actions/reward and local C checks |
| IV | Atharva Sivaraman | 23-29 | Sections 21-25 | 7 | Revision priorities, evaluation plan, synthesis, extended review methodology, evidence grading and comparative evidence synthesis |
| V | Yash Jain | 30-35 | Sections 26-29; Appendices A and B | 6 | Remediation and re-measurement, statistical protocol, team governance, limitations and ethics, artefact manifest and glossary |
| VI | Shared | 36-38 | Annotated references [1]-[25] | 3 | Five references verified per member; consolidated by Yash Jain |

> Three pages of annotated references are a shared responsibility. Each member verifies five entries for publication status, DOI and role statement. Yash Jain consolidates the bibliography, but every member signs off on their own five.

## 3. Reference verification split

| Member | Reg. No. | References verified |
|---|---|---|
| Aditya Rajeshwar Karn | 24BEL0087 | [1]-[5] |
| Yuvraj Singh | 24BEL0057 | [6]-[10] |
| Aditya Singh | 24BEL0008 | [11]-[15] |
| Atharva Sivaraman | 24BEL0082 | [16]-[20] |
| Yash Jain | 24BEL0035 | [21]-[25] |

## 4. Technical and code ownership

| Area | Owner | Artefacts owned |
|---|---|---|
| Environment, training and final integration | Aditya Rajeshwar Karn | `edge_env.py, train_model.py, evaluate_model.py, compare_adaptive_policies.py, diagnose_policy.py, inspect_policy_grid.py, trace_policy.py` |
| C inference, weight export and parity evidence | Yuvraj Singh | `inference.c, inference.h, weights.h, export_weights.py, test_inference.c, test_policy.py, test_policy_parity.py` |
| Native schedulers, c engine and the test suite | Aditya Singh | `main.c, hardware.c, hardware.h, scheduler.c, scheduler.h, task_queue.c, task_queue.h, task.h, drl_scheduler.c, drl_scheduler.h, test_*.c, Makefile` |
| Evaluation, statistics, reproducibility and ci | Atharva Sivaraman | `benchmark_equal_work.py, compare_all_policies.c, compare_policies.c, results/equal_work_benchmark.json, .github/workflows/ci.yml` |
| Documentation, dashboard and document editor | Yash Jain | `README.md, TEAM.md, CONTRIBUTION.md, CHANGELOG.md, LICENSE, docs/, app.py` |

## 5. Deliverables outside the manuscript

| Task | Owner | Expected output |
|---|---|---|
| Git workflow, builds, tags and release | Aditya Singh | Makefile, CI workflow, clean reproducible build |
| PPO training, weight export and Python-C parity | Yuvraj Singh | Saved model archives, weights.h, parity log |
| Benchmark sweep, seeds and machine-readable results | Atharva Sivaraman | results/equal_work_benchmark.json, 20-profile CI |
| Streamlit dashboard and live demonstration | Yash Jain | app.py, screenshots, demo script |
| Abstract, final integration and submission package | Aditya Rajeshwar Karn | Final 38-page PDF/DOCX and repository release |
| Reference verification (five entries each) | All five members | Checked bibliography, pages 36-38 |

## 6. Internal peer review

Round-robin, so no member reviews their own part.

| Author | Part authored | Reviews |
|---|---|---|
| Aditya Rajeshwar Karn | Part I (p. 1-8) | Part II (Yuvraj Singh) |
| Yuvraj Singh | Part II (p. 9-15) | Part III (Aditya Singh) |
| Aditya Singh | Part III (p. 16-22) | Part IV (Atharva Sivaraman) |
| Atharva Sivaraman | Part IV (p. 23-29) | Part V (Yash Jain) |
| Yash Jain | Part V (p. 30-35) | Part I (Aditya Rajeshwar Karn) |

## 7. Presentation slots (20-minute talk + 5-minute Q&A)

| Slot | Time | Presenter | Topic |
|---|---|---|---|
| 1 | 0:00-4:00 | Aditya Rajeshwar Karn | Introduction, motivation, scope and contributions |
| 2 | 4:00-8:00 | Yuvraj Singh | Literature 2022-2024 and the Python-to-C export path |
| 3 | 8:00-12:00 | Aditya Singh | Repository architecture, C engine and baseline schedulers |
| 4 | 12:00-16:00 | Atharva Sivaraman | Evaluation design, statistics and the work-normalised results |
| 5 | 16:00-20:00 | Yash Jain | Remediation, claim boundaries, limitations and conclusion |
| - | 20:00-25:00 | All five | Q&A; lead moderates |

## 8. Individual responsibility cards

### 1. Aditya Rajeshwar Karn (24BEL0087)

- **Email:** aditya.rajeshwar2024@vitstudent.ac.in
- **Primary role:** Team lead - environment, training and final integration
- **Authored:** Part I, pages 1-8 (8 pages) - Front matter (title, abstract, contents); Sections 1-6
- **Focus:** Review scope, problem framing, energy semantics, hardware realism, and the 2020-2022 foundations
- **Owns:** `edge_env.py, train_model.py, evaluate_model.py, compare_adaptive_policies.py, diagnose_policy.py, inspect_policy_grid.py, trace_policy.py`
- **References:** [1]-[5]
- **Presents:** 0:00-4:00 - Introduction, motivation, scope and contributions
- **Reviews:** Part II (Yuvraj Singh)
- **Indicative effort:** about 30 hours

### 2. Yuvraj Singh (24BEL0057)

- **Email:** yuvraj.singh2024@vitstudent.ac.in
- **Primary role:** C inference, weight export and parity evidence
- **Authored:** Part II, pages 9-15 (7 pages) - Sections 7-13
- **Focus:** Runtime power learning, thermal-aware DRL, temporal governors, DAG scheduling, multi-deadline DVFS and invocation economics
- **Owns:** `inference.c, inference.h, weights.h, export_weights.py, test_inference.c, test_policy.py, test_policy_parity.py`
- **References:** [6]-[10]
- **Presents:** 4:00-8:00 - Literature 2022-2024 and the Python-to-C export path
- **Reviews:** Part III (Aditya Singh)
- **Indicative effort:** about 28 hours

### 3. Aditya Singh (24BEL0008)

- **Email:** aditya.singh2024c@vitstudent.ac.in
- **Primary role:** Native schedulers, C engine and the test suite
- **Authored:** Part III, pages 16-22 (7 pages) - Sections 14-20
- **Focus:** Joint heterogeneous control, partial observability, HiDVFS, repository architecture, implemented state/actions/reward and local C checks
- **Owns:** `main.c, hardware.c, hardware.h, scheduler.c, scheduler.h, task_queue.c, task_queue.h, task.h, drl_scheduler.c, drl_scheduler.h, test_*.c, Makefile`
- **References:** [11]-[15]
- **Presents:** 8:00-12:00 - Repository architecture, C engine and baseline schedulers
- **Reviews:** Part IV (Atharva Sivaraman)
- **Indicative effort:** about 28 hours

### 4. Atharva Sivaraman (24BEL0082)

- **Email:** atharva.sivaraman2024@vitstudent.ac.in
- **Primary role:** Evaluation, statistics, reproducibility and CI
- **Authored:** Part IV, pages 23-29 (7 pages) - Sections 21-25
- **Focus:** Revision priorities, evaluation plan, synthesis, extended review methodology, evidence grading and comparative evidence synthesis
- **Owns:** `benchmark_equal_work.py, compare_all_policies.c, compare_policies.c, results/equal_work_benchmark.json, .github/workflows/ci.yml`
- **References:** [16]-[20]
- **Presents:** 12:00-16:00 - Evaluation design, statistics and the work-normalised results
- **Reviews:** Part V (Yash Jain)
- **Indicative effort:** about 28 hours

### 5. Yash Jain (24BEL0035)

- **Email:** yash.jain2024a@vitstudent.ac.in
- **Primary role:** Documentation, dashboard and document editor
- **Authored:** Part V, pages 30-35 (6 pages) - Sections 26-29; Appendices A and B
- **Focus:** Remediation and re-measurement, statistical protocol, team governance, limitations and ethics, artefact manifest and glossary
- **Owns:** `README.md, TEAM.md, CONTRIBUTION.md, CHANGELOG.md, LICENSE, docs/, app.py`
- **References:** [21]-[25]
- **Presents:** 16:00-20:00 - Remediation, claim boundaries, limitations and conclusion
- **Reviews:** Part I (Aditya Rajeshwar Karn)
- **Indicative effort:** about 26 hours

## 9. Declaration

We certify that the work reported in the accompanying literature review and repository was carried out by the team members named above, that each member made a substantial contribution to the parts assigned to them, and that the division recorded here accurately reflects the way the work was shared. All five members have read and approved the final manuscript, the corrected benchmark results and the released code. Simulated energy figures are described as simulated throughout, and no measured hardware saving is claimed.

| Name | Registration No. | Signature | Date |
|---|---|---|---|
| Aditya Rajeshwar Karn | 24BEL0087 | | |
| Yuvraj Singh | 24BEL0057 | | |
| Aditya Singh | 24BEL0008 | | |
| Atharva Sivaraman | 24BEL0082 | | |
| Yash Jain | 24BEL0035 | | |

> **Note:** This allocation is a working record. Each member should confirm their row and sign before submission. If the actual division differed, edit this file and the matrix in Section 28.2 of the review so both records agree.

---

Printable and signed versions: `Division_of_Work.pdf` and `Division_of_Work.docx` (workspace root).
