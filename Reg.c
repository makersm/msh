//
// Created by somin on 15. 12. 7.
//
#include <string.h>
#include "Reg.h"

bool regCommands(char *individual, const char *pattern) {
    regex_t reg;
    regcomp(&reg, pattern, REG_EXTENDED | REG_NEWLINE);
    const char *ind = individual;
    regmatch_t pmatch;
    bool re_val = regexec(&reg, ind, 1, &pmatch, 0)==0 ? true : false;
    regfree(&reg);
    return re_val;
}

void regAndSpiltCommands(char command[], const char *pattern, msh_queue *commands) {
    char *cmd = (char *)malloc(sizeof(char)*strlen(command)+1);
    strcpy(cmd, command);

    regex_t reg;
    regcomp(&reg, pattern, REG_EXTENDED | REG_NEWLINE);

    const int n_matches = 1;
    regmatch_t pmatch[n_matches];

    while (1) {
        int nomatch = regexec(&reg, cmd, n_matches, pmatch, 0);
        if (nomatch) {
            regfree(&reg);
            return;
        }
        int i;
        for (i = 0; i < n_matches; i++) {
            unsigned long start, finish;
            if (pmatch[i].rm_so == -1) {
                break;
            }
            start = pmatch[i].rm_so + (cmd - command);
            finish = pmatch[i].rm_eo + (cmd - command);
            if (i == 0) {
                int j;
                char *tmp = (char *) malloc(sizeof(char) * (finish - start));

                for (j = 0; j < finish - start; j++) {
                    tmp[j] = (command + start)[j];
                }
                tmp[j] = '\0';
                que_enqueue(commands, tmp);
            }
        }
        cmd += pmatch[0].rm_eo;
    }
}
