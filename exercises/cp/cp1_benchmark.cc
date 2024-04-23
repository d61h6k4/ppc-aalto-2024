

#include "benchmark/benchmark.h"
#include "exercises/cp/cp1.h"
#include <algorithm>
#include <random>

namespace {

std::vector<float> generate_data(int ny, int nx) {
  std::vector<float> res;
  res.resize(ny * nx * 3);

  static std::mt19937 rng;
  std::generate_n(res.begin(), ny * nx * 3, rng);

  return res;
}

static void BM_bench_correlate(benchmark::State &state) {
  auto data = generate_data(state.range(0), state.range(0));
  std::vector<float> result;
  result.resize(state.range(0) * state.range(0));

  for (auto _ : state) {
    ppc::corelate(state.range(0), state.range(0), data.data(), result.data());
  }
}

BENCHMARK(BM_bench_correlate)->RangeMultiplier(2)->Range(8, 2 << 10);

} // namespace