

#include "benchmark/benchmark.h"
#include "exercises/cp/cp2a.h"
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

static void BM_bench_correlate(benchmark::State &state) {
  auto data = generate_data(state.range(0), state.range(1));
  std::vector<float> result;
  result.resize(state.range(0) * state.range(0));

  for (auto _ : state) {
    ppc::corelate(state.range(0), state.range(1), data.data(), result.data());
  }
}

BENCHMARK(BM_bench_correlate)->Args({1000, 1000})->Args({4000, 1000});

} // namespace
