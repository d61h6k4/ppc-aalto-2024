

#include "helpers/bmp_utils.h"
#include "helpers/png_utils.h"
#include "gtest/gtest.h"
#include <algorithm>
#include <cstdint>

namespace ppc {
// https://en.wikipedia.org/wiki/BMP_file_format
TEST(BMPTest, Example1Check) {
  Image image = {.width = 2,
                 .height = 2,
                 .channels = 3,
                 .data = std::unique_ptr<uint8_t[]>(new uint8_t[2 * 2 * 3])};
  // RGB
  std::array<uint8_t, 2 * 2 * 3> data = {0,   0, 255, 0,   255, 0,
                                         255, 0, 0,   255, 255, 255};
  std::copy(data.begin(), data.end(), image.data.get());

  write_image_as_bmp(image, "/tmp/exampl1.bmp");
}

TEST(BMPTest, PngReadCheck) {
  auto r = read_png_file("testdata/1e.png");
  ASSERT_TRUE(r.has_value());

  write_image_as_bmp(r.value(), "/tmp/1e.bmp");
}

} // namespace ppc
