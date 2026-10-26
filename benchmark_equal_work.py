import argparse
import json
import os
import re
import subprocess
from pathlib import Path

import numpy as np

ROW = re.compile(
    r"^\s+(Performance governor|DRL C scheduler)\s+"
    r"([\d.]+)\s+([\d.]+)\s+([\d.]+)\s+(\d+)\s+([\d.]+)\s*$",
    re.MULTILINE,
)
ENERGY = re.compile(r"Cumulative Energy:\s+([\d.]+)\s+Joules")

def run_once(binary, tdp, queue, steps, cap):
    proc = subprocess.run(
        [binary, str(tdp), str(queue), str(steps), str(cap)],
        capture_output=True, text=True, check=True,
    )
    out = proc.stdout
    energies = [float(v) for v in ENERGY.findall(out)]
    rows = {
        m.group(1): {
            "served": float(m.group(2)),
            "arrived": float(m.group(3)),
            "dropped": float(m.group(4)),
            "clipped": int(m.group(5)),
            "energy_per_work": float(m.group(6)),
        }
        for m in ROW.finditer(out)
    }
    if len(energies) != 2 or len(rows) != 2:
        raise RuntimeError("Could not parse benchmark output:\n" + out)
    return {
        "perf_energy": energies[0],
        "drl_energy": energies[1],
        "perf": rows["Performance governor"],
        "drl": rows["DRL C scheduler"],
        "warnings": out.count("WARNING:"),
    }

def bootstrap_ci(values, rng, n=10000, alpha=0.05):
    values = np.asarray(values, dtype=float)
    if len(values) < 2:
        return float(values[0]), float(values[0])
    idx = rng.integers(0, len(values), size=(n, len(values)))
    means = values[idx].mean(axis=1)
    return float(np.quantile(means, alpha / 2)), float(np.quantile(means, 1 - alpha / 2))

def main():
    parser = argparse.ArgumentParser(description="Equal-work benchmark with bootstrap confidence intervals")
    parser.add_argument("--binary", default="./scheduler")
    parser.add_argument("--profiles", type=int, default=10)
    parser.add_argument("--steps", type=int, default=200)
    parser.add_argument("--seed", type=int, default=2026)
    parser.add_argument("--json", default="results/equal_work_benchmark.json")
    args = parser.parse_args()

    if not os.path.exists(args.binary):
        subprocess.run(["make"], check=True)

    rng = np.random.default_rng(args.seed)
    records = []

    for i in range(args.profiles):
        tdp = float(rng.choice([5.0, 15.0, 25.0, 45.0, 65.0]))
        queue = float(round(rng.uniform(0.05, 0.95), 3))
        cap = int(rng.choice([50, 60, 70, 80, 90, 100]))
        rec = run_once(args.binary, tdp, queue, args.steps, cap)
        rec.update({"tdp": tdp, "queue": queue, "cap": cap})
        records.append(rec)

    raw_improvement = []
    normalized_improvement = []
    served_ratio = []
    dropped_total = 0.0
    warning_profiles = 0

    for rec in records:
        p, d = rec["perf"], rec["drl"]
        if rec["perf_energy"] > 0:
            raw_improvement.append(
                100.0 * (rec["perf_energy"] - rec["drl_energy"]) / rec["perf_energy"]
            )
        if p["energy_per_work"] > 0:
            normalized_improvement.append(
                100.0 * (p["energy_per_work"] - d["energy_per_work"])
                / p["energy_per_work"]
            )
        if p["served"] > 0:
            served_ratio.append(d["served"] / p["served"])
        dropped_total += d["dropped"]
        warning_profiles += 1 if rec["warnings"] else 0

    def stats(v):
        lo, hi = bootstrap_ci(v, rng)
        return {"mean": float(np.mean(v)), "sd": float(np.std(v, ddof=1)),
                "ci95": [lo, hi], "n": len(v)}

    summary = {
        "profiles": len(records),
        "steps_per_profile": args.steps,
        "seed": args.seed,
        "raw_energy_improvement_pct": stats(raw_improvement),
        "normalized_energy_improvement_pct": stats(normalized_improvement),
        "drl_to_baseline_served_work_ratio": stats(served_ratio),
        "total_dropped_work_units": dropped_total,
        "profiles_with_backlog_clipping_warning": warning_profiles,
        "interpretation": (
            "Energy figures are simulated. Compare normalized_energy_improvement_pct "
            "against raw_energy_improvement_pct: a large gap indicates that the raw "
            "figure is an artefact of unequal served work rather than genuine efficiency."
        ),
    }

    Path(args.json).parent.mkdir(parents=True, exist_ok=True)
    Path(args.json).write_text(
        json.dumps({"summary": summary, "runs": records}, indent=2) + "\n",
        encoding="utf-8",
    )

    print(f"Profiles: {len(records)}  |  steps/profile: {args.steps}")
    print(f"Raw energy improvement (simulated):        "
          f"{summary['raw_energy_improvement_pct']['mean']:6.2f}%  "
          f"95% CI {summary['raw_energy_improvement_pct']['ci95'][0]:.2f} to "
          f"{summary['raw_energy_improvement_pct']['ci95'][1]:.2f}")
    print(f"Normalized improvement (J per served unit): "
          f"{summary['normalized_energy_improvement_pct']['mean']:6.2f}%  "
          f"95% CI {summary['normalized_energy_improvement_pct']['ci95'][0]:.2f} to "
          f"{summary['normalized_energy_improvement_pct']['ci95'][1]:.2f}")
    print(f"DRL/baseline served work ratio:            "
          f"{summary['drl_to_baseline_served_work_ratio']['mean']:6.3f}")
    print(f"Total dropped work units:                  {dropped_total:.3f}")
    print(f"Profiles with clipping warnings:           {warning_profiles}")
    print(f"Saved: {args.json}")

if __name__ == "__main__":
    main()
