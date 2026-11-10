import argparse
import numpy as np

from assignment.assignment import LayoutAssignment
from backends import HEIR
from backends.heir.mlir_interpreter import run_mlir_interpreter
from frontends.tensor import TensorTerm
from lower.lower import Lower

from util.checker import check_results

def vecsum():
    # Create tensor operations
    a = TensorTerm.Tensor("a", [1024], True)
    b = TensorTerm.Tensor("b", [1024], True)
    c = a + b  
    return c

# Run layout assignment, lower to circuit IR, execute with toy backend
args = argparse.Namespace(n=1024, rolls=True, backend="HEIR", fn="vecsum", benchmark="main")
c = vecsum()
kernel = LayoutAssignment(c, args).run()
circuit_ir = Lower(kernel).run()
inputs = {"a": np.random.randn(1024), "b": np.random.randn(1024)}
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