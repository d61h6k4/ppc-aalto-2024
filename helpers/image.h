#pragma once

#include <memory>

namespace ppc {
struct Image {
  int width;
  int height;
  int channels;
  std::unique_ptr<uint8_t[]> data;
};
} // namespace ppc
