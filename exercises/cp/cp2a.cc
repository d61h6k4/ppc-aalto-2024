
#include "exercises/cp/cp2a.h"
#include <cmath>
#include <cstddef>
#include <functional>
#include <numeric>
#include <span>

namespace ppc {

float mean(std::span<const float, std::dynamic_extent> v) {
  double sum =
      std::transform_reduce(v.begin(), v.end(), 0.0, std::plus{},
                            [](float x) { return static_cast<double>(x); });
  auto n = std::distance(v.begin(), v.end());

  return static_cast<float>(sum / static_cast<double>(n));
}

float l2_norm(std::span<const float, std::dynamic_extent> v, float v_mean) {
  float sum = std::transform_reduce(
      v.begin(), v.end(), 0.0f, std::plus{},
      [v_mean](float x) { return std::pow(x - v_mean, 2.0f); });
  return std::sqrt(sum);
}

void corelate(int ny, int nx, const float *data, float *result) {
  std::vector<float> norm_data(ny * nx);

  for (auto i = 0; i < ny; ++i) {
    auto x = std::span(data + i * nx, static_cast<size_t>(nx));
    float x_mean = mean(x);
    float x_norm = l2_norm(x, x_mean);
    for (auto j = 0; j < nx; ++j) {
      norm_data[j + i * nx] = (data[j + i * nx] - x_mean) / x_norm;
    }
  }

  for (auto i = 0; i < ny; ++i) {
    auto x = std::span(norm_data.begin() + i * nx, static_cast<size_t>(nx));

    for (auto j = i; j < ny; ++j) {

      auto y = std::span(norm_data.begin() + j * nx, static_cast<size_t>(nx));

      result[i + j * ny] =
          std::inner_product(x.begin(), x.end(), y.begin(), 0.0f);
    }
  }
}
} // namespace ppc
