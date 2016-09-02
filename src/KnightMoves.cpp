#include <iostream>
#include <cstdint>
#include <cassert>
#include <limits>
#include <math.h>
#include <array>
#include "KnightMoves.h"
#include "privilegedMoves.h"

//#define DISPLAY_PLOTS_FOR_GRAPH 

#ifndef DISPLAY_PLOTS_FOR_GRAPH
  #define CONSOLE(message) std::cout << message << std::endl;
#else
  #define CONSOLE(message)
#endif

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

std::array<ChessMove, 8> movesCoords{
  {{{2,1},  Direction::TopRight},
  {{1,2},  Direction::TopRight},
  {{-1,2}, Direction::TopLeft},
  {{-2,1}, Direction::TopLeft},
  {{-2,-1},Direction::BottomLeft},
  {{-1,-2},Direction::BottomLeft},
  {{1,-2}, Direction::BottomRight},
  {{2,-1}, Direction::BottomRight}}
};

uint64_t numberOfComparings{};
uint64_t stepsCount{};

uint64_t DistanceBetween(const Point& pt1, const Point& pt2)
{
  ++numberOfComparings;
  return sqrt(pow(pt1.x - pt2.x, 2) + pow(pt1.y - pt2.y, 2));
}

bool IsInSameQuart(Point pt1, Point pt2)
{
  auto CoordsInSameQuart = [](auto coord1, auto coord2) -> bool
  {
    return (coord1 > 0 && coord2 > 0) || (coord1 < 0 && coord2 < 0);
  };

  return CoordsInSameQuart(pt1.x, pt2.x) && 
         CoordsInSameQuart(pt1.y, pt2.y);
}

/*!
* Performing all possible comparsions to pick best one to perform move.
* This might be useful on 1st step for example.
*/
ChessMove FindCloserMoveRandomDirection(const Point& ptFrom, const Point& ptTo)
{
  ChessMove move{};
  static uint64_t minDistance = std::numeric_limits<uint64_t>::max();

  for (auto& coord : movesCoords)
  {
    auto curDistance = DistanceBetween(Point(ptFrom) + coord.pt, ptTo);
    if (curDistance < minDistance)
    {
      minDistance = curDistance;
      move = coord;
    }
    else
    /// lets prefer coords from our quart, even if distance is similar
    if (curDistance == minDistance && (IsInSameQuart(Point(ptFrom) + coord.pt, ptTo)))
    {
      move = coord;
    }
  }

  return move;
}

/*!
* Performing only set of privileged comparsions to pick best one to perform move.
* This might be useful when list of privileged comparsion is filled and we didnt reach
* x or y of the @targetPoint.
*/
ChessMove FindCloserMovePrivilegedDirection(const Point& ptFrom, const Point& ptTo)
{
  CONSOLE("<privileged>");
  ChessMove move{};
  static uint64_t minDistance = std::numeric_limits<uint64_t>::max();

  for (auto& coord : privileged_moves::privilegedMoves)
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

ChessMove FindCloserMove(const Point& ptFrom, const Point& ptTo)
{
  ChessMove move;

  if (privileged_moves::privilegedMoves.empty())
  {
    move = FindCloserMoveRandomDirection(ptFrom, ptTo);
  }
  else
  {
    /*!
    * Hardcoded value. Minimal distance that we could reach for @targetPoint  or
    * 'x' or 'y' of @targetPoint
    */
    const int minimalDistanceForPrivilegedMove = 3;

    ++numberOfComparings; //< we do additional compare here to check if we could still use @privelegedMoves list

    /// if we are too closeto 'x' or 'y' of target point
    if (abs(ptFrom.x - ptTo.x) <= minimalDistanceForPrivilegedMove ||
        abs(ptFrom.y - ptTo.y) <= minimalDistanceForPrivilegedMove)
    {
      privileged_moves::privilegedMoves.clear(); //< clear list of @privilegedMoves. We dont need it any more.
      move = FindCloserMove(ptFrom, ptTo);
    }
    else
    {
      move = FindCloserMovePrivilegedDirection(ptFrom, ptTo);
      if (move == ChessMove())
      {
        privileged_moves::privilegedMoves.clear();
        move = FindCloserMove(ptFrom, ptTo);
      }
    }
  }

  // call this only for the first move
  if (stepsCount == 0)
  {
    privileged_moves::PickPrivilegedMoves(movesCoords, move);
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

Result CalculateMoves(Point destPt)
{
  CONSOLE("Looking for a way to: {" << destPt.x << ", " << destPt.y << "}");
  Point stepPt(0,0);
  stepsCount = 0;
  numberOfComparings = 0;

#ifdef DISPLAY_PLOTS_FOR_GRAPH
  std::cout << "X,Y" << std::endl;
  std::cout << stepPt.x << ',' << stepPt.y << std::endl;
#endif

  do
  {
    stepPt = MoveCloser(stepPt, destPt);
    ++stepsCount;

    bool bsameCoordOptimized = privileged_moves::OnTheSameCoordOptimizationPossible(stepPt, destPt, &stepsCount, &numberOfComparings);
    if (bsameCoordOptimized)
    {
      // all steps were done in @OnTheSameCoordOptimizationPossible
      break;
    }

#ifdef DISPLAY_PLOTS_FOR_GRAPH
    std::cout << stepPt.x << ',' << stepPt.y << std::endl;
#endif

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

#ifdef DISPLAY_PLOTS_FOR_GRAPH
  std::cout << destPt.x << ',' << destPt.y << std::endl;
#endif

  return{numberOfComparings, stepsCount};
}

