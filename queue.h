#ifndef QUEUE_H
#define QUEUE_H
/**
 * @file queue.h
 * @brief C89 header-only implementation of an arbitrarily expanding queue.
 * @author veganaiZe <veganaiZe@pm.me>
 */

#include <stdlib.h>  /* free(), malloc(), NULL */

#include "list.h"


typedef struct Queue {
    LinkedListNode * front;
    LinkedListNode * back;
} Queue;


Queue *
new_Queue(const void * head)
{
    LinkedListNode * list_node = (LinkedListNode *) head;

    Queue * queue = (Queue *) malloc(sizeof (Queue));
    if (! queue) { return NULL; }

    queue->front = list_node;
    if (list_node) {
        while (list_node->next) { list_node = list_node->next; }
    }
    queue->back = list_node;

    return queue;
}


int
queue_push_pointer(Queue * queue, const void * element)
{
    LinkedListNode * new_node = NULL;

    if (! queue) { return 0; }  /* Falsey: No queue */
    new_node = (LinkedListNode *) new_VoidListNode(element);
    if (! new_node) { return 0; }  /* Falsey: Unable to allocate node */

    if (queue->back) { queue->back->next = new_node; }
    queue->back = new_node;

    /* On push to empty queue, make front = back */
    if (! queue->front) { queue->front = new_node; }

    return 1;  /* Truthy: Success */
}


int
queue_push_int(Queue * queue, const int element)
{
    LinkedListNode * new_node = NULL;

    if (! queue) { return 0; }  /* Falsey: No queue */
    new_node = (LinkedListNode *) new_IntListNode(element);
    if (! new_node) { return 0; }  /* Falsey: Unable to allocate node */

    if (queue->back) { queue->back->next = new_node; }
    queue->back = new_node;

    /* On push to empty queue, make front = back */
    if (! queue->front) { queue->front = new_node; }

    return 1;  /* Truthy: Success */
}


int
queue_pop_pointer(Queue * queue, const void ** popped_element)
{
    LinkedListNode * old_node = NULL;

    if (! queue) { return 0; }  /* Falsey: No queue */
    if (popped_element && queue->front) {
        *popped_element = ((VoidListNode *) queue->front)->element;
    } else if (popped_element && ! queue->front) {
        *popped_element = NULL;
        return 0;  /* Falsey: No elements left */
    }

    if (queue->front) {
        old_node = queue->front;
        queue->front = queue->front->next;
        free(old_node);
    }
    /* Essential: check if (modified) `queue->front` is (now) null */
    if (! queue->front) {
        queue->back = NULL;
    }

    return 1;  /* Truthy: Element popped */
}


int
queue_pop_int(Queue * queue, int * popped_element)
{
    LinkedListNode * old_node = NULL;

    if (! queue) { return 0; }  /* Falsey: No queue */

    if (popped_element && queue->front) {
        *popped_element = ((IntListNode *) queue->front)->val;
    } else if (popped_element && ! queue->front) {
        popped_element = NULL;
        return 0;  /* Falsey: No elements left */
    }

    if (queue->front) {
        old_node = queue->front;
        queue->front = queue->front->next;
        free(old_node);
    }
    /* Essential: check if (modified) `queue->front` is (now) null */
    if (! queue->front) {
        queue->back = NULL;
    }

    return 1;  /* Falsey: Element popped */
}


void
queue_delete(Queue * queue)
{
    if (! queue) { return; }
    list_delete(queue->front);
    free(queue);
}


#endif  /* QUEUE_H */
