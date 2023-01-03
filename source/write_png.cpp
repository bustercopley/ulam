#include "write_png.hpp"

#include <png.h>

#include <stdexcept>
#include <vector>

#define SOURCE_LOC const char *file = __FILE__, int line = __LINE__
inline auto check(auto status, SOURCE_LOC) {
  if (!status) {
    std::fprintf(stderr, "%s:%d: check failed\n", file, line);
    throw std::runtime_error("Error writing PNG");
  }
  return status;
}

void write_png(const char *filename, int width, int height,
               std::uint8_t *data) {
  constexpr auto bit_depth = 8;
  constexpr auto color_type = PNG_COLOR_TYPE_RGB_ALPHA;
  FILE *file = check(fopen(filename, "wb"));
  auto png_ptr = check(png_create_write_struct(PNG_LIBPNG_VER_STRING, nullptr,
                                               nullptr, nullptr));
  auto info_ptr = check(png_create_info_struct(png_ptr));
  check(!setjmp(png_jmpbuf(png_ptr)));
  png_init_io(png_ptr, file);
  check(!setjmp(png_jmpbuf(png_ptr)));
  png_set_IHDR(png_ptr, info_ptr, width, height, bit_depth, color_type,
               PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_BASE,
               PNG_FILTER_TYPE_BASE);
  png_write_info(png_ptr, info_ptr);
  check(!setjmp(png_jmpbuf(png_ptr)));
  auto row_pointers = std::vector<png_bytep>(height);
  for (int i = 0; auto &row_pointer : row_pointers) {
    row_pointer = data + (4 * width) * i++;
  }
  png_write_image(png_ptr, std::data(row_pointers));
  check(!setjmp(png_jmpbuf(png_ptr)));
  png_write_end(png_ptr, nullptr);
  png_destroy_read_struct(&png_ptr, &info_ptr, nullptr);
  fclose(file);
}
