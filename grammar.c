#include "grammar.h"

enum TERM_INDEX var_index(token *tkn)
{
        if (!tkn)
                return TERM_ERROR_INDEX;
        
        switch (tkn->type) {
        case INT_TYPE:
                return INT_INDEX;

        case OPERATION_TYPE:
                switch (tkn->buff[0]) {
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
