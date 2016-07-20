// KnightMoves.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <cstdint>
#include <cassert>
#include <math.h>

#define CONSOLE(message) std::cout << message << std::endl;

enum class Direction
{
  BottomRight,
  TopRight,
  TopLeft,
  BottomLeft
};

std::ostream& operator<<(std::ostream& os, const Direction& direction)
{
  switch (direction)
  {
  case Direction::BottomRight:
    os << "BottomRight";
    break;
  case Direction::TopRight:
    os << "TopRight";
    break;
  case Direction::TopLeft:
    os << "TopLeft";
    break;
  case Direction::BottomLeft:
    os << "BottomLeft";
    break;
  default:
    assert(false);
    break;
  }

  return os;
}

struct Point
{
  int x, y;
};

struct ChessMove
{
  // 'x' and 'y' coordinates on chess board
  Point pt;
  Direction direction;
};

ChessMove movesCoords[8] = {
  {{2,1},  Direction::TopRight},
  {{1,2},  Direction::TopRight},
  {{-1,2}, Direction::TopLeft},
  {{-2,1}, Direction::TopLeft},
  {{-2,-1},Direction::BottomLeft},
  {{-1,-2},Direction::BottomLeft},
  {{1,-2}, Direction::BottomRight},
  {{2,-1}, Direction::BottomRight}
};

uint64_t DistanceBetween(const Point& pt1, const Point& pt2)
{
  return sqrt(pow(pt1.x - pt2.x, 2) + pow(pt1.y - pt2.y, 2));
}

ChessMove FindCloserMove(const Point& pt1, const Point& pt2)
{
  return movesCoords[0];
}

Point MoveCloser(const Point& currentPt, const Point& destPt)
{
  auto move = FindCloserMove(currentPt, destPt);

  CONSOLE("direction:" << move.direction);

  return {currentPt.x + move.pt.x, currentPt.y + move.pt.y};
}

int main()
{
  Point pt1{0,0};
  Point pt2{2,1};

  std::cout << DistanceBetween(pt1, pt2);
}

