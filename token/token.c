#include "token.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

enum TOKEN_TYPE token_type_char(char c)
{
        if (	c == '0' ||
		c == '1' ||
		c == '2' ||
		c == '3' ||
		c == '4' ||
		c == '5' ||
		c == '6' ||
		c == '7' ||
		c == '8' ||
		c == '9')
		return INT_TYPE;

	if (	c == '+' ||
		c == '-' ||
		c == '*' ||
		c == '/')
		return OPERATION_TYPE;

	if (c == '(')
		return OPEN_BRACKET_TYPE;
	
	if (c == ')')
		return CLOSED_BRACKET_TYPE;
	
	if (c == '$')
		return SPECIAL_TYPE;
	
	return ERROR_TYPE;
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

// void token_append(token *tkn, char c)
// {
//         if (!tkn) return;
//         char ch[2] = {c, '\0'};
//         strcat(tkn->buff, ch);
// }
