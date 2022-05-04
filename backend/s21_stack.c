#include "s21_stack.h"

void push(struct Num **list, double val) {
    struct Num *temp = malloc(sizeof(struct Num));
    temp->value = val;
    temp->next = *list;
    *list = temp;
}

void push_sim(struct Sim **list, char sim) {
    struct Sim *temp = malloc(sizeof(struct Sim));
    temp->sim = sim;
    temp->next = *list;
    *list = temp;
    if (sim == '(' || sim == ')' || sim =='x') {
        temp->priority = 0;
    } else {
        temp->priority = prior(sim);
    }
}

struct Sim* top(struct Sim **list) {
    return *list;
}

struct Num* top_num(struct Num **list) {
    return *list;
}

double pop(struct Num **list) {
    double res = (*list)->value;
    struct Num *temp = *list;
    *list = (*list)->next;
    free(temp);
    return res;
}

char pop_sim(struct Sim **list) {
    char res = (*list)->sim;
    struct Sim *temp = *list;
    *list = (*list)->next;
    free(temp);
    return res;
}

int prior(char sim) {
    int prior;
    if (sim == '(' || sim == 'x') {
        prior = 0;
    } else if (sim == '+' || sim == '-') {
        prior = 1;
    } else if (sim == '*' || sim == '/' || sim =='m') {
        prior = 3;
    } else if (sim == '^') {
        prior = 3;
    } else {
        prior = 4;
    }
    return prior;
}

