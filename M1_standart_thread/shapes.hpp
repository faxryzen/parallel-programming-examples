#pragma once
#include <cstddef>
#include <cmath>

namespace sav
{
  struct bb_t
  {
    size_t width = 0;
    size_t height = 0;
  };

  struct point_t
  {
    size_t x = 0;
    size_t y = 0;
  };

  struct circle_t
  {
    size_t radius = 0;
    point_t center = {0, 0};
  };

    class Tile
  {
  public:
    Tile(bb_t size, circle_t circle):
      bb_(size),
      cc_(circle)
    {}
    bool isPointIn(const point_t p) const
    {
      double dist = std::sqrt(std::pow(p.x - cc_.center.x, 2) + std::pow(p.y - cc_.center.y, 2));
      if (dist >= cc_.radius)
      {
        return false;
      }
      return true;
    }
    bb_t getBoundingBox() const
    {
      return bb_;
    }
  private:
    bb_t bb_;
    circle_t cc_;
  };
}
