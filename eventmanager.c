//
// Created by somin on 15. 12. 10.
//

#include <pthread.h>
#include "eventmanager.h"
#include "executemanager.h"

void msh_eventman_init() {
    pthread_mutex_init(&mutex, NULL);
}
static void msh_eventman_send_event(msh_event e) {
    pthread_mutex_lock(&mutex);
    switch (e.event_types) {
        case INPUTMAN_PARSE_DONE:
            msh_executeman_execute_input(e);

    }
    pthread_mutex_unlock(&mutex);
}