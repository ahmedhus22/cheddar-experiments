#pragma once

#include <algorithm>
#include <chrono>
#include <cmath>
#include <functional>
#include <iomanip>
#include <iostream>
#include <numeric>
#include <string>
#include <tuple>
#include <utility>
#include <vector>

#include <cuda_runtime.h>
#include <nvtx3/nvToolsExt.h>

// ============================================================================
// Configuration
// ============================================================================

struct BenchmarkConfig {
  int warmups = 1;
  int iterations = 3;
};

// ============================================================================
// Timing Statistics
// ============================================================================

using Clock = std::chrono::steady_clock;

struct TimingStats {
  std::vector<double> samples;

  void add(double ms) {
    samples.push_back(ms);
  }

  double median() const {
    if (samples.empty()) return 0.0;

    auto x = samples;
    std::sort(x.begin(), x.end());

    const size_t n = x.size();

    return n % 2 == 0
        ? (x[n / 2 - 1] + x[n / 2]) / 2.0
        : x[n / 2];
  }

  double min() const {
    return samples.empty() ? 0.0 :
        *std::min_element(samples.begin(), samples.end());
  }

  double max() const {
    return samples.empty() ? 0.0 :
        *std::max_element(samples.begin(), samples.end());
  }

  double mean() const {
    return samples.empty() ? 0.0 :
        std::accumulate(samples.begin(), samples.end(), 0.0)
        / samples.size();
  }

  double stddev() const {
    if (samples.empty()) return 0.0;

    const double m = mean();
    double sum = 0.0;

    for (double x : samples) {
      const double d = x - m;
      sum += d * d;
    }

    return std::sqrt(sum / samples.size());
  }
};

// ============================================================================
// Benchmark Phase
// ============================================================================

struct BenchmarkPhase {
  std::string name;
  std::function<void()> function;
  TimingStats stats;
};

// ============================================================================
// CUDA Synchronization
// ============================================================================

inline void sync_cuda() {
  cudaError_t err = cudaDeviceSynchronize();

  if (err != cudaSuccess) {
    std::cerr << "CUDA synchronization failed: "
              << cudaGetErrorString(err) << '\n';
    std::abort();
  }
}

// ============================================================================
// Timing
// ============================================================================

inline double time_phase(const BenchmarkPhase& phase) {
  nvtxRangePushA(phase.name.c_str());

  sync_cuda();
  auto start = Clock::now();

  phase.function();

  sync_cuda();
  auto end = Clock::now();

  nvtxRangePop();

  return std::chrono::duration<double, std::milli>(
      end - start).count();
}

// ============================================================================
// Run Benchmark Stage
// ============================================================================

inline void run_benchmark_stage(
    const char* stage_name,
    std::vector<BenchmarkPhase>& phases,
    const BenchmarkConfig& config) {

  auto run_iteration = [&](bool record, int iteration) {

    double total_ms = 0.0;

    for (auto& phase : phases) {
      if (!phase.function) continue;

      const double ms = time_phase(phase);

      total_ms += ms;

      if (record) {
        phase.stats.add(ms);
      }
    }

    std::cerr << stage_name << " iteration "
              << iteration << ": "
              << total_ms << " ms\n";
  };

  std::cerr << "\n========== "
            << stage_name << " Warmup ==========\n";

  for (int i = 0; i < config.warmups; ++i) {
    run_iteration(false, i + 1);
  }

  std::cerr << "\n========== "
            << stage_name << " Measurements ==========\n";

  for (int i = 0; i < config.iterations; ++i) {
    run_iteration(true, i + 1);
  }
}

// ============================================================================
// Reporting
// ============================================================================

inline void print_stats(
    const std::string& name,
    const TimingStats& stats) {

  if (stats.samples.empty()) return;

  std::cout << std::fixed << std::setprecision(3);

  std::cout << "\n" << name << '\n';

  std::cout << "  samples: ";
  for (double x : stats.samples) {
    std::cout << x << " ms ";
  }

  std::cout << "\n";
  std::cout << "  median: " << stats.median() << " ms\n";
  std::cout << "  min:    " << stats.min() << " ms\n";
  std::cout << "  max:    " << stats.max() << " ms\n";
  std::cout << "  mean:   " << stats.mean() << " ms\n";
  std::cout << "  stddev: " << stats.stddev() << " ms\n";
}

inline void report_stage(
    const char* stage_name,
    const std::vector<BenchmarkPhase>& phases) {

  std::cout << "\n========== "
            << stage_name << " Results ==========\n";

  for (const auto& phase : phases) {
    if (phase.function && !phase.stats.samples.empty()) {
      print_stats(phase.name, phase.stats);
    }
  }
}

// ============================================================================
// Complete Benchmark
// ============================================================================

struct Benchmark {
  std::vector<BenchmarkPhase> setup;
  std::vector<BenchmarkPhase> inference;

  void run_setup(const BenchmarkConfig& config) {
    run_benchmark_stage("Setup", setup, config);
  }

  void run_inference(const BenchmarkConfig& config) {
    run_benchmark_stage("Inference", inference, config);
  }

  void report() const {
    report_stage("Setup", setup);
    report_stage("Inference", inference);
  }
};

// ============================================================================
// Convenience Factory
// ============================================================================

template <typename F>
BenchmarkPhase phase(const char* name, F&& function) {
  return {
      name,
      std::function<void()>(std::forward<F>(function)),
      {}
  };
}

inline BenchmarkPhase phase(const char* name) {
  return {name, {}, {}};
}
