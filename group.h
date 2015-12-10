//
// Created by somin on 15. 12. 7.
//

#ifndef SHELL_GROUP_H
#define SHELL_GROUP_H
#include <stdbool.h>
#include "queue.h"

typedef struct IndivCommand {
    QUEUE *command;
    bool isBack;
    bool isPipe;
} Group;

Group* groupInit();

void switchGroup(Group *);
#endif //SHELL_GROUP_H
