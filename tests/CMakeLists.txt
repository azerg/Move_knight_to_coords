project(tests)

set(sources test.cpp ${CMAKE_SOURCE_DIR}/src/KnightMoves.cpp)
add_executable(tests ${sources})

add_test(NAME "{0,0}" COMMAND tests "0" "0")
add_test(NAME "{-1,-1}" COMMAND tests "-1" "-1")
add_test(NAME "{250,-2}" COMMAND tests "250" "-2")
add_test(NAME "{5555,-12345}" COMMAND tests "5555" "-12345")
add_test(NAME "{55567,45678}" COMMAND tests "55567" "45678")