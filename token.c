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
	
	return ERROR_TYPE;
}

void token_clear(token *tkn)
{
        if (!tkn) return;
        memset(tkn->buff, 0, 100);
        tkn->type = DEFAULT_TYPE;
}

void token_set(token *tkn, const char *s, enum TOKEN_TYPE t)
{
        if (!tkn) return;
        strcpy(tkn->buff, s);
        tkn->type = t;
}

void token_append(token *tkn, char c)
{
        if (!tkn) return;
        char ch[2] = {c, '\0'};
        strcat(tkn->buff, ch);
}
