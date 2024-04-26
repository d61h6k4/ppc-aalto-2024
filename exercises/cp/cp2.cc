#include "exercises/cp/cp2.h"
#include "exercises/cp/ops.h"
#include "hwy/aligned_allocator.h"
#include "hwy/highway.h"

HWY_BEFORE_NAMESPACE();

namespace ppc {
namespace HWY_NAMESPACE {

void CorelateVec(int ny, int nx, const float *HWY_RESTRICT data,
                 float *HWY_RESTRICT result) {

  const hwy::HWY_NAMESPACE::ScalableTag<float> d;
  const size_t N = hwy::HWY_NAMESPACE::Lanes(d);

  hwy::AlignedFreeUniquePtr<float[]> norm_data =
      hwy::AllocateAligned<float>(ny * nx);

  for (auto i = 0; i < ny; ++i) {
    float x_mean = MeanVec(data + i * nx, static_cast<size_t>(nx));
    float x_norm = L2LengthVec(data + i * nx, static_cast<size_t>(nx), x_mean);

    for (auto j = 0; j < nx; ++j) {
      norm_data[j + i * nx] = (data[j + i * nx] - x_mean) / x_norm;
    }
  }

  for (auto i = 0; i < ny; ++i) {
    for (auto j = i; j < ny; ++j) {

      hwy::HWY_NAMESPACE::Vec<decltype(d)> res = hwy::HWY_NAMESPACE::Zero(d);
      size_t k = 0;
      for (; k <= nx - N; k += N) {
        const auto v0 =
            hwy::HWY_NAMESPACE::Load(d, norm_data.get() + k + i * nx);
        const auto v1 =
            hwy::HWY_NAMESPACE::Load(d, norm_data.get() + k + j * nx);
        res = hwy::HWY_NAMESPACE::MulAdd(v0, v1, res);
      }

      result[i + j * ny] = hwy::HWY_NAMESPACE::ReduceSum(d, res);

      for (; k < nx; ++k) {
        result[i + j * ny] +=
            (norm_data.get()[k + i * nx]) * (norm_data.get()[k + j * nx]);
      }
    }
  }
}
} // namespace HWY_NAMESPACE
} // namespace ppc

HWY_AFTER_NAMESPACE();

#if HWY_ONCE

namespace ppc {
HWY_EXPORT(CorelateVec);

HWY_DLLEXPORT void Corelate(int ny, int nx, const float *HWY_RESTRICT data,
                            float *HWY_RESTRICT result) {
  return HWY_STATIC_DISPATCH(CorelateVec)(ny, nx, data, result);
}
} // namespace ppc

#endif // HWY_ONCE
