project(tests)

set(sources test.cpp ${CMAKE_SOURCE_DIR}/src/KnightMoves.cpp)
add_executable(test ${sources})

add_test(NAME "{0,0}" COMMAND test "0" "0")
add_test(NAME "{-1,-1}" COMMAND test "-1" "-1")
add_test(NAME "{250,-2}" COMMAND test "250" "-2")
add_test(NAME "{5555,-12345}" COMMAND test "5555" "-12345")
add_test(NAME "{55567,45678}" COMMAND test "55567" "45678")