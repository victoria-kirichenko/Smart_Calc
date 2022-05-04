#include "s21_smart_calc.h"

int check(char* str) {
    int res = 1, cnt = 0, scob = 0;
    while (cnt != (int)strlen(str)) {
        if (str[cnt] == 'x' && cnt != 0 && cnt != (int)strlen(str)) {
            if (str[cnt-1] == ')' || str[cnt+1] == '(' || (str[cnt-1] <= '9' && str[cnt-1] >= '0') || (str[cnt+1] <= '9' && str[cnt+1] >= '0') 
            || str[cnt+1] == 's' || str[cnt+1] == 'c' || str[cnt+1] == 't' || str[cnt+1] == 'a' || str[cnt+1] == 'l' || str[cnt+1] == 'm' 
            || str[cnt+1] == 'i' || str[cnt+1] == 'o' || str[cnt+1] == 'q' || str[cnt+1] == 'n') {
                res = 0;
            }
        } else if ((str[cnt] == 'n' && str[cnt + 1] == '(' && str[cnt + 2] == '-')|| (str[cnt] == 'l' && str[cnt + 1] == '(' && str[cnt + 2] == '-')) {
            res = 0;
        } else if (str[cnt] == '.') {
            if (cnt == 0 || cnt == (int)(strlen(str) - 1)) {
                res = 0;
            } else {
                if ((str[cnt-1] >= '9' && str[cnt-1] <= '0') || (str[cnt+1] >= '9' && str[cnt+1] <= '0')) {
                    res = 0;
                }
            }
        } else if (str[cnt] == '+' || str[cnt] == '-' || str[cnt] == '*' || str[cnt] == '/' || str[cnt] == '^') {
            if (cnt == 0) {
                if (str[cnt] != '-') {
                    res = 0;
                } else if (str[cnt] == '-' && str[cnt + 1] <= '0' && str[cnt + 1] >= '9') {
                    res = 0;
                } else if (cnt == (int)(strlen(str) - 1)) {
                    res = 0;
                } else {
                    if ((str[cnt-1] != ')' && str[cnt-1] > '9' && str[cnt-1] < '0') || ((str[cnt+1] < '0' && str[cnt+1] > '9') || str[cnt+1] == 'm' ||
                    str[cnt+1] == '+' || str[cnt+1] == '-' || str[cnt+1] == '*' || str[cnt+1] == '/' || str[cnt+1] == '^')) {
                        res = 0;
                    }
                }
            }
        } else if (str[cnt] == ')') {
            scob -= 1;
            if (scob == -1) {
                res = 0;
            } 
            if (cnt != 0) {
                if (str[cnt-1] == '+' || str[cnt-1] == '/' || str[cnt-1] == '*' || str[cnt-1] == '-' || str[cnt-1] == '^' || str[cnt-1] == '(') {
                    res = 0;
                }
                if (str[cnt+1] == 's' || str[cnt+1] == 'c' || str[cnt+1] == 't' || str[cnt+1] == 'a' || str[cnt+1] == 'l' || str[cnt+1] == 'm' ||
                str[cnt+1] == 'i' || str[cnt+1] == 'o' || str[cnt+1] == 'q' || str[cnt+1] == 'n' ||
                (str[cnt+1] >= '9' && str[cnt+1] <='0')) {
                    res = 0;
                }
            }
             else {
                res = 0;
            }
        } else if (str[cnt] == '(') {
            scob += 1;
            if (cnt != (int)(strlen(str) - 1)) {
                if (str[cnt+1] == '+' || str[cnt+1] == '/' || str[cnt+1] == '*' || str[cnt+1] == '^' || str[cnt+1] == ')') {
                    res = 0;
                }
                if (str[cnt-1] <= '9' && str[cnt-1] >= '0') {
                    res = 0;
                }
            } else {
                res = 0;
            }
        } else if (str[cnt] == 's' || str[cnt] == 'c' || str[cnt] == 't' || str[cnt] == 'l' || str[cnt] == 'a' || str[cnt] == 'i' || str[cnt] == 'o'
            || str[cnt] == 'q' || str[cnt] == 'n') {
            if ((cnt != 0 && str[cnt-1] == ')') || (str[cnt-1] <= '9' && str[cnt-1] >= '0')) {
                res = 0;
            }
        } else if (str[cnt] == 'm') {
            if (cnt == 0 || cnt == (int)strlen(str)) {
                res = 0;
            } else if (cnt != 0 && cnt != (int)strlen(str) && (str[cnt-1] == '(' || str[cnt+1] == ')' || str[cnt-1] == '+' || str[cnt-1] == '/' || str[cnt-1] == '*' || str[cnt-1] == '-' || str[cnt-1] == '^' 
            || str[cnt + 1] == '+' || str[cnt + 1] == '/' || str[cnt + 1] == '*' || str[cnt + 1] == '-' || str[cnt + 1] == '^')) {
                res = 0;
            }
        }
        cnt++;
    }
    if (scob != 0) {
        res = 0;
    }
    return res;
}

double readstr(char* str, double x) {
    struct Num *Num = NULL;
    struct Sim *Sim = NULL;
    double res = 0, a, b;
    while (*str != '\0') {
        if ((*(str) <= '9' && *(str) >= '0') || *(str) == '.') {
            double num = strtod(str, &str);
            push(&Num, num);
        } else {
            char sim = *(str);
            if (sim == ')') {
                if (top(&Sim)->sim == '(') {
                    pop_sim(&Sim);
                    push(&Num, operation_one(pop(&Num), pop_sim(&Sim)));
                } else {
                    while (top(&Sim)->sim != '(') {
                        b = pop(&Num);
                        a = pop(&Num);
                        push(&Num, operation_two(a, b, pop_sim(&Sim)));
                    }
                    pop_sim(&Sim);
                }
            } else if (top(&Sim) == NULL) {
                if (top_num(&Num) == NULL && prior(sim) == 1) {
                    push(&Num, 0.0);
                }
                if (sim == 'x') {
                    push(&Num, x);
                } else {
                    push_sim(&Sim, sim);
                }
            } else if (prior(sim) > top(&Sim)->priority || sim == '(' || sim == 'x') {
                if (prior(sim) == 1 && *(str-1) == '(') {
                    push(&Num, 0.0);
                }
                if (sim == 'x') {
                    push(&Num, x);
                } else {
                    push_sim(&Sim, sim);
                }
            } else {
                while (top(&Sim) != NULL && prior(sim) <= top(&Sim)->priority) {
                    if (top(&Sim)->priority == 4) {
                        push(&Num, operation_one(pop(&Num), pop_sim(&Sim)));
                    } else {
                        b = pop(&Num);
                        a = pop(&Num);
                        push(&Num, operation_two(a, b, pop_sim(&Sim)));
                    }
                }
                push_sim(&Sim, sim);
            }
            str++;
        }
    }
    while(top(&Sim) != NULL) {
        if (top(&Sim)->priority == 4) {
            push(&Num, operation_one(pop(&Num), pop_sim(&Sim)));
        } else {
            b = pop(&Num);
            a = pop(&Num);
            push(&Num, operation_two(a, b, pop_sim(&Sim)));
        }
    }
    res = pop(&Num);
    return res;
}

double operation_one(double a, char sim) {
    double res;
    if (sim == 's') {
        res = sin(a);
    } else if (sim == 'c') {
        res = cos(a);
    } else if (sim == 't') {
        res = tan(a);
    } else if (sim == 'q') {
        res = sqrt(a);
    } else if (sim == 'i') {
        res = asin(a);
    } else if (sim == 'o') {
        res = acos(a);
    } else if (sim == 'a') {
        res = atan(a);
    } else if (sim == 'l') {
        res = log10(a);
    } else if (sim == 'n') {
        res = log(a);
    }
    return res;
}

double operation_two(double a, double b, char sim) {
    double res;
    if (sim == '+') {
        res = a + b;
    } else if (sim == '-') {
        res = a - b;
    } else if (sim == '*') {
        res = a * b;
    } else if (sim == '/') {
        res = a / b;
    } else if (sim == '^') {
        res = pow(a, b);
    } else if (sim == 'm') {
        res = fmod(a, b);
    }
    return res;
}
