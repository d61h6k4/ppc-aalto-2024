
#include "exercises/mf/mf2.h"
#include "hwy/contrib/thread_pool/thread_pool.h"
#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <vector>

namespace ppc {
void mf(int ny, int nx, int hy, int hx, const float *in, float *out) {
  hwy::ThreadPool pool(hwy::ThreadPool::MaxThreads());
  pool.Run(0, ny, [&](uint64_t y, size_t /* thread */) {
    for (auto x = 0; x < nx; ++x) {

      std::vector<float> w;
      w.reserve((2 * hy + 1) * (2 * hx + 1));
      for (auto j = std::max(0, static_cast<int>(y) - hy);
           j < std::min(static_cast<int>(y) + hy + 1, ny); ++j) {
        for (auto i = std::max(0, x - hx); i < std::min(x + hx + 1, nx); ++i) {
          w.push_back(in[i + nx * j]);
        }
      }
      std::sort(w.begin(), w.end());

      auto n = w.size();
      if (n % 2 == 1) {
        size_t k = (n - 1) / 2;
        out[x + nx * y] = w[k];
      } else {
        size_t k = n / 2;
        out[x + nx * y] = (w[k - 1] + w[k]) / 2.0f;
      }
    }
  });
}
} // namespace ppc
