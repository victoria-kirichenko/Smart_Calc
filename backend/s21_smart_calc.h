#ifndef SRC_BACKEND_S21_SMART_CALC_H_
#define SRC_BACKEND_S21_SMART_CALC_H_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "s21_stack.h"

int check(char *str);
double readstr(char *str, double x);
double operation_one(double a, char sim);
double operation_two(double a, double b, char sim);

#endif  // SRC_BACKEND_S21_SMART_CALC_H_
