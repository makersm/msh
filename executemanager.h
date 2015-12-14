//
// Created by somin on 15. 12. 11.
//

#include "event.h"
#include "data/group.h"

#ifndef SHELL_EXECUTEMANAGER_H
#define SHELL_EXECUTEMANAGER_H

void msh_executeman_init(pthread_t*, msh_event);
static void msh_executeman_run(msh_event*);
void msh_executeman_switch_input_type(msh_event);
void msh_executeman_pump_event(msh_event);


#endif //SHELL_EXECUTEMANAGER_H
