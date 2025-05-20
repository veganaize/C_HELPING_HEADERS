#ifndef LIST_H
#define LIST_H
/**
 * @file list.h
 * @brief C89 header-only implementation of singly-linked lists.
 * @author veganaiZe <veganaiZe@pm.me>
 */

#include <stdarg.h>  /* va_list, va_start(), va_arg(), va_end() */
#include <stdlib.h>  /* free(), malloc(), NULL */


/**
 * Effective super type for other node types.
 */
typedef struct LinkedListNode {
    struct LinkedListNode * next;
} LinkedListNode;


/**
 * LeetCode compatible linked list node.
 * LeetCode doesn't include typedef portions, only `struct ListNode`.
 * LeetCode doesn't have `next` pointer first. (Bad for generic routines.)
 */
typedef struct ListNode {
     struct ListNode * next;
     int val;
} IntListNode;


/**
 * General (void *) linked list node.
 */
typedef struct VoidListNode {
    struct VoidListNode * next;
    void * element;
} VoidListNode;


/**
 * Create a new linked list node, with an integer value.
 */
#define new_LeetListNode(x) new_IntListNode((x))
IntListNode *
new_IntListNode(int val)
{
    IntListNode * new_node = (IntListNode *) malloc(sizeof (IntListNode));
    if (! new_node) { return NULL; }

    new_node->next = NULL;
    new_node->val = val;
    return new_node;
}


/**
 * Create new linked list node, with a pointer element.
 */
VoidListNode *
new_VoidListNode(void * element)
{
    VoidListNode * new_node = (VoidListNode *) malloc(sizeof (VoidListNode));
    if (! new_node) { return NULL; }

    new_node->next = NULL;
    new_node->element = element;
    return new_node;
}


/**
 * Create linked list from list of integer value arguments.
 *
 * First argument is number of nodes in (rest of) list.
 */
IntListNode *
list_ints_new(size_t ints_count, ...)
{
    IntListNode * head = NULL;
    IntListNode * node = NULL;
    va_list int_values = NULL;

    va_start(int_values, ints_count);
    head = node = new_IntListNode(va_arg(int_values, int));
    while (--ints_count) {
        node->next = new_IntListNode(va_arg(int_values, int));
        node = node->next;
    }
    va_end(int_values);
    return head;
}


/**
 * Free entire linked list from memory, to avoid leaks.
 *
 * This only deletes linked list nodes, themselves.
 * It doesn't free any memory that list elements may point to.
 * Any other (non-node) objects pointed at must be freed manually, externally.
 */
void
list_delete(void * node)
{
    LinkedListNode * next = NULL;

    while(node != NULL) {
        next = ((LinkedListNode *) node)->next;
        free(node);
        node = next;
    }
}


#endif  /* LIST_H */
