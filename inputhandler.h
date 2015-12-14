//
// Created by somin on 15. 12. 9.
//

#ifndef SHELL_INPUTMANAGER_H
#define SHELL_INPUTMANAGER_H

#include "event.h"
#include "data/queue.h"

void msh_inputhan_run();

char*msh_inputhan_read_input();
void msh_inputhan_parse_input(char *);
void msh_inputhan_pump_event(msh_event);

void msh_inputhan_prompt();
void msh_inputhan_set_groups(msh_queue *);

#endif //SHELL_INPUTMANAGER_H
