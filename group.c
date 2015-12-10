//
// Created by somin on 15. 12. 7.
//
#include "group.h"

Group* groupInit() {
    Group *g = (Group*)malloc(sizeof(Group));
    g->isPipe = false;
    g->isBack = false;
}

void switchGroup(Group *group) {
    switch (group->isPipe){
        case true:
            printf("True"); break;
        case false:
            printf("false"); break;
        default:
            break;
    }
    if(!group->isBack) {
        waitInput();
    }

}