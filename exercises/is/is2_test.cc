

#include "exercises/is/is.h"
#include "gtest/gtest.h"

#include "helpers/png_utils.h"

namespace {

TEST(IsTest, SegmentsCheck) {
  auto r = ppc::read_png_file("testdata/1a.png");

  std::vector<float> data;
  data.resize(r->height * r->width);
  std::transform(r->data.get(), r->data.get() + r->height * r->width,
                 data.begin(),
                 [](uint8_t el) { return static_cast<float>(el); });

  ppc::Result res = ppc::Segment(r->height, r->width, data.data());
  std::cout << res.y0 << "," << res.x0 << " " << res.y1 << "," << res.x1
            << "\n";
}

} // namespace
