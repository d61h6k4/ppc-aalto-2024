

#include "exercises/cp/ops.h"


#include "hwy/highway.h"
#include "hwy/tests/test_util-inl.h"

HWY_BEFORE_NAMESPACE();
namespace ppc {
namespace HWY_NAMESPACE {
namespace hn = hwy::HWY_NAMESPACE;

HWY_NOINLINE void TestMeanVec() {
  std::vector<float> in = {0.66897318, 0.84343284, 0.47596726, 0.51690874,
                           0.62002344, 0.66113556, 0.76851434, 0.12560271,
                           0.37458967, 0.72227079};
  const auto exp = 0.5777419;

  float res = MeanVec(in.data(), in.size());

  EXPECT_NEAR(exp, res, 1e-3);
}

HWY_NOINLINE void TestL2LengthVec() {
  std::vector<float> in = {0.66897318, 0.84343284, 0.47596726, 0.51690874,
                           0.62002344, 0.66113556, 0.76851434, 0.12560271,
                           0.37458967, 0.72227079};
  const auto exp = 0.6361597311211996;

  float res = L2LengthVec(in.data(), in.size(), 0.5777419f);

  EXPECT_NEAR(exp, res, 1e-3);
}

} // namespace HWY_NAMESPACE
} // namespace ppc
HWY_AFTER_NAMESPACE();

#if HWY_ONCE
namespace ppc {
HWY_BEFORE_TEST(OpsTest);
HWY_EXPORT_AND_TEST_P(OpsTest, TestMeanVec);
HWY_EXPORT_AND_TEST_P(OpsTest, TestL2LengthVec);
} // namespace ppc
#endif
