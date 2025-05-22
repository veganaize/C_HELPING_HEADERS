#include <assert.h>  /* assert()     */
#include <stdio.h>   /* puts(), NULL */

#include "queue.h"


int
main(void)
{
    const int one   = 1;
    const int two   = 2;
    const int three = 3;
    int result = -1;
    int value  = -1;
    int i = 0;
    Queue * queue = new_Queue(NULL);
    const void * popped_pointer = NULL;

    /* Test empty queue */
    assert( NULL == queue->front );
    assert( NULL == queue->back );

    /* Queue pointer tests */
    queue_push_pointer(queue, &one);
    queue_push_pointer(queue, &two);
    queue_push_pointer(queue, &three);

    queue_pop_pointer(queue, &popped_pointer);
    assert( &one == popped_pointer );
    queue_pop_pointer(queue, &popped_pointer);
    assert( &two == popped_pointer );
    queue_pop_pointer(queue, &popped_pointer);
    assert( &three == popped_pointer );
    queue_pop_pointer(queue, &popped_pointer);
    assert( NULL == popped_pointer );

    /* Queue integer tests */
    queue_push_int(queue, one);
    queue_push_int(queue, 2);

    result = queue_pop_int(queue, &value);
    assert( 1 == result );
    assert( 1 == value );

    queue_pop_int(queue, &value);
    assert( 1 == result );
    assert( 2 == value );

    result = queue_pop_int(queue, &value);
    assert( 0 == result );  /* Falsey because queue empty */
    assert( 2 == value );  /* Unaltered `value` because queue empty */

    free(queue);
    queue = NULL;

    /* Queue from list of integers */
    queue = new_Queue(list_ints_new(5, 1,2,3,4,5));
    for (i=1; queue_pop_int(queue, &value); ++i) {
        assert( i == value );
    }

    queue_delete(queue);
    queue = NULL;

    queue = new_Queue(NULL);
    queue_delete(queue);
    queue = NULL;

    queue_delete(NULL);

    /* If this doesn't appear then something went wrong. */
    puts("All queue tests pass.");
    return 0;
}
