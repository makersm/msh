//
// Created by somin on 15. 12. 13.
//

#include "blockingqueue.h"
#include <pthread.h>

static sem_t msh_blockingqueue_sem;

void msh_blockingqueue_init(msh_blockingqueue *bq) {
    sem_init(&msh_blockingqueue_sem, 0, 0);
    bq->queue = que_create();
}

void msh_blockingqueue_offer(msh_blockingqueue* bq, msh_event* event) {
    //mutex for several threads
    static pthread_mutex_t offer_mutex;

    pthread_mutex_lock(&offer_mutex);
    //for take method
    que_enqueue(bq->queue, event);
    sem_post(&msh_blockingqueue_sem);

    pthread_mutex_unlock(&offer_mutex);
}

msh_event* msh_blockingqueue_take(msh_blockingqueue* bq) {
    static pthread_mutex_t take_mutex;

    pthread_mutex_lock(&take_mutex);

    void *tmp;
    sem_wait(&msh_blockingqueue_sem);
    que_dequeue(bq->queue, &tmp);

    pthread_mutex_unlock(&take_mutex);

    msh_event *tt = (msh_event*)tmp;
    return tt;
}