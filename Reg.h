//
// Created by somin on 15. 12. 7.
// this crazy regex makes me mad, I got lots of headache..

#ifndef SHELL_REG_H
#define SHELL_REG_H
#include <regex.h>
#include <stdbool.h>
#include "data/queue.h"

static const char *semi_p = "([^;\'\"]+)(([\"][^\"]*[\"])*([\'][^\']*[\'])*([^;]+)*)*";
static const char *pipe_p = "([^|\'\"]+)(([\"][^\"]*[\"])*([\'][^\']*[\'])*([^|]+)*)*";
static const char *back_p = ".+[&]( |\t)*$";
static const char *space = ".+( |\t).+";

bool regCommands(char *individual, const char *p);
void regAndSpiltCommands(char [], const char *, msh_queue *);

#endif //SHELL_REG_H
