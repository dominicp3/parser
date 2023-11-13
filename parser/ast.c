#include <tree.h>
#include <array.h>
#include "token.h"
#include <stdio.h>

static bool remove_T(tree_node_t *syntax_tree)
{
        if (!syntax_tree)
                return false;

        array_t *postorder = tree_postorder(syntax_tree);
        array_t *children;

        tree_node_t *node;
        token node_token;

        size_t i;
        for (i = 0; i < array_size(postorder); i++) {                
                node = *(tree_node_t **) array_get(postorder, i);
                node_token = *(token *) tree_data(node);

                if (node_token.type == VARIABLE_TYPE && node_token.d.character == 'T') {                
                        children = tree_children(node);

                        if (array_size(children) == 1) {
                                // ONLY CHILD, (AKA EPSILON)
                                tree_remove_subtree(node);
                                tree_destroy(node);
                        } else {
                                // T HAS CHILDREN OP, E
                                tree_node_t *E_top = tree_parent(node);

                                tree_remove_subtree(node);
                                tree_node_t *op = *(tree_node_t **) array_get(children, 0);
                                tree_node_t *E = *(tree_node_t **) array_get(children, 1);

                                tree_add_child(E_top, op);
                                tree_add_child(E_top, E);

                                tree_destroy_node(node);
                        }
                }
        }

        array_destroy(postorder);
        return true;
}

static bool remove_brackets(tree_node_t *syntax_tree)
{
        if (!syntax_tree)
                return false;

        array_t *postorder = tree_postorder(syntax_tree);

        tree_node_t *node;
        token node_token;

        size_t i;

        for (i = 0; i < array_size(postorder); i++) {                
                node = *(tree_node_t **) array_get(postorder, i);
                node_token = *(token *) tree_data(node);

                if (node_token.type == OPEN_BRACKET_TYPE || node_token.type == CLOSED_BRACKET_TYPE) {
                        tree_remove_subtree(node);
                        tree_destroy(node);
                }
        }

        array_destroy(postorder);
        return true;
}

bool abstract_syntax_tree(tree_node_t *syntax_tree)
{
        return syntax_tree && remove_T(syntax_tree) && remove_brackets(syntax_tree);
}
