#include "sieve.hpp"
#include "write_png.hpp"

#include <cstdint>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

#include <png.h>

int main() {
  try {
    constexpr int size = 800;
    std::vector<bool> sieve(2 * size * size);
    std::vector<unsigned int> image_data(size * size);
    sift(sieve);

    constexpr unsigned int colors[]{0xffffffff, 0xff000000};

    int sieve_index = 0;
    auto add_point = [&](int x, int y) {
      auto offset = x + size * y;
      auto color = colors[(int)sieve.at(sieve_index++)];
      if (offset >= 0 && offset < size * size) {
        image_data.at(offset) = color;
      }
    };

    int x = size / 2;
    int y = size / 2;
    image_data[x + size * y] = colors[0]; // 1
    add_point(--x, y);                    // 3
    for (int n = 0; n != size; ++n) {
      for (int j = 0; j != n; ++j) {
        add_point(++x, ++y);
      }
      for (int j = 0; j != n; ++j) {
        add_point(++x, --y);
      }
      for (int j = 0; j != n; ++j) {
        add_point(--x, --y);
      }
      add_point(--x, y);
      for (int j = 0; j != n; ++j) {
        add_point(--x, ++y);
      }
    }
    write_png("ulam.png", size, size, (std::uint8_t *)std::data(image_data));
    return 0;
  } catch (std::exception &e) {
    std::fprintf(stderr, "%s\n", e.what());
    return 1;
  }
}
