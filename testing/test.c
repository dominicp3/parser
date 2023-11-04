#include "lexer.h"
#include "token.h"
#include "parser.h"

#include <array.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void print_tokens(array_t *tokens)
{
	if (!tokens) return;
	token t;
	printf("[");
	for (size_t i = 0; i < array_size(tokens); i++) {
		t = *(token *)array_get(tokens, i);

		if (t.type == INT_TYPE)
			printf("{%lld, %d}", t.d.integer, t.type);
		else
			printf("{%c, %d}", t.d.character, t.type);

		if (i + 1 < array_size(tokens))
			printf(", ");
	}
	printf("]\n");
}

void lexer_arg(const char *str)
{
	array_t *tokens = string_to_tokens(str);
	print_tokens(tokens);
	array_destroy(tokens);
}

void parse_arg(const char *str)
{
	array_t *tokens = string_to_tokens(str);
	char *outcome = parse_tokens(tokens) ? "PASSED" : "REJECTED";
	printf("%s\n", outcome);
	array_destroy(tokens);
}

int main(int argc, char *argv[])
{
	// printf("%ld\n", __STDC_VERSION__);
	if (argc != 2) {
		printf("usage: %s [string]\n", argv[0]);
		return 1;
	}

	// test_args(argv[1]);
	parse_arg(argv[1]);

	return 0;
}
