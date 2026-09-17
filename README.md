# CHEDDAR Experiments

## Build Instructions
There are submodules in this repository.
`git clone --recurse-submodules https://github.com/ahmedhus22/cheddar-experiments.git`
Or initialize submodules after cloning: `git submodule update --init --recursive`
```
cmake -S . -B build \
    -DCMAKE_CUDA_COMPILER=/usr/local/cuda/bin/nvcc 

cmake --build build
```
### Run Tests
Run the tests directly. For example, to run the alexnet-tiny_tests:
```
./build/tests/alexnet-tiny_tests
```

## Generate the CHEDDAR files
To generate the cheddar files, use my patched [HEIR CHEDDAR backend](https://github.com/ahmedhus22/heir/tree/cheddar-backend) fork. Note that the fork is experimental and unstable but it is currently working for the tested samples.

### Cheddar Conversion Passes
```
bazel run //tools:heir-opt -- \
--linalg-canonicalizations \
--mlir-to-ckks \
--scheme-to-cheddar='entry-function=sample_func' \
$PWD/sample.mlir > sample_cheddar.mlir
```

### Emit the CHEDDAR C++ code 
```
bazel run //tools:heir-translate -- --emit-cheddar $PWD/sample.mlir > sample.cpp
```

### EMITC Backend
```
bazel run //tools:heir-opt --  --ext-const-threshold=1   '--annotate-module=backend=cheddar scheme=ckks'   --linalg-canonicalizations   '--torch-linalg-to-ckks=min-slot-count=16384 greedy-level-budget=10'   '--scheme-to-cheddar'   --cheddar-to-emitc   $PWD/sample.mlir > $PWD/samples/sample_cheddar.mlir
```
```
bazel run //tools:heir-translate -- --mlir-to-cpp $PWD/sample_cheddar.mlir > $PWD/sample.cpp
```

## Required Setup
- CUDA Version: Tested on 12.6 (Latest version 13.3 doesn’t work)
- Clang Version: 20 (LLVM-21 causes some issues)
- libtommath: Cheddar optionally requires libtommath, Instead of a system-wide installation, It is built separately
and linked to Cheddar. So, Cheddar’s CMake file was modified.

## Known Issues
- Setting a log default scale is not supported. Ex: #ckks.scheme_param< logDefaultScale = 45>, this causes issues in the verifier.
- In general avoid giving #ckks.scheme_param, CHEDDAR backend will generate a supported configuration automatically.