#ifndef SRC_BUILD_S21_STACK_H_
#define SRC_BUILD_S21_STACK_H_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Num {
    struct Num *next;
    double value;
};

struct Sim {
    struct Sim *next;
    char sim;
    int priority;
};

void push(struct Num **list, double val);
void push_sim(struct Sim **list, char sim);
struct Sim* top(struct Sim **list);
struct Num* top_num(struct Num **list);
double pop(struct Num **list);
char pop_sim(struct Sim **list);
int prior(char sim);

#endif  //  SRC_BUILD_S21_STACK_H_
