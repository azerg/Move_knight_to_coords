Move knight to coordinates
=========
An algorithm of moving knight in chess.
# [![Build Status](https://travis-ci.org/azerg/Move_knight_to_coords.png )] ( https://travis-ci.org/azerg/Move_knight_to_coords)

### Task:
* Calculate number of moves required by chess knight to move from (0,0) to definite coordinates.
* Size of chess board is unlimited.

### Solution:
1. Lets define list of possible knight moves:
    ```
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
    ```
2. Lets apply recursivly moves to the definite knight coord, picking _movesCoords[x]_ with minimal distance to the _destination point_.



### Version info for sample test data:

#### v 0.2:
+ using predefined direction as long as possible
+ same line optimization.
| Coords    |   Steps   |   Comparings |
| :------------: |:----------------:|:---------------:|
|{0, 0}|                2 |              21
|{-1, -1}|              5 |              9
|{5, -30}|              11 |             45
|{-30, 5}|              17 |             145
|{250, -2}|             128 |            20
|{55, -290}|            151 |            1201
|{5555, -12345}|        6180|            33980
|{55567, 45678}|        34907|           191895

#### v 0.1:
| Coords    |   Steps   |   Comparings |
| :------------: |:----------------:|:---------------:|
|{0, 0}|                2 |              20
|{-1, -1}|              4 |              10
|{5, -30}|              15 |             150
|{-30, 5}|              15 |             150
|{250, -2}|             128 |            1250
|{55, -290}|            147 |            1305
|{5555, -12345}|        6304|            63040
|{55567, 45678}|        34905|           349050