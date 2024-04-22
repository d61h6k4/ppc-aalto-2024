
#include "helpers/png_utils.h"
#include "gtest/gtest.h"

namespace ppc {

TEST(PngTest, SanityCheck) {
  auto r = read_png_file("testdata/1e.png");
  ASSERT_TRUE(r.has_value());
}

} // namespace ppc
