#pragma once
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

  class Segment
  {
  public:
    Segment(bb_t bounding_box, size_t radius_of_circle):
      bbx_(bounding_box),
      rad_(radius_of_circle)
    {}
    bool isPointIn(const point_t p) const
    {
      long double dist = std::sqrt(std::pow(p.x, 2) + std::pow(p.y, 2));
      if (dist > rad_)
      {
        return false;
      }
      return true;
    }
    bb_t getBBox() const
    {
      return bbx_;
    }
  private:
    bb_t bbx_;
    size_t rad_;
  };
}
