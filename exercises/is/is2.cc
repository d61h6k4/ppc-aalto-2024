
#include "exercises/is/is.h"
#include <iostream>
#include <limits>

namespace ppc {

std::array<float, 3> Mean(const float *data, int ly, int lx, int ry, int rx,
                          int ny, int nx) {
  std::array<float, 3> nom;
  std::array<float, 3> denom;

  for (auto y = ly; y < ry; ++y) {
    for (auto x = lx; x < rx; ++x) {
      for (auto c = 0; c < 3; ++c) {
        nom[c] += data[c + 3 * x + 3 * nx * y];
        denom[c] += 1.0f;
      }
    }
  }

  for (auto c = 0; c < 3; ++c) {
    nom[c] /= denom[c];
  }
  return nom;
}

std::array<float, 3> OuterMean(const float *data, int ly, int lx, int ry,
                               int rx, int ny, int nx) {
  std::array<float, 3> nom;
  std::array<float, 3> denom;

  for (auto y = 0; y < ny; ++y) {
    for (auto x = 0; x < nx; ++x) {
      if ((y < ly || ry <= y) && (x < lx || rx <= x)) {
        for (auto c = 0; c < 3; ++c) {
          nom[c] += data[c + 3 * x + 3 * nx * y];
          denom[c] += 1.0f;
        }
      }
    }
  }

  for (auto c = 0; c < 3; ++c) {
    nom[c] /= denom[c];
  }
  return nom;
}

float Loss(const Result &res, const float *data, int ny, int nx) {
  float err = 0.0f;

  for (auto y = 0; y < ny; ++y) {
    for (auto x = 0; x < nx; ++x) {
      if (res.y0 <= y && y < res.y1 && res.x0 <= x && x < res.x1) {
        float c_err = 0.0f;
        for (auto c = 0; c < 3; ++c) {
          c_err += res.inner[c] - data[c + 3 * x + 3 * nx * y];
        }
        err += c_err * c_err;
      } else {
        float c_err = 0.0f;
        for (auto c = 0; c < 3; ++c) {
          c_err += res.outer[c] - data[c + 3 * x + 3 * nx * y];
        }
        err += c_err * c_err;
      }
    }
  }
  return err;
}

Result Segment(int ny, int nx, const float *data) {
  Result res = {.y0 = 0,
                .x0 = 0,
                .y1 = ny,
                .x1 = nx,
                .inner = Mean(data, 0, 0, ny, nx, ny, nx),
                .outer = OuterMean(data, 0, 0, ny, nx, ny, nx)};
  float error = Loss(res, data, ny, nx);

  for (auto sy = 1; sy <= ny; ++sy) {
    for (auto sx = 1; sx <= nx; ++sx) {
      for (auto cy = 0; cy + sy <= ny; ++cy) {
        for (auto cx = 0; cx + sx <= nx; ++cx) {
          Result t = {.y0 = cy,
                      .x0 = cx,
                      .y1 = cy + sy,
                      .x1 = cy + sx,
                      .inner = Mean(data, cy, cx, cy + sy, cx + sx, ny, nx),
                      .outer =
                          OuterMean(data, cy, cx, cy + sy, cx + sx, ny, nx)};
          if (auto l = Loss(t, data, ny, nx) < error) {
            error = l;
            res = t;
          }
        }
      }
    }
  }

  return res;
}
} // namespace ppc
