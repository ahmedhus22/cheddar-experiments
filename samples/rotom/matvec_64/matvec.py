import argparse
import numpy as np

from assignment.assignment import LayoutAssignment
from backends import HEIR
from backends.heir.mlir_interpreter import run_mlir_interpreter
from frontends.tensor import TensorTerm
from lower.lower import Lower

from util.checker import check_results

def matvec_64():
    # Create tensor operations
    a = TensorTerm.Tensor("a", [64, 64], True)  # 64x64 ciphertext matrix
    b = TensorTerm.Tensor("b", [64], False)  # 64-element plaintext vector
    c = a @ b  # Matrix-vector multiplication
    return c

# Run layout assignment, lower to circuit IR, execute with toy backend
args = argparse.Namespace(n=4096, rolls=True, backend="HEIR", fn="matvec_64", benchmark="main")
c = matvec_64()
kernel = LayoutAssignment(c, args).run()
circuit_ir = Lower(kernel).run()
inputs = {"a": np.random.randn(64, 64), "b": np.random.randn(64)}
heir_backend = HEIR(circuit_ir, inputs, args)

heir_backend.run()
# Run MLIR interpreter to get results
mlir_file = f"heir/{args.fn}/{args.fn}.mlir"
mlir_results = run_mlir_interpreter(mlir_file, args.n)
# Check MLIR results against tensor_ir.eval()
tensor_ir = c
runtime = 0
check_results(tensor_ir, inputs, kernel, mlir_results, runtime, args)
heir_backend.serialize_results(mlir_results)