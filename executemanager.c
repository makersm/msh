//
// Created by somin on 15. 12. 11.
//

#include <bits/pthreadtypes.h>
#include <pthread.h>
#include <assert.h>
#include "executemanager.h"
#include "eventmanager.h"

void msh_executeman_init(pthread_t *thread_handle, msh_event e) {
    int is_created = pthread_create(thread_handle, NULL, msh_executeman_run, (void*)&e);
    assert(is_created == 0);
}

static void msh_executeman_run(msh_event e) {
    msh_executeman_execute_input(e);
    msh_executeman_pump_event(e);
}

void msh_executeman_execute_input(msh_event e) {
    msh_group *commands = (msh_group *)e.data;
}

void msh_executeman_pump_event(msh_event e) {
    msh_eventman_dispatch_event(e);
}
