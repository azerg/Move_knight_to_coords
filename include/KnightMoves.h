#pragma once 

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

  bool operator==(const Point& right)
  {
    return this->x == right.x && this->y == right.y;
  }
  Point operator+(Point pt) noexcept
  {
    return Point(this->x + pt.x, this->y + pt.y);
  }
};

struct ChessMove
{
  // coordinates on chess board
  Point pt;
  Direction direction;

  bool operator==(const ChessMove& right)
  {
    return (this->direction == right.direction &&
            this->pt == right.pt);
  }

  ChessMove& operator=(const ChessMove& right)
  {
    pt = right.pt;
    direction = right.direction;
    return *this;
  }
};

struct Result
{
  uint64_t numberOfComparings;
  uint64_t stepsCount;
};

Result CalculateMoves(Point destPt);

