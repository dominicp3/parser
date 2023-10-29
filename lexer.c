#include "token.h"
#include <stdio.h>
#include <array.h>
#include <stdbool.h>

array *string_to_tokens(const char *s)
{
	if (!s)
		return NULL;

	array *tokens = array_init(sizeof(token), NULL, 0);
	token tkn;

	do {
		if (*s == ' ' || *s == '\0')
			continue;

		token_clear(&tkn);
		tkn.type = token_type_char(*s);

		if (token_type_char(*s) == INT_TYPE) {
			while (token_type_char(*s) == INT_TYPE)
				token_append(&tkn, *s++);
			s--;
		} else {
			token_append(&tkn, *s);
		}

		array_append(tokens, &tkn);
	} while (*++s);

	return tokens;
}
