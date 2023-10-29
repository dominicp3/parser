#include "parse.h"
#include "grammar.h"
#include "lexer.h"
#include <stdbool.h>

void push_chars_stack(stack *stk, const char* str)
{
        if (!stk || !str)
                return;

        token tkn;
        char c[2] = {'\0', '\0'};

        do {
                *c = *str;

                token_set(&tkn, c, token_type_char(*str));
                stack_push(stk, &tkn);
        } while (*++str);
}

bool parse_tokens(array *tokens)
{
        if (!tokens)
                return false;

        stack *stk = stack_init(sizeof(token));

        push_chars_stack(stk, "$S");

        token cur_tkn_input;
        token cur_tkn_stack;

        size_t index = 0;
        while (index < array_size(tokens)) {
                cur_tkn_input = *(token *) array_get(tokens, index);
        }

        (void) cur_tkn_input;
        (void) cur_tkn_stack;

        stack_destroy(stk);

        return true;
}
