//
// Created by somin on 15. 12. 11.
//

#include <bits/pthreadtypes.h>
#include <pthread.h>
#include <assert.h>
#include "executemanager.h"

void msh_executeman_init(pthread_t *thread_handle) {
    int is_created = pthread_create(thread_handle, NULL, msh_executeman_run, NULL);
    pthread_join(*thread_handle, 0);
    assert(is_created == 0);
}

static void msh_executeman_run() {

}
void msh_executeman_execute_input(msh_event e) {

}