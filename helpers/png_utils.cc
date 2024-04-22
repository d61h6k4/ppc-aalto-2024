#include "helpers/png_utils.h"

#ifdef __cplusplus
extern "C" {
#endif
#include "png.h"
#ifdef __cplusplus
}
#endif
#include <algorithm>
#include <csetjmp>
#include <cstdint>
#include <cstdio>
#include <memory>

#include <string>

std::optional<ppc::Image> ppc::read_png_file(const std::string &filename) {
  // header for testing if it is a png
  png_byte header[8];

  // open file as binary in C format
  FILE *fp = fopen(filename.c_str(), "rb");
  if (!fp) {
    return std::nullopt;
  }

  // read the header
  fread(header, 1, 8, fp);

  // test if png
  if (png_sig_cmp(header, 0, 8) != 0) {
    fclose(fp);
    return std::nullopt;
  }

  // create png struct
  png_structp png_ptr =
      png_create_read_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);
  if (!png_ptr) {
    fclose(fp);
    return std::nullopt;
  }

  // create png info struct
  png_infop info_ptr = png_create_info_struct(png_ptr);
  if (!info_ptr) {
    png_destroy_read_struct(&png_ptr, (png_infopp) nullptr,
                            (png_infopp) nullptr);
    fclose(fp);
    return std::nullopt;
  }

  // create png info struct
  png_infop end_info = png_create_info_struct(png_ptr);
  if (!end_info) {
    png_destroy_read_struct(&png_ptr, (png_infopp) nullptr,
                            (png_infopp) nullptr);
    fclose(fp);
    return std::nullopt;
  }

  // png error stuff, not sure. libpng man suggests this.
  if (setjmp(png_jmpbuf(png_ptr))) {
    png_destroy_read_struct(&png_ptr, (png_infopp) nullptr,
                            (png_infopp) nullptr);
    fclose(fp);
    return std::nullopt;
  }

  // init png reading
  png_init_io(png_ptr, fp);

  // let libpng know you already read the first 8 bytes
  png_set_sig_bytes(png_ptr, 8);

  // read all the info up to the image data
  png_read_info(png_ptr, info_ptr);

  // variables to pass to get info
  int bit_depth, color_type;
  png_uint_32 twidth, theight;

  // get info about png
  png_get_IHDR(png_ptr, info_ptr, &twidth, &theight, &bit_depth, &color_type,
               nullptr, nullptr, nullptr);
  int width = twidth;
  int height = theight;
  int channels = png_get_channels(png_ptr, info_ptr);

  // Update the png info struct
  png_read_update_info(png_ptr, info_ptr);

  // Row size in bytes
  int rowbytes = png_get_rowbytes(png_ptr, info_ptr);

  // Allocate the image_data as a big block, to be given to opengl
  png_byte *image_data = new png_byte[rowbytes * height];
  if (!image_data) {
    // clean up memory and close stuff
    png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
    fclose(fp);
    return std::nullopt;
  }

  // row_pointers is for pointing to image_data for reading the png with libpng
  png_bytep *row_pointers = new png_bytep[height];
  if (!row_pointers) {
    // clean up memory and close stuff
    png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
    delete[] image_data;
    fclose(fp);
    return std::nullopt;
  }
  // set the individual row_pointers to point at the correct offsets of
  // image_data
  for (int i = 0; i < height; ++i) {
    row_pointers[i] = image_data + i * rowbytes;
  }

  // read the png into image_data through row_pointers
  png_read_image(png_ptr, row_pointers);

  Image image = {.width = width,
                 .height = height,
                 .channels = channels,
                 .data = std::unique_ptr<uint8_t[]>(
                     new uint8_t[width * height * channels * bit_depth / 8])};

  std::copy(image_data, image_data + rowbytes * height, image.data.get());

  // clean up memory and close stuff
  png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
  delete[] image_data;
  delete[] row_pointers;
  fclose(fp);

  return image;
}
