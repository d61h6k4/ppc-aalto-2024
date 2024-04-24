

#include "gtest/gtest.h"
#include <array>

#include "exercises/mf/mf1.h"

namespace {

TEST(Mf1Test, Example1dOddKernelCheck) {
  auto in = std::array<float, 3>{0.83151951, 0.15822186, 0.30184449};

  auto exp = std::array<float, 3>{0.49487066268920898, 0.30184449,
                                  0.23003315925598145};

  std::vector<float> out;
  out.resize(1 * 3);

  ppc::mf(1, 3, 1, 1, in.data(), out.data());

  for (auto i = 0; i < 3; ++i) {
    EXPECT_NEAR(exp[i], out[i], 1e-5) << "Mismatch at position: " << i;
  }
}

TEST(Mf1Test, Example1dTOddKernelCheck) {
  auto in = std::array<float, 3>{0.83151951, 0.15822186, 0.30184449};

  auto exp = std::array<float, 3>{0.49487066268920898, 0.30184449,
                                  0.23003315925598145};

  std::vector<float> out;
  out.resize(1 * 3);

  ppc::mf(3, 1, 1, 1, in.data(), out.data());

  for (auto i = 0; i < 3; ++i) {
    EXPECT_NEAR(exp[i], out[i], 1e-5) << "Mismatch at position: " << i;
  }
}

TEST(Mf1Test, ExampleOddKernelCheck) {
  auto in = std::array<float, 100>{
      0.83151951, 0.15822186, 0.30184449, 0.62918585, 0.53705921, 0.17689269,
      0.80909173, 0.90798536, 0.12309407, 0.69996566, 0.23909772, 0.64494266,
      0.96490359, 0.5094244,  0.10827875, 0.80270269, 0.39915961, 0.58024097,
      0.3725465,  0.11891794, 0.17751392, 0.43747135, 0.91954191, 0.48178709,
      0.3588881,  0.57529722, 0.11698103, 0.66818444, 0.53035854, 0.78597043,
      0.87586533, 0.56344078, 0.83620028, 0.28210862, 0.69486999, 0.51782611,
      0.40661355, 0.76039496, 0.81177171, 0.07158876, 0.07402729, 0.61804063,
      0.88990985, 0.94761395, 0.7134854,  0.50714538, 0.65985421, 0.53952407,
      0.68538061, 0.72320675, 0.25116334, 0.73540031, 0.15667732, 0.42733337,
      0.66038003, 0.55272719, 0.33852468, 0.77376526, 0.26668005, 0.51688013,
      0.10182178, 0.09529765, 0.23255788, 0.26652327, 0.65575945, 0.39252781,
      0.37757912, 0.34716092, 0.62827294, 0.00255602, 0.88480701, 0.98191785,
      0.02315218, 0.96215495, 0.80462741, 0.24664944, 0.66954176, 0.43827505,
      0.46915594, 0.99014068, 0.92800451, 0.939028,   0.27714896, 0.46089852,
      0.16389247, 0.41668195, 0.60331666, 0.64550427, 0.12846735, 0.26232293,
      0.09206791, 0.14583284, 0.1748501,  0.55691054, 0.53913057, 0.83623721,
      0.46014056, 0.46105677, 0.53909184, 0.35061915};

  auto exp = std::array<float, 100>{
      0.44202017784118652, 0.47339355945587158, 0.56930512189865112,
      0.52324175834655762, 0.52324175834655762, 0.46810939908027649,
      0.69147181510925293, 0.48970028758049011, 0.47639372944831848,
      0.24782028794288635, 0.33828455209732056, 0.43747135,
      0.5094244,           0.5094244,           0.5094244,
      0.39915961,          0.58024097,          0.53035854,
      0.58024097,          0.45145252346992493, 0.50045609474182129,
      0.64494266,          0.56344078,          0.5094244,
      0.5094244,           0.40661355,          0.57529722,
      0.53035854,          0.58024097,          0.45145252346992493,
      0.50045609474182129, 0.61804063,          0.61804063,
      0.7134854,           0.51782611,          0.51782611,
      0.53952407,          0.65985421,          0.68538061,
      0.70429372787475586, 0.59074068069458008, 0.61804063,
      0.61804063,          0.69486999,          0.55272719,
      0.55272719,          0.53952407,          0.65985421,
      0.68538061,          0.60113036632537842, 0.17649255692958832,
      0.23255788,          0.42733337,          0.65575945,
      0.55272719,          0.55272719,          0.50714538,
      0.53952407,          0.53952407,          0.57257652282714844,
      0.49328184127807617, 0.23255788,          0.26652327,
      0.42733337,          0.55272719,          0.55272719,
      0.39252781,          0.43827505,          0.46915594,
      0.49301803112030029, 0.9064057469367981,  0.27714896,
      0.27714896,          0.27714896,          0.41668195,
      0.41668195,          0.41668195,          0.46915594,
      0.43827505,          0.36573943495750427, 0.9064057469367981,
      0.27714896,          0.46089852,          0.46089852,
      0.53913057,          0.53913057,          0.46105677,
      0.46915594,          0.46105677,          0.40988755226135254,
      0.53691864013671875, 0.22599953413009644, 0.36902374029159546,
      0.36902374029159546, 0.5000145435333252,  0.49963557720184326,
      0.53218674659729004, 0.50007426738739014, 0.40583795309066772,
      0.30647104978561401};

  std::vector<float> out;
  out.resize(10 * 10);

  ppc::mf(10, 10, 1, 1, in.data(), out.data());

  for (auto i = 0; i < 100; ++i) {
    EXPECT_NEAR(exp[i], out[i], 1e-5) << "Mismatch at position: " << i;
  }
}

} // namespace