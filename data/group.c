//
// Created by somin on 15. 12. 7.
//
#include <malloc.h>
#include "group.h"

msh_group * groupInit() {
    msh_group *g = (msh_group *)malloc(sizeof(msh_group));
    g->isPipe = false;
    g->isBack = false;
}

}