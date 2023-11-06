#ifndef _____PARSER_H_____
#define _____PARSER_H_____

#include "token.h"

#include <stack.h>
#include <array.h>
#include <stdbool.h>
#include <tree.h>

#define NUM_VAR 3
#define NUM_TERM 8

enum TERMINAL_VARIABLE {
        TERMINAL,
        VARIABLE,
        INVALID
};

enum TERM_INDEX {
        PLUS_INDEX,
        MINUS_INDEX,
        TIMES_INDEX,
        DIVIDE_INDEX,
        OPEN_BRACKET_INDEX,
        CLOSED_BRAKCET_INDEX,
        INT_INDEX,
//      EPSILON_INDEX,
        SPECIAL_INDEX,
        TERM_ERROR_INDEX
};

enum VAR_INDEX {
        S_INDEX,
        E_INDEX,
        T_INDEX,
        VAR_ERROR_INDEX
};

/*
        @ = EPSILON
        ! = BLANK

        S -> E | @
        E -> ( E ) T | num T | @
        T -> + E | - E | * E | / E | @
*/

static const char *parse_table[NUM_VAR][NUM_TERM] = {
/*        +,    -,    *,    /,     (,     ),   num,   $   */
/* S */ {"!",  "!",  "!",  "!",   "E",   "!",  "E",  "@"},
/* E */ {"!",  "!",  "!",  "!",  "(E)T",  "@",  "nT", "!"},
/* T */ {"+E", "-E", "*E", "/E",  "!",   "@",  "!",  "@"}
};

tree_node_t *syntax_tree(array_t *tokens);

#endif /* _____PARSER_H_____ */
