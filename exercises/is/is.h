#pragma once

#include <array>


namespace ppc {

struct Result {
  int y0;
  int x0;
  int y1;
  int x1;
  std::array<float, 3> outer;
  std::array<float, 3> inner;
};

Result Segment(int ny, int nx, const float *data);
} // namespace ppc
