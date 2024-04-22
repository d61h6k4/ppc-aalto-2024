#pragma once

#include "helpers/image.h"
#include <optional>
#include <string>

namespace ppc {
std::optional<Image> read_png_file(const std::string &filename);
}
