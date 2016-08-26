#include <cstdint>
#include <cassert>

enum class Direction
{
  BottomRight,
  TopRight,
  TopLeft,
  BottomLeft
};

struct Point
{
  Point() = default;
  Point(int x, int y) :
    x{x},
    y{y}
  {}

  int x, y;

  Point operator+(Point pt) noexcept
  {
    return Point(this->x + pt.x, this->y + pt.y);
  }
};

struct Result
{
  uint64_t numberOfComparings;
  uint64_t stepsCount;
};

Result CalculateMoves(Point destPt);

