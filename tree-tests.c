#include <assert.h>  /* assert()       */
#include <stdio.h>   /* puts(), NULL   */
#include <string.h>  /* strcmp(), NULL */

#include "tree.h"


int
main(void)
{
    IntTreeNode * tree = NULL;
    char char_buffer[512] = { 0 };
    int node_count = 0;

    tree = tree_ints_bfs_new(list_ints_new(7, 4,2,7,1,3,6,9));
    node_count = tree_traverse_bfs(tree, char_buffer);
    assert( 7 == node_count );
    assert( 0 == strcmp(char_buffer,"4271369") );

    tree_delete(tree);
    while (node_count) { char_buffer[--node_count] = 0; }

    tree = tree_ints_bfs_new(list_ints_new(3, 1,2,3));
    node_count = tree_traverse_bfs(tree, char_buffer);
    assert( 3 == node_count );
    assert( 0 == strcmp(char_buffer,"123") );

    tree_delete(tree);
    while (node_count) { char_buffer[--node_count] = 0; }

    tree = NULL;
    node_count = tree_traverse_bfs(tree, char_buffer);
    assert( 0 == node_count );
    assert( 0 == strcmp(char_buffer, "") );

    /* If this doesn't appear then something went wrong. */
    puts("All tree tests pass.");
    return 0;
}
