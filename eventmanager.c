//
// Created by somin on 15. 12. 10.
//

#include <pthread.h>
#include <assert.h>
#include "eventmanager.h"
#include "executemanager.h"

void msh_eventman_init(pthread_t* thread_handle) {
    msh_blockingqueue_init();
    int is_created = pthread_create(thread_handle, NULL, msh_eventman_run, NULL);
    assert(is_created == 0);
}

static void msh_eventman_run() {
    for (; ;)
        msh_eventman_dispatch_event(*msh_blockingqueue_take(&(msh_eventman_instance()->events)));
}

void msh_eventman_dispatch_event(msh_event e) {
    pthread_t execute_handle;

    switch (e.event_types) {
        case INPUTMAN_PARSE_DONE:
            msh_executeman_init(&execute_handle, e);
            break;
        default:
            break;
        
    }
}

void msh_eventman_request(msh_event *event) {
    msh_blockingqueue_offer(&msh_eventman_instance()->events, event);
    return;
}


/*
 * Request flow
 *
 * e.g.) when inputman input done case
 * 1. inputman calls eventman.instace() for eventman variable ==> local_eventman = Eventman.instance()
 * 2. inputman calls inputman's eventman method 'requst' ==> local_eventman.request(msh_event(INPUT_DONE));
 * 3. inputman continues its main loop
 */