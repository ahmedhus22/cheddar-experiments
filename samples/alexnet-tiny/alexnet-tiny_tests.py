from pathlib import Path
import numpy as np

testdata_dir = Path(__file__).parents[2] / "tests" / "testdata"

torch_out = np.fromfile(
    testdata_dir / "torch_output.bin",
    dtype=np.float64
)

cheddar_out = np.fromfile(
    testdata_dir / "cheddar_output.bin",
    dtype=np.float64
)

assert torch_out.shape == cheddar_out.shape

diff = np.abs(torch_out - cheddar_out)

print("Torch:", torch_out)
print("CHEDDAR:", cheddar_out)
print("Abs error:", diff)
print("Max error:", diff.max())
print("Mean error:", diff.mean())
print("All close:", np.allclose(torch_out, cheddar_out,
                                atol=1e-6, rtol=1e-6))