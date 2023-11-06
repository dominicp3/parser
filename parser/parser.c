#include "parser.h"
#include "token.h"
#include <stack.h>
#include <string.h>
#include <stdio.h>

static enum VAR_INDEX variable_index(char);
static enum TERM_INDEX terminal_index(token);
static void push_chars_stack(stack__t *, const char *);
static bool token_equal_char(token, char);
static enum TERMINAL_VARIABLE is_char_terminal_variable(char);

tree_node_t *syntax_tree(array_t *tokens)
{
        if (!tokens)
                return false;

        token dollar;
        token_set_character(&dollar, '$');
        array_append(tokens, &dollar);

        stack__t *parse_stack = stack_init(sizeof (char));
        push_chars_stack(parse_stack, "S$");

        stack__t *variable_stack = stack_init(sizeof (tree_node_t *));

        tree_node_t *node;
        tree_node_t *node_tmp;

        token token_input;
        char token_parse_stack;

        int var_index;
        int term_index;        

        bool accepted = false;

        const char *rule;
        const char *rule_tmp;

        enum TERMINAL_VARIABLE token_type;

        token tree_token;
        token_set_character(&tree_token, 'S');

        tree_node_t *syntax_tree = tree_node(&tree_token, sizeof tree_token, NULL);

        stack__t *node_stack = stack_init(sizeof (tree_node_t *));
        stack_push(node_stack, &syntax_tree);

        size_t input_index = 0;

        while (true) {
                token_input = *(token *) array_get(tokens, input_index);
                token_parse_stack = *(char *) stack_pop(parse_stack);

                token_type = is_char_terminal_variable(token_parse_stack);

                if (token_type == TERMINAL) {
                        if (token_equal_char(token_input, token_parse_stack)) {
                                // GOOD, continue

                                if (token_parse_stack == '$') {
                                        accepted = true;
                                        break;
                                }

                                input_index++;
                        } else {
                                // BAD, end program
                                if (token_input.type == INT_TYPE)
                                        printf("ERROR: Invalid input, terminals do not match {%lld, %c}\n", token_input.d.integer, token_parse_stack);
                                else
                                        printf("ERROR: Invalid input, terminals do not match {%c, %c}\n", token_input.d.character, token_parse_stack);
                                break;
                        }
                } else

                if (token_type == VARIABLE) {
                        var_index = variable_index(token_parse_stack);
                        term_index = terminal_index(token_input);

                        if (var_index == VAR_ERROR_INDEX) {
                                printf("ERROR: invalid variable {%c}\n", token_parse_stack);
                                break;
                        }

                        if (term_index == TERM_ERROR_INDEX) {
                                if (token_input.type == INT_TYPE)
                                        printf("ERROR: invalid terminal {%lld}\n", token_input.d.integer);
                                else
                                        printf("ERROR: invalid terminal {%c}\n", token_input.d.character);
                                break;
                        }

                        rule = parse_table[var_index][term_index];
                        node = *(tree_node_t **) stack_pop(node_stack);

                        rule_tmp = rule;
                        do {
                                token_set_character(&tree_token, *rule_tmp);
                                node_tmp = tree_node(&tree_token, sizeof tree_token, NULL);
                                tree_add_child(node, node_tmp);
                                
                                if (is_char_terminal_variable(*rule_tmp) == VARIABLE)
                                        stack_push(variable_stack, &node_tmp);
                        } while (*++rule_tmp);

                        while (!stack_empty(variable_stack))
                                stack_push(node_stack, stack_pop(variable_stack));

//                      if rule is empty, error
                        if (!strcmp(rule, "!")) {
                                if (token_input.type == INT_TYPE)
                                        printf("ERROR: table cell invalid {%lld, %c}\n", token_input.d.integer, token_parse_stack);
                                else
                                        printf("ERROR: table cell invalid {%c, %c}\n", token_input.d.character, token_parse_stack);
                                break;
                        }

//                      if rule is not epsilon, push onto stack
                        if (strcmp(rule, "@"))
                                push_chars_stack(parse_stack, rule);
                }
        }

        stack_destroy(node_stack);
        stack_destroy(parse_stack);
        stack_destroy(variable_stack);

        if (!accepted) {
                tree_destroy(syntax_tree);
                return NULL;
        }

        return syntax_tree;
}

static enum VAR_INDEX variable_index(char c)
{
        switch (c) {
        case 'S': return S_INDEX;
        case 'E': return E_INDEX;
        case 'T': return T_INDEX;
        default:  return VAR_ERROR_INDEX;
        }
}

static enum TERM_INDEX terminal_index(token tkn)
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

static void push_chars_stack(stack__t *stk, const char *str)
{
        if (!stk || !str)
                return;

        size_t str_len = strlen(str);
        size_t i;
        for (i = 0; i < str_len; i++)
                stack_push(stk, (char *) str + str_len - 1 - i);
}

static bool token_equal_char(token tkn, char c)
{
        if (tkn.type == INT_TYPE)
                return c == 'n';

        return tkn.d.character == c;
}

static enum TERMINAL_VARIABLE is_char_terminal_variable(char c)
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
