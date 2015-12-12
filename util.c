//
// Created by somin on 15. 12. 13.
//

#include "util.h"
#include <pthread.h>
#include <limits.h>
#include <unistd.h>

void endless_sleep() {
    for (; ;) {
        sleep(INT_MAX);
    }
}

void main_never_die() {
    pthread_t sleeper;
    pthread_create(&sleeper, NULL, endless_sleep, NULL);
    pthread_join(sleeper, NULL);
}