#ifndef _____PARSER_H_____
#define _____PARSER_H_____

#include <stack.h>
#include <array.h>
#include <stdbool.h>
#include "token.h"

#define NUM_VAR 3
#define NUM_TERM 9

enum TERM_INDEX {
        PLUS_INDEX,
        MINUS_INDEX,
        TIMES_INDEX,
        DIVIDE_INDEX,
        OPEN_BRACKET_INDEX,
        CLOSED_BRAKCET_INDEX,
        INT_INDEX,
        EPSILON_INDEX,
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
        E -> ( E ) T | num T
        T -> + E | - E | * E | / E | @
*/

const char *parse_table[NUM_VAR][NUM_TERM] = {
/*        +,    -,    *,    /,     (,     ),   num,   @,   $ */
/* S */ {"!",  "!",  "!",  "!",   "E",   "!",  "E",  "!", "@"},
/* E */ {"!",  "!",  "!",  "!",  "(E)",  "!",  "nT", "!", "!"},
/* T */ {"+E", "-E", "*E", "/E",  "!",   "!",  "!",  "@", "@"}
};

enum TERM_INDEX var_index(token *tkn);
enum VAR_INDEX term_index(token *tkn);

void push_chars_stack(stack *stk, const char* str);
bool parse_tokens(array *tokens);

#endif /* _____PARSER_H_____ */
