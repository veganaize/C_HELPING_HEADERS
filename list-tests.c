#include <assert.h>  /* assert()     */
#include <stdio.h>   /* puts(), NULL */

#include "list.h"


int
main(void)
{
    struct ListNode * list_node = NULL;
    IntListNode     * int_node  = NULL;
    VoidListNode    * void_node = NULL;
    const int value = 42;

    /* Test LeetCode ListNode */
    list_node = new_LeetListNode(value);
    assert( 42 == list_node->val );
    assert( NULL == list_node->next );
    list_delete(list_node); list_node = NULL;

    /* Test IntListNode */
    int_node = new_IntListNode(value);
    assert( 42 == int_node->val );
    assert( NULL == int_node->next );
    list_delete(int_node); int_node = NULL;

    int_node = list_ints_new(5, 1,2,3,4,value);
    assert( 1 == int_node->val );
    assert( 2 == int_node->next->val );
    assert( 42 == int_node->next->next->next->next->val );
    assert( NULL == int_node->next->next->next->next->next );
    list_delete(int_node); int_node = NULL;

    /* Test VoidListNode */
    void_node = new_VoidListNode(&value);
    assert( 42 == *(int*)void_node->element );
    list_delete(void_node); void_node = NULL;

    /* If this doesn't appear then something went wrong. */
    puts("All list tests pass.");
    return 0;
}
