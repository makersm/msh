//
// Created by somin on 15. 12. 7.
// this crazy regex makes me mad, I got lots of headache..

#ifndef SHELL_REG_H
#define SHELL_REG_H
#include <regex.h>
#include <stdbool.h>
#include "queue.h"

static const char *semi_p = "([^;\'\"]+)(([\"][^\"]*[\"])*([\'][^\']*[\'])*([^;]+)*)*";
static const char *pipe_p = "([^|\'\"]+)(([\"][^\"]*[\"])*([\'][^\']*[\'])*([^|]+)*)*";
static const char *back_p = ".+[&]( |\t)*$";

bool regCommands(char *individual, const char *p);
void regAndSpiltCommands(char [], const char *, QUEUE *);

#endif //SHELL_REG_H
