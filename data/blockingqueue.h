//
// Created by somin on 15. 12. 13.
//

#ifndef MSH_BLOCKINGQUEUE_H
#define MSH_BLOCKINGQUEUE_H

#include <semaphore.h>
#include "queue.h"
#include "../event.h"

typedef struct bq {
    msh_queue *queue;
}msh_blockingqueue;

void msh_blockingqueue_init(msh_blockingqueue*);
void msh_blockingqueue_offer(msh_blockingqueue*, msh_event*);
msh_event* msh_blockingqueue_take(msh_blockingqueue*);
#endif //MSH_BLOCKINGQUEUE_H
