#ifndef _____PARSE_H_____
#define _____PARSE_H_____

#include <stack.h>
#include <array.h>
#include <stdbool.h>

void push_chars_stack(stack *stk, const char* str);
bool parse_tokens(array *tokens);

#endif /* _____PARSE_H_____ */
