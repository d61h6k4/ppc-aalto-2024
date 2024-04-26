#pragma once

#include "hwy/base.h"

namespace ppc {

HWY_DLLEXPORT void Corelate(int ny, int nx, const float *HWY_RESTRICT data,
                            float *HWY_RESTRICT result);
}
