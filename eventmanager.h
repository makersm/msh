//
// Created by somin on 15. 12. 10.
//

#include <bits/pthreadtypes.h>
#include <stdlib.h>
#include "event.h"
#include "data/blockingqueue.h"

#ifndef SHELL_EVENTMANAGER_H
#define SHELL_EVENTMANAGER_H

void msh_eventman_init(pthread_t *);

static void msh_eventman_dispatch_event(msh_event);

static void msh_eventman_run();

typedef struct eventman_class {
    msh_blockingqueue events;
    pthread_t *thread_handle;
} eventman_class;

eventman_class *msh_eventman_instance();

void msh_eventman_request(msh_event *event);


#endif //SHELL_EVENTMANAGER_H
