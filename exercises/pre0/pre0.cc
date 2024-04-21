
#include "exercises/pre0/pre0.h"

Result calculate(int ny, int nx, const float *data, int y0, int x0, int y1,
                 int x1) {
  std::array<float, 3> avg = {0.0f, 0.0f, 0.0f};
  std::array<float, 3> sum = {0.0f, 0.0f, 0.0f};

  for (auto y = y0; y < y1; ++y) {
    for (auto x = x0; x < x1; ++x) {
      for (auto c = 0; c < 3; ++c) {
          float q = data[c + 3 * x + 3 * nx * y] - avg[c];
          float tmp_sum = sum[c] + 1.0f;
          float r = q / tmp_sum;

          avg[c] += r;
          sum[c] = tmp_sum;
      }
    }
  }

  return Result{.avg = avg};
}
