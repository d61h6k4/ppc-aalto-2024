
#include "gtest/gtest.h"
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

#include "exercises/cp/cp1.h"
#include "helpers/png_utils.h"

namespace {

TEST(Cp1Test, SmallExampleCheck) {
  std::array<float, 9> data = {
      0.7551154160935887, 0.5689297291090776, 0.7050092710839561,
      0.8358774871996657, 0.9892637252134603, 0.39319196357175146,
      0.8631422476328803, 0.7306355809513364, 0.6609835212701702};
  std::array<float, 9> expected = {0.9999999999999996,
                                   0.0f,
                                   0.0f,
                                   -0.48898962011474034,
                                   1.0,
                                   0.0f,
                                   0.4265511,
                                   0.5803745180425443,
                                   0.9999999999999999};
  std::array<float, 9> result = {};
  ppc::corelate(3, 3, data.data(), result.data());

  for (auto i = 0; i < 9; ++i) {
    EXPECT_NEAR(expected[i], result[i], 1e-5) << "Mismatch at position: " << i;
  }
}

TEST(Cp1Test, ImageExampleCheck) {
  auto r = ppc::read_png_file("testdata/1d.png");
  std::vector<float> result;
  result.resize(r->height * r->height);

  std::vector<float> data;
  data.resize(r->height * r->width);
  std::transform(r->data.get(), r->data.get() + r->height * r->width,
                 data.begin(),
                 [](uint8_t el) { return static_cast<float>(el); });

  ppc::corelate(r->height, r->width, data.data(), result.data());

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
