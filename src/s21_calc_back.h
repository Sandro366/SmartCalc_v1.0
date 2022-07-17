#ifndef SRC_S21_CALC_BACK_H_
#define SRC_S21_CALC_BACK_H_

#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  double value;
  char type;
} lexema;

typedef struct stack {
  lexema value;
  struct stack *next;
} stack_t;

double s21_calculator(char *string, double x);
int Maths(stack_t **num, stack_t **operation, lexema value);
void reading(char *src, stack_t **num, stack_t **operation, double x);
lexema read_number(char *src, int *index);
lexema read_function(char *src, int *index);
void error_memory();
void stack_push(stack_t **stack, lexema value);
lexema stack_pop(stack_t **stack);
lexema stack_peek(stack_t **stack);
int stack_size(stack_t **stack);
void stack_free(stack_t **stack);
int getRang(char ch);

#endif  // SRC_S21_CALC_BACK_H_
