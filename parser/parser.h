#ifndef _____PARSER_H_____
#define _____PARSER_H_____

#include "token.h"

#include <stack.h>
#include <array.h>
#include <stdbool.h>

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

extern const char *parse_table[NUM_VAR][NUM_TERM]; // = {
/*        +,    -,    *,    /,     (,     ),   num,   $ */
// /* S */ {"!",  "!",  "!",  "!",   "E",   "!",  "E",  "@"},
// /* E */ {"!",  "!",  "!",  "!",  "(E)",  "@",  "nT", "!"},
// /* T */ {"+E", "-E", "*E", "/E",  "!",   "!",  "!",  "@"}
// };

enum VAR_INDEX variable_index(char c);
enum TERM_INDEX terminal_index(token tkn);

bool token_equal_char(token tkn, char c);

enum TERMINAL_VARIABLE is_char_terminal_variable(char c);

void push_chars_stack(stack__t *stk, const char* str);
bool parse_tokens(array_t *tokens);

#endif /* _____PARSER_H_____ */
