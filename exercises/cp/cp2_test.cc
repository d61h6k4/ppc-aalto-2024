
#include "exercises/cp/cp2.h"
#include "gtest/gtest.h"
#include <vector>

#include <algorithm>
#include <csetjmp>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <ios>
#include <iostream>
#include <memory>

#include <sstream>
#include <string>

#include "helpers/png_utils.h"

namespace {

TEST(Cp2aTest, ImageExampleCheck) {
  auto r = ppc::read_png_file("testdata/1d.png");
  std::vector<float> result;
  result.resize(r->height * r->height);

  std::vector<float> data;
  data.resize(r->height * r->width);
  std::transform(r->data.get(), r->data.get() + r->height * r->width,
                 data.begin(),
                 [](uint8_t el) { return static_cast<float>(el); });

  ppc::Corelate(r->height, r->width, data.data(), result.data());

  std::vector<float> exp;
  exp.reserve(r->height * r->height);

  std::ifstream exp_file("testdata/1d_corelate.npy");
  while (exp_file) {
    std::string row;
    if (!std::getline(exp_file, row)) {
      break;
    }
    std::istringstream ss(row);
    std::string field;
    while (std::getline(ss, field, ',')) {
      std::stringstream fs(field);
      float f = 0.0f;
      fs >> f;

      exp.push_back(f);
    }
  }

  for (auto i = 0; i < r->height * r->height; ++i) {
    EXPECT_NEAR(exp[i], result[i], 1e-5) << "Mismatch at position: " << i;
  }
}

} // namespace
