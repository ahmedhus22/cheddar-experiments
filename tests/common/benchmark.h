#pragma once

#include <algorithm>
#include <chrono>
#include <cmath>
#include <cstdlib>
#include <functional>
#include <iomanip>
#include <iostream>
#include <numeric>
#include <string>
#include <utility>
#include <vector>

#include <cuda_runtime.h>
#include <nvtx3/nvToolsExt.h>


// ============================================================================
// Timing
// ============================================================================

using Clock = std::chrono::steady_clock;


struct TimingStats {
  std::vector<double> samples;

  void add(double ms) {
    samples.push_back(ms);
  }

  bool empty() const {
    return samples.empty();
  }

  std::size_t size() const {
    return samples.size();
  }

  double median() const {
    if (samples.empty()) {
      return 0.0;
    }

    auto x = samples;
    std::sort(x.begin(), x.end());

    if (x.size() % 2 == 0) {
      return (x[x.size() / 2 - 1] +
              x[x.size() / 2]) /
             2.0;
    }

    return x[x.size() / 2];
  }

  double min() const {
    if (samples.empty()) {
      return 0.0;
    }

    return *std::min_element(
        samples.begin(),
        samples.end());
  }

  double max() const {
    if (samples.empty()) {
      return 0.0;
    }

    return *std::max_element(
        samples.begin(),
        samples.end());
  }

  double mean() const {
    if (samples.empty()) {
      return 0.0;
    }

    return std::accumulate(
               samples.begin(),
               samples.end(),
               0.0) /
           samples.size();
  }

  double stddev() const {
    if (samples.empty()) {
      return 0.0;
    }

    const double m = mean();

    double sum = 0.0;

    for (double x : samples) {
      const double d = x - m;
      sum += d * d;
    }

    // Population standard deviation.
    return std::sqrt(sum / samples.size());
  }
};


// ============================================================================
// CUDA / Timing Helpers
// ============================================================================

inline double elapsed_ms(
    Clock::time_point start,
    Clock::time_point end) {

  return std::chrono::duration<double, std::milli>(
      end - start).count();
}


inline void sync_cuda() {
  cudaError_t err = cudaDeviceSynchronize();

  if (err != cudaSuccess) {
    std::cerr
        << "cudaDeviceSynchronize failed: "
        << cudaGetErrorString(err)
        << "\n";

    std::abort();
  }
}


// ============================================================================
// Benchmark Configuration
// ============================================================================

struct BenchmarkConfig {
  int warmups = 1;
  int iterations = 3;
};


// ============================================================================
// Configuration / Setup
// ============================================================================
//
// Setup phases are independent operations:
//
//   Context Generation
//   Key Generation
//   Evaluation Key Generation
//   Configuration
//
// Each phase can have its own callable and TimingStats.
//

struct SetupBenchmark {

  std::function<void()> context_generation;

  std::function<void()> key_generation;

  std::function<void()> eval_key_generation;

  std::function<void()> configuration;

  TimingStats context_generation_stats;

  TimingStats key_generation_stats;

  TimingStats eval_key_generation_stats;

  TimingStats configuration_stats;
};


// ============================================================================
// Inference Timing
// ============================================================================
//
// One inference consists of:
//
//   Encryption
//       ↓
//   Plaintext Preprocessing
//       ↓
//   Encrypted Computation
//       ↓
//   Decryption
//
// The four phase timings are returned from ONE inference iteration.
//

struct InferenceTiming {

  double encryption_ms = 0.0;

  double preprocessing_ms = 0.0;

  double evaluation_ms = 0.0;

  double decryption_ms = 0.0;

  double online_total_ms() const {
    return encryption_ms +
           preprocessing_ms +
           evaluation_ms +
           decryption_ms;
  }
};


// ============================================================================
// Inference Benchmark
// ============================================================================
//
// The model-specific code provides one callable:
//
//   InferenceTiming inference();
//
// The callable owns all model-specific state and executes the complete
// inference in the correct order.
//

struct InferenceBenchmark {

  std::function<InferenceTiming()> inference;

  TimingStats encryption_stats;

  TimingStats preprocessing_stats;

  TimingStats evaluation_stats;

  TimingStats decryption_stats;

  TimingStats online_total_stats;
};


// ============================================================================
// Complete Benchmark Specification
// ============================================================================
//
// Separates the benchmark into:
//
//   1. Configuration / Setup
//   2. Inference
//

struct BenchmarkSpecification {

  SetupBenchmark setup;

  InferenceBenchmark inference;
};


// ============================================================================
// Timed Phase
// ============================================================================
//
// Used inside one inference iteration.
//
// CUDA synchronization is performed both before and after the operation:
//
//   sync
//   start
//   operation
//   sync
//   end
//
// Therefore asynchronous CUDA work launched by the operation is included.
//

inline double time_phase(
    const char* name,
    const std::function<void()>& function) {

  nvtxRangePushA(name);

  sync_cuda();

  const auto start = Clock::now();

  function();

  sync_cuda();

  const auto end = Clock::now();

  nvtxRangePop();

  return elapsed_ms(start, end);
}


// ============================================================================
// Timed Setup Phase
// ============================================================================
//
// Setup operations use the same timing semantics as inference phases.
//
// This helper is intentionally separate from time_phase() so that the
// benchmark code clearly distinguishes setup from inference.
//

inline double time_setup_phase(
    const char* name,
    const std::function<void()>& function) {

  nvtxRangePushA(name);

  sync_cuda();

  const auto start = Clock::now();

  function();

  sync_cuda();

  const auto end = Clock::now();

  nvtxRangePop();

  return elapsed_ms(start, end);
}


// ============================================================================
// Run One Setup Phase
// ============================================================================

inline void run_setup_phase(
    const char* name,
    const std::function<void()>& function,
    TimingStats& stats,
    const BenchmarkConfig& config) {

  if (!function) {
    return;
  }

  // --------------------------------------------------------------------------
  // Warmup
  // --------------------------------------------------------------------------

  for (int i = 0; i < config.warmups; ++i) {

    const double warmup_ms =
        time_setup_phase(
            name,
            function);

    std::cerr
        << name
        << " warmup "
        << (i + 1)
        << ": "
        << warmup_ms
        << " ms\n";
  }


  // --------------------------------------------------------------------------
  // Measured repetitions
  // --------------------------------------------------------------------------

  for (int i = 0; i < config.iterations; ++i) {

    const double ms =
        time_setup_phase(
            name,
            function);

    stats.add(ms);

    std::cerr
        << name
        << " iteration "
        << (i + 1)
        << ": "
        << ms
        << " ms\n";
  }
}


// ============================================================================
// Run Configuration / Setup
// ============================================================================
//
// Execution order:
//
//   Context Generation
//   Key Generation
//   Evaluation Key Generation
//   Configuration
//
// Each setup phase is independently warmed up and measured.
//

inline void run_setup(
    SetupBenchmark& setup,
    const BenchmarkConfig& config) {

  std::cerr
      << "\n"
      << "========================================\n"
      << "Configuration / Setup\n"
      << "========================================\n";


  run_setup_phase(
      "Context Generation",
      setup.context_generation,
      setup.context_generation_stats,
      config);


  run_setup_phase(
      "Key Generation",
      setup.key_generation,
      setup.key_generation_stats,
      config);


  run_setup_phase(
      "Evaluation Key Generation",
      setup.eval_key_generation,
      setup.eval_key_generation_stats,
      config);


  run_setup_phase(
      "Configuration",
      setup.configuration,
      setup.configuration_stats,
      config);
}


// ============================================================================
// Run One Inference
// ============================================================================

inline InferenceTiming run_inference(
    const InferenceBenchmark& benchmark) {

  if (!benchmark.inference) {
    std::cerr
        << "Inference function is not configured.\n";

    std::abort();
  }

  return benchmark.inference();
}


// ============================================================================
// Run Inference Benchmark
// ============================================================================
//
// Execution order:
//
//   Warmup 1
//       Encryption
//       Preprocessing
//       Evaluation
//       Decryption
//
//   Measurement 1
//       Encryption
//       Preprocessing
//       Evaluation
//       Decryption
//
//   Measurement 2
//       Encryption
//       Preprocessing
//       Evaluation
//       Decryption
//
//   ...
//
// Only measured iterations are added to TimingStats.
//

inline void run_inference_benchmark(
    InferenceBenchmark& benchmark,
    const BenchmarkConfig& config) {

  if (!benchmark.inference) {
    std::cerr
        << "Inference function is not configured.\n";

    std::abort();
  }


  // --------------------------------------------------------------------------
  // Warmup
  // --------------------------------------------------------------------------

  std::cerr
      << "\n"
      << "========================================\n"
      << "Inference Warmup\n"
      << "========================================\n";

  for (int i = 0; i < config.warmups; ++i) {

    const InferenceTiming timing =
        run_inference(benchmark);

    std::cerr
        << "Warmup iteration "
        << (i + 1)
        << " online total: "
        << timing.online_total_ms()
        << " ms\n";
  }


  // --------------------------------------------------------------------------
  // Measured repetitions
  // --------------------------------------------------------------------------

  std::cerr
      << "\n"
      << "========================================\n"
      << "Inference\n"
      << "========================================\n";

  for (int i = 0; i < config.iterations; ++i) {

    const InferenceTiming timing =
        run_inference(benchmark);

    const double online_ms =
        timing.online_total_ms();


    benchmark.encryption_stats.add(
        timing.encryption_ms);

    benchmark.preprocessing_stats.add(
        timing.preprocessing_ms);

    benchmark.evaluation_stats.add(
        timing.evaluation_ms);

    benchmark.decryption_stats.add(
        timing.decryption_ms);

    benchmark.online_total_stats.add(
        online_ms);


    std::cerr
        << "Iteration "
        << (i + 1)
        << " online total: "
        << online_ms
        << " ms\n";
  }
}


// ============================================================================
// Statistics Reporting
// ============================================================================

inline void print_stats(
    const char* name,
    const TimingStats& stats) {

  std::cout
      << std::fixed
      << std::setprecision(3);

  std::cout
      << "\n"
      << name
      << "\n";

  std::cout
      << "  samples: ";

  for (double x : stats.samples) {
    std::cout
        << x
        << " ms ";
  }

  std::cout
      << "\n";

  std::cout
      << "  median: "
      << stats.median()
      << " ms\n";

  std::cout
      << "  min:    "
      << stats.min()
      << " ms\n";

  std::cout
      << "  max:    "
      << stats.max()
      << " ms\n";

  std::cout
      << "  mean:   "
      << stats.mean()
      << " ms\n";

  std::cout
      << "  stddev: "
      << stats.stddev()
      << " ms\n";
}


// ============================================================================
// Setup Report
// ============================================================================

inline void report_setup(
    const SetupBenchmark& setup) {

  std::cout
      << "\n"
      << "========================================\n"
      << "Configuration / Setup Results\n"
      << "========================================\n";

  if (!setup.context_generation_stats.empty()) {
    print_stats(
        "Context Generation",
        setup.context_generation_stats);
  }

  if (!setup.key_generation_stats.empty()) {
    print_stats(
        "Key Generation",
        setup.key_generation_stats);
  }

  if (!setup.eval_key_generation_stats.empty()) {
    print_stats(
        "Evaluation Key Generation",
        setup.eval_key_generation_stats);
  }

  if (!setup.configuration_stats.empty()) {
    print_stats(
        "Configuration",
        setup.configuration_stats);
  }
}


// ============================================================================
// Inference Report
// ============================================================================

inline void report_inference(
    const InferenceBenchmark& inference) {

  std::cout
      << "\n"
      << "========================================\n"
      << "Inference Results\n"
      << "========================================\n";

  if (!inference.encryption_stats.empty()) {
    print_stats(
        "Encryption",
        inference.encryption_stats);
  }

  if (!inference.preprocessing_stats.empty()) {
    print_stats(
        "Plaintext Preprocessing",
        inference.preprocessing_stats);
  }

  if (!inference.evaluation_stats.empty()) {
    print_stats(
        "Encrypted Computation",
        inference.evaluation_stats);
  }

  if (!inference.decryption_stats.empty()) {
    print_stats(
        "Decryption",
        inference.decryption_stats);
  }

  if (!inference.online_total_stats.empty()) {
    print_stats(
        "Online Total",
        inference.online_total_stats);
  }
}


// ============================================================================
// Complete Benchmark Report
// ============================================================================

inline void report_benchmark(
    const BenchmarkSpecification& benchmark) {

  report_setup(benchmark.setup);

  report_inference(benchmark.inference);
}

