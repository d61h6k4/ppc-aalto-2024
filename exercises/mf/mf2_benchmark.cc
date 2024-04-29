

#include "benchmark/benchmark.h"
#include "exercises/mf/mf2.h"
#include <algorithm>
#include <random>
#include <vector>

namespace {

std::vector<float> generate_data(int ny, int nx) {
  std::vector<float> res;
  res.resize(ny * nx);

  static std::mt19937 rng;
  std::generate_n(res.begin(), ny * nx, rng);

  return res;
}

static void BM_bench_small_kernel_mf(benchmark::State &state) {
  auto data = generate_data(state.range(0), state.range(0));
  std::vector<float> result;
  result.resize(state.range(0) * state.range(0));

  for (auto _ : state) {
    ppc::mf(state.range(0), state.range(0), 10, 10, data.data(), result.data());
  }
}

BENCHMARK(BM_bench_small_kernel_mf)
    ->Args({100, 100})
    ->Args({500, 500})
    ->Args({1000, 1000})
    ->Args({1500, 1500});

static void BM_bench_big_kernel_mf(benchmark::State &state) {
  auto data = generate_data(state.range(0), state.range(0));
  std::vector<float> result;
  result.resize(state.range(0) * state.range(0));

  for (auto _ : state) {
    ppc::mf(state.range(0), state.range(0), 50, 50, data.data(), result.data());
  }
}

BENCHMARK(BM_bench_big_kernel_mf)->RangeMultiplier(2)->Range(128, 256);

} // namespace
