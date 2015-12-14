//
// Created by somin on 15. 12. 9.
//

#ifndef SHELL_EVENT_H
#define SHELL_EVENT_H

typedef struct msh_event {
    int event_types;
    void *data;
} msh_event;

enum msh_event_types {
    INPUTHAN_READ_INPUT,
    INPUTHAN_PARSE_DONE,
    INPUTHAN_BACK_INPUT,
};

#endif //SHELL_EVENT_H
