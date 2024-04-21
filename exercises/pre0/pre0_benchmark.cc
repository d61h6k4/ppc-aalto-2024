
#include "benchmark/benchmark.h"
#include "exercises/pre0/pre0.h"
#include <algorithm>
#include <random>

std::vector<float> generate_data(int ny, int nx) {
    std::vector<float> res;
    res.resize(ny * nx * 3);

    static std::mt19937 rng;
    std::generate_n(res.begin(), ny * nx * 3, rng);

    return res;
}


static void BM_small_bench_calculate(benchmark::State& state) {
    auto data = generate_data(100, 100);
    for (auto _ : state) {
        benchmark::DoNotOptimize(calculate(100, 100, data.data(), 10, 10, 60, 60));
    }
}

BENCHMARK(BM_small_bench_calculate);


static void BM_big_bench_calculate(benchmark::State& state) {
    auto data = generate_data(1000, 1000);
    for (auto _ : state) {
        benchmark::DoNotOptimize(calculate(1000, 1000, data.data(), 10, 10, 510, 510));
    }
}

BENCHMARK(BM_big_bench_calculate);
