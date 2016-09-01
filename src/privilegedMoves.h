#pragma once

#include <array>
#include <vector>
#include "KnightMoves.h"

namespace privileged_moves
{
  extern std::vector<ChessMove> privilegedMoves;

  unsigned int PickPrivilegedMoves(
    const std::array<ChessMove, 8>& allPossibleMoves,
    ChessMove chosen1stMove);

  bool OnTheSameCoordOptimizationPossible(const Point& currentPt, const Point& destPt, uint64_t* stepsCount, uint64_t* numberOfComparings);
} // namespace privileged_moves


