// Copyright(C) Tommy Hinks <tommy.hinks@gmail.com>
// This file is subject to the license terms in the LICENSE file
// found in the top-level directory of this distribution.

#include "thinks/poisson_disk_sampling/examples/vec_traits_in_namespace_example.h"

#include <cassert>
#include <cstdint>
#include <fstream>

#include "thinks/poisson_disk_sampling/poisson_disk_sampling.h"

namespace {

struct Vec3 {
  float x;
  float y;
  float z;
};

}  // namespace

namespace thinks {

template <>
struct VecTraits<Vec3> {
  using ValueType = float;

  static constexpr auto kSize = 3;

  static ValueType Get(const Vec3& v, const std::size_t i) {
    return *(&v.x + i);
  }

  static void Set(Vec3* const v, const std::size_t i, const ValueType val) {
    *(&v->x + i) = val;
  }
};

} // namespace thinks

namespace examples {

void VecTraitsInNamespaceExample(const std::string& filename) {
  constexpr auto radius = 2.f;
  const std::array<float, 3> x_min = {-10.f, -10.f, -10.f};
  const std::array<float, 3> x_max = {10.f, 10.f, 10.f};
  const auto samples =
      thinks::PoissonDiskSampling<float, 3, Vec3>(radius, x_min, x_max);

  std::ofstream ofs{filename};
  assert(ofs);
  for (const auto& sample : samples) {
    ofs << sample.x << ", " << sample.y << ", " << sample.z << '\n';
  }
  ofs.close();
}

}  // namespace examples
