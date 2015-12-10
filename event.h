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
    INPUTMAN_READ_INPUT,
    INPUTMAN_PARSE_DONE,
};

#endif //SHELL_EVENT_H
