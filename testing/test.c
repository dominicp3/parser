#include "lexer.h"
#include "token.h"
#include "parser.h"
#include "ast.h"
#include "evaluate.h"

#include <array.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <tree.h>

void print_tokens(array_t *tokens)
{
	if (!tokens) return;
	token t;
	printf("[");
	for (size_t i = 0; i < array_size(tokens); i++) {
		t = *(token *) array_get(tokens, i);

		if (t.type == INT_TYPE)
			printf("{%lld, %d}", t.d.integer, t.type);
		else
			printf("{%c, %d}", t.d.character, t.type);

		if (i + 1 < array_size(tokens))
			printf(", ");
	}
	printf("]\n");
}

void print_syntax_array(array_t *arr)
{
	if (!arr)
		return;
	// printf("[");
	token t;
	tree_node_t *node;
	for (size_t i = 0; i < array_size(arr); i++) {
		node = *(tree_node_t **) array_get(arr, i);
		t = *(token *) tree_data(node);
		
		if (t.type == INT_TYPE)
			printf("%lld", t.d.integer);
		else
			printf("%c", t.d.character);

		if (i + 1 < array_size(arr))
			printf("  ");
	}

	printf("\n");
}

void lexer_arg(const char *str)
{
	array_t *tokens = string_to_tokens(str);
	print_tokens(tokens);
	array_destroy(tokens);
}

void parse_arg(const char *str)
{
	// array_t *arr;
	array_t *tokens = string_to_tokens(str);
	tree_node_t *root = syntax_tree(tokens);
	array_destroy(tokens);
	// printf("%s\n", root ? "PASSED" : "REJECTED");

	// arr = tree_postorder(root);
	// print_syntax_array(arr);
	// array_destroy(arr);

	abstract_syntax_tree(root);

	// arr = tree_postorder(root);
	// print_syntax_array(arr);
	// array_destroy(arr);

	int x = 0;
	evaluate(root, &x);
	printf("%d\n", x);

	tree_destroy(root);
}

int main(int argc, char *argv[])
{
	if (argc != 2) {
		printf("usage: %s [string]\n", argv[0]);
		return 1;
	}

	printf("Input: %s\n\n", argv[1]);

	// test_args(argv[1]);
	parse_arg(argv[1]);

	return 0;
}
