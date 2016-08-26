#include <iostream>
#include "KnightMoves.h"

#define CONSOLE(message) std::cout << message << std::endl;

int main(int agrc, char* argv[])
{
  if (agrc != 3)
  {
    CONSOLE("Usage: <dest X coord> <dest Y coord>\n"
            "Coords are expected to be a values of integer.");
    return 0;
  }

  auto result = CalculateMoves({atoi(argv[1]),atoi(argv[2])});
  CONSOLE("Reached target in " << result.stepsCount << " steps. Comparings done: " << result.numberOfComparings);
}

