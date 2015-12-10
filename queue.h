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
} QUEUE;

QUEUE *que_create(void);
QUEUE *que_destroy(QUEUE *queue);
bool que_dequeue(QUEUE *queue, void **data_out);
bool que_enqueue(QUEUE *queue, void *data_in);
bool que_front(QUEUE *queue, void **data_out);
bool que_rear(QUEUE *queue, void **data_out);
int que_count(QUEUE *queue);
bool que_is_empty(QUEUE *queue);
bool que_is_full(QUEUE *queue);

#endif //SHELL_QUEUE_H
