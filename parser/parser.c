#include "parser.h"
#include <queue.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>

// const char *parse_table[NUM_VAR][NUM_TERM] = {
// /*        +,    -,    *,    /,     (,     ),   num,   $ */
// /* S */ {"!",  "!",  "!",  "!",   "E",   "!",  "E",  "@"},
// /* E */ {"!",  "!",  "!",  "!",  "(E)",  "!",  "nT", "!"},
// /* T */ {"+E", "-E", "*E", "/E",  "!",   "@",  "!",  "@"}
// };

enum VAR_INDEX variable_index(char c)
{
        switch (c) {
        case 'S': return S_INDEX;
        case 'E': return E_INDEX;
        case 'T': return T_INDEX;
        default:  return VAR_ERROR_INDEX;
        }
}

enum TERM_INDEX terminal_index(token tkn)
{        
        switch (tkn.type) {
        case INT_TYPE:
                return INT_INDEX;

        case OPERATION_TYPE:
                switch (tkn.d.character) {
                case '+': return PLUS_INDEX;
                case '-': return MINUS_INDEX;
                case '*': return TIMES_INDEX;
                case '/': return DIVIDE_INDEX;
                default:  return TERM_ERROR_INDEX;
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
}

void push_chars_stack(stack__t *stk, const char *str)
{
        if (!stk || !str)
                return;

        size_t str_len = strlen(str);
        size_t i;
        for (i = 0; i < str_len; i++)
                stack_push(stk, (char *) str + str_len - 1 - i);
}

bool token_equal_char(token tkn, char c)
{
        if (tkn.type == INT_TYPE)
                return c == 'n';

        return tkn.d.character == c;
}

enum TERMINAL_VARIABLE is_char_terminal_variable(char c)
{
        int i;
        for (i = 0; i < NUM_TERMINALS; i++) {
                if (c == terminals[i])
                        return TERMINAL;
        }

        for (i = 0; i < NUM_VARIABLES; i++) {
                if (c == variables[i])
                        return VARIABLE;
        }

        return INVALID;
}

tree_node_t *parse_tokens(array_t *tokens)
{
        if (!tokens)
                return false;

        token t;
        token_set_character(&t, '$');
        array_append(tokens, &t);

        stack__t *stk = stack_init(sizeof (char));
        stack__t *var_stack = stack_init(sizeof (tree_node_t *));

        push_chars_stack(stk, "S$");

        token tree_token;

        tree_node_t *node;
        tree_node_t *node_tmp;

        char var_buff[100];
        memset(var_buff, 0, 100);

        token tkn_input;
        char tkn_stack;
        int var_index;
        int term_index;
        bool accepted = false;
        const char *rule;
        enum TERMINAL_VARIABLE tkn_stack_type;

        token_set_character(&tree_token, 'S');
        tree_node_t *syntax_tree_root = tree_node(&tree_token, sizeof tree_token, NULL);
        stack__t *node_stack = stack_init(sizeof (tree_node_t *));
        stack_push(node_stack, &syntax_tree_root);

        size_t input_index = 0;
        while (true) {

                tkn_input = *(token *) array_get(tokens, input_index);
                tkn_stack = *(char *) stack_pop(stk);

                tkn_stack_type = is_char_terminal_variable(tkn_stack);

                if (tkn_stack_type == TERMINAL) {
                        if (token_equal_char(tkn_input, tkn_stack)) {
                                // GOOD, continue

                                if (tkn_stack == '$') {
                                        accepted = true;
                                        break;
                                }

                                input_index++;
                        } else {
                                // BAD, end program
                                if (tkn_input.type == INT_TYPE)
                                        printf("ERROR: Invalid input, terminals do not match {%lld, %c}\n", tkn_input.d.integer, tkn_stack);
                                else
                                        printf("ERROR: Invalid input, terminals do not match {%c, %c}\n", tkn_input.d.character, tkn_stack);
                                break;
                        }
                } else

                if (tkn_stack_type == VARIABLE) {
                        var_index = variable_index(tkn_stack);
                        term_index = terminal_index(tkn_input);

                        if (var_index == VAR_ERROR_INDEX) {
                                printf("ERROR: invalid variable {%c}\n", tkn_stack);
                                break;
                        }

                        if (term_index == TERM_ERROR_INDEX) {
                                if (tkn_input.type == INT_TYPE)
                                        printf("ERROR: invalid terminal {%lld}\n", tkn_input.d.integer);
                                else
                                        printf("ERROR: invalid terminal {%c}\n", tkn_input.d.character);
                                break;
                        }

                        rule = parse_table[var_index][term_index];
                        node = *(tree_node_t **) stack_pop(node_stack);

                        // token abc = *(token *) tree_get_data(node);
                        // printf("node: %c\n", abc.d.character);

                        const char *tmp = rule;
                        do {
                                token_set_character(&tree_token, *tmp);
                                node_tmp = tree_node(&tree_token, sizeof tree_token, NULL);

                                tree_add_child(node, node_tmp);
                                
                                if (is_char_terminal_variable(*tmp) == VARIABLE) {
                                        stack_push(var_stack, &node_tmp);
                                }

                        } while (*++tmp);

                        while (!stack_empty(var_stack)) {
                                stack_push(node_stack, stack_pop(var_stack));
                        }

//                      if rule is empty, error
                        if (!strcmp(rule, "!")) {
                                if (tkn_input.type == INT_TYPE)
                                        printf("ERROR: table cell invalid {%lld, %c}\n", tkn_input.d.integer, tkn_stack);
                                else
                                        printf("ERROR: table cell invalid {%c, %c}\n", tkn_input.d.character, tkn_stack);
                                break;
                        }

//                      if rule is not epsilon, push onto stack
                        if (strcmp(rule, "@"))
                                push_chars_stack(stk, rule);
                }
        }

        stack_destroy(node_stack);
        stack_destroy(stk);
        stack_destroy(var_stack);

        if (!accepted) {
                tree_destroy(syntax_tree_root);
                return NULL;
        }

        return syntax_tree_root;
}
