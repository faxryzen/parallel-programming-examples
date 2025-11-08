#ifndef SHAPES_HPP
#define SHAPES_HPP

#include <cstddef>
#include <cmath>

namespace sav
{
  struct point_t
  {
    long double x = 0;
    long double y = 0;
  };

  struct bb_t
  {
    size_t width = 0;
    size_t height = 0;
    point_t center = {0, 0};
  };
}

#endif
