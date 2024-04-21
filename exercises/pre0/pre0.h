#pragma once

#include <array>

struct Result {
    std::array<float, 3> avg;
};

Result calculate(int ny, int nx, const float* data, int y0, int x0, int y1, int x1);
