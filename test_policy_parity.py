import os
import subprocess
import sys

import numpy as np
from stable_baselines3 import PPO

MODEL_PATH = sys.argv[1] if len(sys.argv) > 1 else "ppo_edge_scheduler.zip"
C_PROGRAM = os.path.join(".", "test_inference")
N = 1000

model = PPO.load(MODEL_PATH, device="cpu")
rng = np.random.default_rng(42)

observations = rng.uniform(
    0.0, 1.0, size=(N, 3)
).astype(np.float32)

python_actions, _ = model.predict(
    observations,
    deterministic=True
)
python_actions = np.asarray(python_actions).reshape(-1)

input_text = "".join(
    f"{obs[0]:.9g} {obs[1]:.9g} {obs[2]:.9g}\n"
    for obs in observations
)

result = subprocess.run(
    [C_PROGRAM, "--batch"],
    input=input_text,
    text=True,
    capture_output=True,
    check=True,
)

c_actions = np.fromstring(result.stdout, sep="\n", dtype=int)

if len(c_actions) != N:
    raise RuntimeError(
        f"Expected {N} C actions, received {len(c_actions)}. "
        f"stderr: {result.stderr}"
    )

mismatches = np.flatnonzero(c_actions != python_actions)

print(f"Observations tested: {N}")
print(f"Matching actions: {N - len(mismatches)}")
print(f"Mismatches: {len(mismatches)}")
print(f"Agreement: {(N - len(mismatches)) / N * 100:.2f}%")

if len(mismatches):
    print("\nFirst 10 mismatches:")
    for i in mismatches[:10]:
        print(
            f"obs={observations[i].tolist()}, "
            f"Python={python_actions[i]}, C={c_actions[i]}"
        )
    sys.exit(1)
else:
    print("PASS: Python and C agree on all tested observations.")
