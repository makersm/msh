//
// Created by somin on 15. 12. 7.
//

#ifndef SHELL_GROUP_H
#define SHELL_GROUP_H
#include <stdbool.h>
#include "queue.h"

typedef struct IndivCommand {
    msh_queue *command;
    bool isBack;
    bool isPipe;
} msh_group;

msh_group * groupInit();

#endif //SHELL_GROUP_H
