//
// Created by somin on 15. 12. 6.
// this queue will be store split commands and IndivCommands

#ifndef SHELL_QUEUE_H
#define SHELL_QUEUE_H
#include <stdbool.h>
#include <malloc.h>

typedef struct node {
    void *data;
    struct node *link;
} NODE;

typedef struct queue {
    NODE *front;
    NODE *rear;
    int count;
} msh_queue;

msh_queue *que_create(void);
msh_queue *que_destroy(msh_queue *queue);
bool que_dequeue(msh_queue *queue, void **data_out);
bool que_enqueue(msh_queue *queue, void *data_in);
bool que_front(msh_queue *queue, void **data_out);
bool que_rear(msh_queue *queue, void **data_out);
int que_count(msh_queue *queue);
bool que_is_empty(msh_queue *queue);
bool que_is_full(msh_queue *queue);

#endif //SHELL_QUEUE_H
