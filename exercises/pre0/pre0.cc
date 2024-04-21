
#include "exercises/pre0/pre0.h"

Result calculate(int ny, int nx, const float *data, int y0, int x0, int y1,
                 int x1) {
  std::array<float, 3> avg = {0.0f, 0.0f, 0.0f};
  std::array<double, 3> avg_d = {0.0, 0.0, 0.0};
  std::array<int, 3> num = {0, 0, 0};

  for (auto c = 0; c < 3; ++c) {
    for (auto y = y0; y < y1; ++y) {
      for (auto x = x0; x < x1; ++x) {
        avg_d[c] += static_cast<double>(data[c + 3 * x + 3 * nx * y]);
        num[c] += 1;
      }
    }
  }
  for (auto c = 0; c < 3; ++c) {
    avg[c] = static_cast<float>(avg_d[c] / static_cast<double>(num[c]));
  }

  return Result{.avg = avg};
}
