
#include "hwy/aligned_allocator.h"
#include "hwy/highway.h"
#include <cmath>

HWY_BEFORE_NAMESPACE();

namespace ppc {
namespace HWY_NAMESPACE {

namespace hn = hwy::HWY_NAMESPACE;

float MeanVec(const float *HWY_RESTRICT v, size_t size) {
  const hn::ScalableTag<float> d;
  const size_t N = hn::Lanes(d);
  HWY_DASSERT(size >= N);

  hn::Vec<decltype(d)> sum = hn::Zero(d);
  size_t i = 0;
  for (; i <= size - N; i += N) {
    const hn::Vec<decltype(d)> v0 = hn::LoadU(d, v + i);
    sum = hn::Add(v0, sum);
  }

  float fsum = hn::ReduceSum(d, sum);
  for (; i < size; ++i) {
    fsum += v[i];
  }

  return fsum / static_cast<float>(size);
}

float L2LengthVec(const float *HWY_RESTRICT v, size_t size, float mean_v) {
  const hn::ScalableTag<float> d;
  const size_t N = hn::Lanes(d);

  hn::Vec<decltype(d)> dist_vec = hn::Zero(d);
  const auto mean_v_vec = hn::Set(d, mean_v);

  size_t i = 0;
  for (; i <= size - N; i += N) {
    const hn::Vec<decltype(d)> v0 = hn::LoadU(d, v + i);
    const auto diff = hn::Sub(v0, mean_v_vec);
    dist_vec = hn::MulAdd(diff, diff, dist_vec);
  }

  float dist = hn::ReduceSum(d, dist_vec);
  for (; i < size; ++i) {
    dist += (v[i] - mean_v) * (v[i] - mean_v);
  }

  return std::sqrt(dist);
}

} // namespace HWY_NAMESPACE
} // namespace ppc

HWY_AFTER_NAMESPACE();
