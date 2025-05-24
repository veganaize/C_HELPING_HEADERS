#ifndef TREE_H
#define TREE_H
/**
 * @file tree.h
 * @brief C89 header-only implementation of a binary tree.
 * @author veganaiZe <veganaiZe@pm.me>
 */

#include <stdlib.h>  /* malloc(), free(), NULL        */

#include "queue.h"


/**
 * Effective super type for binary tree nodes.
 */
typedef struct BinaryTreeNode {
    struct BinaryTreeNode * left;
    struct BinaryTreeNode * right;
} BinaryTreeNode;


/**
 * LeetCode compatible binary tree node.
 * LeetCode doesn't include the typedef portion, only `struct TreeNode`.
 * LeetCode doesn't have child pointers first. (Bad for generic routines.)
 */
typedef struct TreeNode {
    struct TreeNode * left;
    struct TreeNode * right;
    int val;
} IntTreeNode;


typedef struct VoidTreeNode {
    struct VoidTreeNode * left;
    struct VoidTreeNode * right;
    int * val;
} VoidTreeNode;


#define new_TreeNode new_IntTreeNode
IntTreeNode *
new_IntTreeNode(int val)
{
    IntTreeNode * tree_node = (IntTreeNode *) malloc(sizeof (IntTreeNode));
    if (! tree_node) { return NULL; }

    tree_node->val = val;
    tree_node->left = NULL;
    tree_node->right = NULL;

    return tree_node;
}


IntTreeNode *
tree_ints_bfs_new(IntListNode * list)
{
    int result = 0;
    IntTreeNode * tree_top = NULL;
    BinaryTreeNode * tree_node = NULL;
    Queue * tree_node_queue = new_Queue(NULL);

    tree_top = new_IntTreeNode(list->val);
    if (! tree_top) { return NULL; }

    result = queue_push_pointer(tree_node_queue, tree_top);
    if (! result) { return NULL; }

    while (queue_pop_pointer(tree_node_queue, (const void**) &tree_node)) {
        if (list->next) {
            list = list->next;
            tree_node->left = (BinaryTreeNode *) new_IntTreeNode(list->val);
            queue_push_pointer(tree_node_queue, tree_node->left);
        } else { tree_node->left = NULL; }

        if (list->next) {
            list = list->next;
            tree_node->right = (BinaryTreeNode *) new_IntTreeNode(list->val);
            queue_push_pointer(tree_node_queue, tree_node->right);
        } else { tree_node->right = NULL; }
    }

    queue_delete(tree_node_queue);
    tree_node_queue = NULL;
    return tree_top;
}


int
tree_traverse_bfs(IntTreeNode * tree_node, char * result_string)
{
    int node_count = 0;
    Queue * queue = NULL;

    if (! tree_node) { return 0; }

    queue = new_Queue(NULL);
    if (! queue) { return -1; }

    queue_push_pointer(queue, tree_node);
    while(queue_pop_pointer(queue, (const void**) &tree_node)) {
        *result_string++ = (char) (tree_node->val + 48);
        ++node_count;
        if (tree_node->left) { queue_push_pointer(queue, tree_node->left); }
        if (tree_node->right) { queue_push_pointer(queue, tree_node->right); }
    }

    return node_count;
}


void
tree_delete(IntTreeNode * tree_node)
{
    if (tree_node->left) { tree_delete(tree_node->left); }
    if (tree_node->right) { tree_delete(tree_node->right); }
    free(tree_node);
}


#endif  /* TREE_H */
