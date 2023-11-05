#include "token.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

enum TOKEN_TYPE token_type_char(char c)
{
	switch (c) {
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':
		return INT_TYPE;

	case '+':
	case '-':
	case '*':
	case '/':
		return OPERATION_TYPE;

	case '(':
		return OPEN_BRACKET_TYPE;

	case ')':
		return CLOSED_BRACKET_TYPE;

	case '$':
		return SPECIAL_TYPE;
	
	case 'S':
	case 'E':
	case 'T':
		return VARIABLE_TYPE;

	default:
		return ERROR_TYPE;
	}
}

void token_clear(token *tkn)
{
        if (!tkn) return;
        memset(&tkn->d, 0, sizeof(tkn->d));
        tkn->type = DEFAULT_TYPE;
}

void token_set_character(token *tkn, char c)
{
        if (!tkn) return;

	tkn->d.character = c;
	tkn->type = token_type_char(c);
}

void token_set_integer(token *tkn, int64_t n)
{
	if (!tkn) return;

	tkn->d.integer = n;
	tkn->type = INT_TYPE;
}
