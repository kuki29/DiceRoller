#ifndef _DICE_ROLLER_DEFINES_H_
#define _DICE_ROLLER_DEFINES_H_

#include <vector>

// Token for addition
#define ADD (INT_MAX + 1)
// Token for substraction
#define SUB (INT_MAX + 2)
// Token for multiplication
#define MUL (INT_MAX + 3)
// Token for division
#define DIV (INT_MAX + 4)
// Token for error
#define ERR (INT_MAX + 1)

typedef unsigned int uint;
// TODO: change uint to int
// Pair of int and int
typedef std::pair<int, int> p_ii;
// Vector of pairs of int and int
typedef std::vector<p_ii> vec_p_ii;

#endif