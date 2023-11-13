#include "evaluate.h"
#include "token.h"
#include <stdio.h>

static long eval_S(tree_node_t *);
static long eval_E(tree_node_t *);

static long eval_node(tree_node_t *node)
{
        token t = *(token *) tree_data(node);

        if (t.type == VARIABLE_TYPE) {
                switch (t.d.character) {
                case 'S':
                        return eval_S(node);
                case 'E':
                        return eval_E(node);
                default:;
                }
        }

        if (t.type == INT_TYPE) {
                return t.d.integer;
        }

        return 0;
}

static long eval_S(tree_node_t *S)
{
        if (!S)
                return 0;
        return eval_E(tree_child(S, 0));
}

static long eval_E(tree_node_t *E)
{
        tree_node_t *node;

        // TWO CASES: E -> NUM; E -> NUM OP NUM; E->E

        array_t *children = tree_children(E);
        if (array_size(children) == 1) {
                node = tree_child(E, 0);
                token t = *(token *) tree_data(node);
                if (t.type == INT_TYPE)
                        return t.d.integer;
                return eval_E(node);
        }

        tree_node_t *left_E  = tree_child(E, 0);
        tree_node_t *op      = tree_child(E, 1);
        tree_node_t *right_E = tree_child(E, 2);

        token t = *(token *) tree_data(op);

        switch (t.d.character) {
        case '+':
                return eval_node(left_E) + eval_node(right_E);
        case '-':
                return eval_node(left_E) - eval_node(right_E);
        case '*':
                return eval_node(left_E) * eval_node(right_E);
        case '/':
                return eval_node(left_E) / eval_node(right_E);
        default:
                return 0;
        }
}

bool evaluate(tree_node_t *ast, int *result)
{
        if (!ast)
                return false;
        *result = eval_node(ast);
        return true;
}
