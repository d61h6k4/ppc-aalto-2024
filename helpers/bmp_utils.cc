
#include <array>
#include <cstddef>
#include <cstdint>
#include <fstream>
#include <ios>
#include <iostream>

#include "helpers/bmp_utils.h"

namespace ppc {

#pragma pack(push, 1)
struct BmpHeader {
  std::array<unsigned char, 2> bitmap_signature_bytes = {'B', 'M'};
  uint32_t size_of_bitmap_file =
      54; // Calculate this value as pixel_data_offset + width * height *
          // channels
  uint32_t reserved_bytes = 0;
  uint32_t pixel_data_offset = 54;
};

struct BmpInfoHeader {
  uint32_t size_of_this_header = 40;
  int32_t width = 0;                   // set width
  int32_t height = 0;                  // set height
  uint16_t number_of_color_planes = 1; // must be 1
  uint16_t color_depth = 24;
  uint32_t compression_method = 0;
  uint32_t raw_bitmap_data_size = 0;    // generally ignored
  int32_t horizontal_resolution = 2835; // in pixel per meter
  int32_t vertialcal_resolution = 2835; // in pixel per meter
  uint32_t color_table_entries = 0;
  uint32_t important_colors = 0;
};
#pragma pack(pop)

void write_image_as_bmp(const Image &image, const std::string &filename) {
  // if channels number not 3, we don't write them
  if (image.channels != 3) {
    return;
  }

  std::ofstream fout(filename, std::ios::out | std::ios::binary);

  BmpInfoHeader bmpInfoHeader;
  bmpInfoHeader.width = image.width;
  bmpInfoHeader.height = image.height;
  bmpInfoHeader.size_of_this_header = sizeof(bmpInfoHeader);

  int rowbytes = (bmpInfoHeader.color_depth * image.width + 31) / 32 * 4;
  bmpInfoHeader.raw_bitmap_data_size = rowbytes * image.height;

  BmpHeader bmpHeader;
  bmpHeader.pixel_data_offset = sizeof(bmpHeader) + sizeof(bmpInfoHeader);
  bmpHeader.size_of_bitmap_file =
      bmpHeader.pixel_data_offset + bmpInfoHeader.raw_bitmap_data_size;

  std::cout << bmpHeader.size_of_bitmap_file << " "
            << bmpHeader.pixel_data_offset << std::endl;

  std::cout << "header:\n"
            << bmpInfoHeader.size_of_this_header << " " << bmpInfoHeader.width
            << " " << bmpInfoHeader.height << " "
            << bmpInfoHeader.raw_bitmap_data_size;

  std::cout << "rb = " << rowbytes;

  fout.write((char *)&bmpHeader, sizeof(bmpHeader));
  fout.write((char *)&bmpInfoHeader, sizeof(bmpInfoHeader));

  for (int y = image.height - 1; y >= 0; --y) {
    for (int x = 0; x < image.width; ++x) {
      fout.put(
          (unsigned char)(image.data.get()[2 + 3 * x + 3 * image.width * y]));
      fout.put(
          (unsigned char)(image.data.get()[1 + 3 * x + 3 * image.width * y]));
      fout.put(
          (unsigned char)(image.data.get()[0 + 3 * x + 3 * image.width * y]));
    }

    for (int x = image.width * 3; x < rowbytes; ++x) {
      fout.put(0);
    }
  }
}
} // namespace ppc
