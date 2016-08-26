#include <iostream>
#include "KnightMoves.h"

#define CONSOLE(message) std::cout << message << std::endl;

int main(int agrc, char* argv[])
{
  auto result = CalculateMoves({atoi(argv[1]),atoi(argv[2])});
  CONSOLE("Reached target in " << result.stepsCount << " steps. Comparings done: " << result.numberOfComparings);
}

