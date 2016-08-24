#include <iostream>
#include <cstdint>
#include <cassert>
#include <limits>
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

struct ChessMove
{
  // coordinates on chess board
  Point pt;
  Direction direction;

  ChessMove& operator=(const ChessMove& right)
  {
    pt = right.pt;
    direction = right.direction;
    return *this;
  }
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

uint64_t numberOfComparings{};

uint64_t DistanceBetween(const Point& pt1, const Point& pt2)
{
  ++numberOfComparings;
  return sqrt(pow(pt1.x - pt2.x, 2) + pow(pt1.y - pt2.y, 2));
}

ChessMove FindCloserMove(const Point& ptFrom, const Point& ptTo)
{
  ChessMove move{};
  uint64_t minDistance = std::numeric_limits<uint64_t>::max();

  for (auto& coord : movesCoords)
  {
    auto curDistance = DistanceBetween(Point(ptFrom) + coord.pt, ptTo);
    if (curDistance < minDistance)
    {
      minDistance = curDistance;
      move = coord;
    }
  }

  return move;
}

Point MoveCloser(const Point& currentPt, const Point& destPt)
{
  auto move = FindCloserMove(currentPt, destPt);
  move.pt = move.pt + currentPt; // doing move

  CONSOLE(move.direction << " (" << DistanceBetween(move.pt, destPt) << ")");

  return move.pt;
}

uint64_t CalculateMoves(Point destPt)
{
  CONSOLE("Looking for a way to: {" << destPt.x << ", " << destPt.y << "}");
  Point stepPt(0,0);
  uint64_t stepsCount{};

  do
  {
    stepPt = MoveCloser(stepPt, destPt);
    ++stepsCount;

    auto distance = DistanceBetween(stepPt, destPt);

    if (distance == 0) // oeps we did it
    {
      //
      break;
    }
    else if (distance == 1)
    {
      /*
      *   . . .                                       |  . . .
      *   . x . -> 2 moves left to get to dest point  |  . x . -> 3 moves left
      *   x . .                                       |  . x .
      */
      if (stepPt.x == destPt.x || stepPt.y == destPt.y)
      {
        // + 3 moves
        stepsCount += 3;
        CONSOLE("We stopped moving and are staying _not diagonally_ to the destination point. So 3 moves left.")
      }
      else
      {
        // + 2 moves
        stepsCount += 2;
        CONSOLE("We stopped moving and are staying _diagonally_ to the destination point. So 2 moves left.")
      }
      break;
    }

  } while (true);

  return stepsCount;
}

int main(int agrc, char* argv[])
{
  if (agrc != 3)
  {
    CONSOLE("Usage: <dest X coord> <dest Y coord>\n"
            "Coords are expected to be a values of integer.");
    return 0;
  }

  auto stepsCount = CalculateMoves({atoi(argv[1]),atoi(argv[2])});
  CONSOLE("Reached target in " << stepsCount << " steps. Comparings done: " << numberOfComparings);
}

