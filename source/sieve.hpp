#pragma once

#include <algorithm>
#include <array>
#include <cstddef>
#include <cstdint>
#include <numeric>
#include <tuple>

constexpr void sift_mark(auto start, auto stop, auto step) {
  *start = false;
  while (stop - start > step) {
    start += step;
    *start = false;
  }
}

constexpr void sift(auto &container) {
  using std::begin;
  using std::end;
  std::fill(begin(container), end(container), true);

  // Value at position i: val(i) = 2i + 3
  // Position of value v: idx(v) = (v - 3) / 2
  // Step between (odd) multiples of p:
  //     idx((n + 2)p) - idx(np)
  //   = (np + 2p - 3) / 2 - (np - 3) / 2
  //   = p = 2i + 3
  // Position of square of value at i:
  //   idx(val(i)²) = idx(4i² + 12i + 9) = 2i² + 6i + 3

  std::ptrdiff_t position{0};   // position of next candidate
  auto iter = begin(container); // iterator to square of next candidate
  while (2 * position + 3 < end(container) - iter) {
    iter += 2 * position + 3;
    if (container[position]) {
      sift_mark(iter, end(container), 2 * position + 3);
    }
    if (2 * position + 3 < end(container) - iter) {
      iter += 2 * position + 3;
      ++position;
    } else {
      break;
    }
  }
}
