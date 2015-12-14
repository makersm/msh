//
// Created by somin on 15. 12. 13.
//

#include "util.h"
#include "event.h"
#include "data/blockingqueue.h"
#include "eventmanager.h"
#include <pthread.h>
#include <limits.h>
#include <unistd.h>
char* msh_util_time_stamp() {
    time_t t = time(NULL);
    char re_val[1024];
    sprintf(re_val, "%ld", t);
    return re_val;
}

void msh_util_endless_sleep() {
    for (; ;) {
        sleep(INT_MAX);
    }
}

void msh_util_main_never_die() {
    pthread_t sleeper;
    pthread_create(&sleeper, NULL, msh_util_endless_sleep, NULL);
    pthread_join(sleeper, NULL);
}

void msh_util_start_input() {
    msh_event event;
    event.event_types = INPUTHAN_READ_INPUT;
    event.data = NULL;
    msh_eventman_request(&event);
}