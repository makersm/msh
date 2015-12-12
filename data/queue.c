//
// Created by somin on 15. 12. 7.
//

#include "queue.h"


msh_queue *que_create(void) {
    msh_queue *queue;

    queue = (msh_queue *) malloc(sizeof(msh_queue));
    if (queue) {
        queue->front = NULL;
        queue->rear = NULL;
        queue->count = 0;
    }
    return queue;
}

msh_queue *que_destroy(msh_queue *queue) {
    NODE *node_temp;

    if (queue) {
        while (queue->front != NULL) {
            free(queue->front->data);
            node_temp = queue->front;
            queue->front = queue->front->link;
            free(node_temp);
        } //while
        free(queue);
    } //if
    return NULL;
}

//insert node in rear
bool que_enqueue(msh_queue *queue, void *data_in) {
    NODE *node_new;

    if (!(node_new = (NODE *) malloc(sizeof(NODE))))
        return false;

    node_new->data = data_in;
    node_new->link = NULL;

    if (queue->count == 0) queue->front = node_new;
    else queue->rear->link = node_new;

    (queue->count)++;
    queue->rear = node_new;
    return true;
}

//bring front node and delete
bool que_dequeue(msh_queue *queue, void **data_out) {
    NODE *node_del;

    if (!queue->count) return false;

    *data_out = queue->front->data;
    node_del = queue->front;
    if (queue->count == 1) queue->rear = queue->front = NULL;
    else queue->front = queue->front->link;

    --(queue->count);
    free(node_del);

    return true;
}

bool que_front(msh_queue *queue, void **data_out) {
    if (!queue->count) return false;
    else {
        *data_out = queue->front->data;
        return true;
    }
}

bool que_rear(msh_queue *queue, void **data_out) {
    if (!queue->count) return false;
    else {
        *data_out = queue->rear->data;
        return true;
    }
}

bool que_is_empty(msh_queue *queue) {
    return (queue->count == 0);
}

bool que_is_full(msh_queue *queue) {
    NODE *node_temp;

    node_temp = (NODE *) malloc(sizeof(*(queue->rear)));
    if (node_temp) {
        free(node_temp);
        return false;
    }
    return true;
}

int que_count(msh_queue *queue) {
    return queue->count;
}

