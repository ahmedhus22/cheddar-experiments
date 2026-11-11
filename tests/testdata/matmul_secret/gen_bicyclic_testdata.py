import numpy as np
from pathlib import Path

np.random.seed(42)
inputs = {"a": np.random.standard_normal((16, 17)).astype(np.float32), "b": np.random.standard_normal((17, 19)).astype(np.float32)}
c = inputs["a"] @ inputs["b"]

save_dir = Path(__file__).parent / "bicyclic"
save_dir.mkdir(parents=True, exist_ok=True)
# np.save(save_dir / "result", c.flatten())
# np.save(save_dir / "a", inputs["a"].flatten())
# np.save(save_dir / "b", inputs["b"].flatten())
inputs["a"].tofile(save_dir / "a.bin")
inputs["b"].tofile(save_dir / "b.bin")
c.tofile(save_dir / "result.bin")

#print first few values of a, b, and c for verification
print("a:", inputs["a"].flatten()[:10])
print("b:", inputs["b"].flatten()[:10])
print("c:", c.flatten()[:10])