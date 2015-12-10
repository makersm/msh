//
// Created by somin on 15. 12. 10.
//

#include <bits/pthreadtypes.h>
#include "event.h"

#ifndef SHELL_EVENTMANAGER_H
#define SHELL_EVENTMANAGER_H
static pthread_mutex_t mutex;
void msh_eventman_init();
void msh_eventman_send_event(msh_event);
#endif //SHELL_EVENTMANAGER_H
