#include "parser.h"
#include "lexer.h"
#include <stdbool.h>

enum TERM_INDEX var_index(token *tkn)
{
        if (!tkn)
                return TERM_ERROR_INDEX;
        
        switch (tkn->type) {
        case INT_TYPE:
                return INT_INDEX;

        case OPERATION_TYPE:
                switch (tkn->d.character) {
                case '+': return PLUS_INDEX;
                case '-': return MINUS_INDEX;
                case '*': return TIMES_INDEX;
                case '/': return DIVIDE_INDEX;
                }

        case OPEN_BRACKET_TYPE:
                return OPEN_BRACKET_INDEX;

        case CLOSED_BRACKET_TYPE:
                return CLOSED_BRAKCET_INDEX;

        case SPECIAL_TYPE:
                return SPECIAL_INDEX;

        default:
                return TERM_ERROR_INDEX;

        }

        return TERM_ERROR_INDEX;
}

enum VAR_INDEX term_index(token *tkn) {(void) tkn; return VAR_ERROR_INDEX;}

void push_chars_stack(stack *stk, const char* str)
{
        if (!stk || !str)
                return;

        token tkn;

        do {
                token_set_character(&tkn, *str);
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
