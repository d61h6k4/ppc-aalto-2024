

#include "benchmark/benchmark.h"
#include "exercises/mf/mf1.h"
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
      ppc::mf(state.range(0), state.range(0), 3, 3, data.data(), result.data());
  }
}

BENCHMARK(BM_bench_small_kernel_mf)->RangeMultiplier(2)->Range(8, 2 << 10);


static void BM_bench_big_kernel_mf(benchmark::State &state) {
  auto data = generate_data(state.range(0), state.range(0));
  std::vector<float> result;
  result.resize(state.range(0) * state.range(0));

  for (auto _ : state) {
      ppc::mf(state.range(0), state.range(0), 50, 50, data.data(), result.data());
  }
}

BENCHMARK(BM_bench_big_kernel_mf)->RangeMultiplier(2)->Range(128, 2 << 10);

} // namespace
