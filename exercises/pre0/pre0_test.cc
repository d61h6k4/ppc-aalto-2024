
#include "exercises/pre0/pre0.h"
#include "gtest/gtest.h"
#include <limits>

namespace {
TEST(Pre0Test, CheckWithConstants) {
  const int ny = 10;
  const int nx = 10;
  const int y0 = 0;
  const int x0 = 0;
  const int y1 = 10;
  const int x1 = 10;

  std::array<float, 10 * 10 * 3> img{};
  for (auto c = 0; c < 3; ++c) {
    for (auto x = x0; x < x1; ++x) {
      for (auto y = y0; y < y1; ++y) {
        img[c + 3 * x + 3 * nx * y] = 1.0f;
      }
    }
  }

  auto res = calculate(ny, nx, img.data(), y0, x0, y1, x1);

  EXPECT_EQ(res.avg[0], 1.0f);
  EXPECT_EQ(res.avg[1], 1.0f);
  EXPECT_EQ(res.avg[2], 1.0f);
}

TEST(Pre0Test, CheckChannelsDonotMix) {
  const int ny = 10;
  const int nx = 10;
  const int y0 = 0;
  const int x0 = 0;
  const int y1 = 10;
  const int x1 = 10;

  std::array<float, 10 * 10 * 3> img{};
  for (auto c = 0; c < 3; ++c) {
    for (auto x = x0; x < x1; ++x) {
      for (auto y = y0; y < y1; ++y) {
        img[c + 3 * x + 3 * nx * y] = static_cast<float>(c);
      }
    }
  }

  auto res = calculate(ny, nx, img.data(), y0, x0, y1, x1);

  EXPECT_EQ(res.avg[0], 0.0f);
  EXPECT_EQ(res.avg[1], 1.0f);
  EXPECT_EQ(res.avg[2], 2.0f);
}

TEST(Pre0Test, CheckWithBigNumbers) {
  const int ny = 10;
  const int nx = 10;
  const int y0 = 0;
  const int x0 = 0;
  const int y1 = 10;
  const int x1 = 10;

  std::array<float, 10 * 10 * 3> img{};
  for (auto c = 0; c < 3; ++c) {
    for (auto x = x0; x < x1; ++x) {
      for (auto y = y0; y < y1; ++y) {
        img[c + 3 * x + 3 * nx * y] = std::numeric_limits<float>::max();
      }
    }
  }

  auto res = calculate(ny, nx, img.data(), y0, x0, y1, x1);

  EXPECT_EQ(res.avg[0], std::numeric_limits<float>::max());
  EXPECT_EQ(res.avg[1], std::numeric_limits<float>::max());
  EXPECT_EQ(res.avg[2], std::numeric_limits<float>::max());
}

TEST(Pre0Test, CheckWithSmallNumbers) {
  const int ny = 10;
  const int nx = 10;
  const int y0 = 0;
  const int x0 = 0;
  const int y1 = 10;
  const int x1 = 10;

  std::array<float, 10 * 10 * 3> img{};
  for (auto c = 0; c < 3; ++c) {
    for (auto x = x0; x < x1; ++x) {
      for (auto y = y0; y < y1; ++y) {
        img[c + 3 * x + 3 * nx * y] = std::numeric_limits<float>::min();
      }
    }
  }

  auto res = calculate(ny, nx, img.data(), y0, x0, y1, x1);

  EXPECT_EQ(res.avg[0], std::numeric_limits<float>::min());
  EXPECT_EQ(res.avg[1], std::numeric_limits<float>::min());
  EXPECT_EQ(res.avg[2], std::numeric_limits<float>::min());
}

} // namespace
