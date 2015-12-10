//
// Created by somin on 15. 12. 9.
//

#ifndef SHELL_INPUTMANAGER_H
#define SHELL_INPUTMANAGER_H

#include "event.h"
#include "queue.h"

static void msh_inputman_run();

void msh_inputman_init(pthread_t*);
char*msh_inputman_read_input();
msh_event msh_inputman_parse_input(char *);
void msh_inputman_pump_event(msh_event);

void msh_inputman_prompt();
void msh_inputman_set_groups(QUEUE *);

#endif //SHELL_INPUTMANAGER_H
