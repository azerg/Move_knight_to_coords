#include "privilegedMoves.h"

namespace privileged_moves
{

  /*!
  * This list is used starting from 2nd step. On the first step we are looking for a best direction.
  * All other moves (until one of coords ~ targetPoint coord) will be on the same direction.
  * So:
  *     1. on 1st step we do all comparsions to pick a valid direction.
  *     2. for next comparsions we are saving @moveCoords with definite _direction_ to @privilegedMoves.
  *     3. we do use step coords only from @privilegedMoves until one of our current coords
  *        came close to the coord of target point ( x or y )
  */
  std::vector<ChessMove> privilegedMoves; //< dynamically-filled list of moves ( one destination only )

  unsigned int PickPrivilegedMoves(
    const std::array<ChessMove, 8>& allPossibleMoves,
    ChessMove chosen1stMove)
  {
    for (auto& moveIt: allPossibleMoves)
    {
      if (moveIt.direction == chosen1stMove.direction)
      {
        privilegedMoves.push_back(moveIt);
      }
    }

    return privilegedMoves.size();
  }

  bool OnTheSameCoordOptimizationPossible(const Point& currentPt, const Point& destPt, uint64_t* stepsCount, uint64_t* numberOfComparings)
  {
    int differentSrc, differentDest;
    bool bSameFound = false;

    ++*numberOfComparings;
    if (currentPt.x == destPt.x)
    {
      differentSrc = currentPt.y;
      differentDest = destPt.y;
      bSameFound = true;
    }
    else if (currentPt.y == destPt.y)
    {
      differentSrc = currentPt.x;
      differentDest = destPt.x;
      bSameFound = true;
    }

    if (!bSameFound)
      return false;

    /// in theory we may start not in {0,0} and dest point
    /// will be closer to {0,0} as we.
    if (std::abs(differentSrc) > std::abs(differentDest))
    {
      std::swap(differentSrc, differentDest);
    }

    // we dont expect to see differentSrc == 0
    if (differentSrc == 0)
      return false;

    auto div = std::div(differentDest, differentSrc);
    *stepsCount += div.quot * 2; /// we need two steps to reach 4x coord.
    switch (div.rem)
    {
    case 0: /// wow. rly we got it?
      break;
    case 1: /// ah close to dest... but 3 moves left
      /*
      o - current
      d - dest

      . . . .    . . . .    . . . .    . . . .
      . . . . -> . . . . -> . o . . -> . . . .
      . . o .    . . . .    . . . .    . . . .
      . . d .    o . d .    . . d .    . . o .

      */
      *stepsCount += 3;
      break;
    case 2:
      /// 2 moves to reach the target left:
      /*
      o - current
      d - dest

      . . o .    . . . .    . . . . 
      . . . . -> o . . . -> . . . .
      . . d .    . . d .    . . o .

      */
      *stepsCount += 2;
      break;
    case 3:
      /// 3 moves to reach the target left:
      /*
      o - current
      d - dest

      . . o .    . . . .    . . . .    . . . .
      . . . . -> . . . . -> . . . o -> . . . .
      . . . .    . o . .    . . . .    . . . .
      . . d .    . . d .    . . d .    . . o .

      */
      *stepsCount += 3;
      break;
    default:
      return false; /// O.o
      break;
    }
    
    return true;
  }

} // namespace privileged_moves
