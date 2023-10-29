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

		if (token_type_char(*s) == INT_TYPE) {

			int64_t n = 0;
			do {
				n *= 10;
				n += *s - '0';
			} while (token_type_char(*++s) == INT_TYPE);

			token_set_integer(&tkn, n);
			s--;
		} else {
			token_set_character(&tkn, *s);
		}

		array_append(tokens, &tkn);
	} while (*++s);

	return tokens;
}
