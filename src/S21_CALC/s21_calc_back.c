#include "s21_calc_back.h"

double s21_calculator(char *string, double x) {
  stack_t *num = NULL;
  stack_t *operation = NULL;
  reading(string, &num, &operation, x);
  double result = stack_peek(&num).value;
  stack_free(&num);
  stack_free(&operation);
  return result;
}

int Maths(stack_t **num, stack_t **operation, lexema value) {
  double a, b;
  a = stack_peek(num).value;
  stack_pop(num);
  if (stack_peek(operation).type == '+') {
    b = stack_peek(num).value;
    stack_pop(num);
    value.value = a + b;
    value.type = '0';
    stack_push(num, value);
    stack_pop(operation);
  } else if (stack_peek(operation).type == '-') {
    b = stack_peek(num).value;
    stack_pop(num);
    value.value = b - a;
    value.type = '0';
    stack_push(num, value);
    stack_pop(operation);
  } else if (stack_peek(operation).type == '^') {
    b = stack_peek(num).value;
    stack_pop(num);
    value.value = pow(b, a);
    value.type = '0';
    stack_push(num, value);
    stack_pop(operation);
  } else if (stack_peek(operation).type == '*') {
    b = stack_peek(num).value;
    stack_pop(num);
    value.value = a * b;
    value.type = '0';
    stack_push(num, value);
    stack_pop(operation);
  } else if (stack_peek(operation).type == '/') {
    b = stack_peek(num).value;
    stack_pop(num);
    value.value = b / a;
    value.type = '0';
    stack_push(num, value);
    stack_pop(operation);
  } else if (stack_peek(operation).type == '%') {
    b = stack_peek(num).value;
    stack_pop(num);
    value.value = fmod(b, a);
    value.type = '0';
    stack_push(num, value);
    stack_pop(operation);
  } else if (stack_peek(operation).type == 's') {
    value.value = sin(a);
    value.type = '0';
    stack_push(num, value);
    stack_pop(operation);
  } else if (stack_peek(operation).type == 'c') {
    value.value = cos(a);
    value.type = '0';
    stack_push(num, value);
    stack_pop(operation);
  } else if (stack_peek(operation).type == 't') {
    value.value = tan(a);
    value.type = '0';
    stack_push(num, value);
    stack_pop(operation);
  } else if (stack_peek(operation).type == 'i') {
    value.value = asin(a);
    value.type = '0';
    stack_push(num, value);
    stack_pop(operation);
  } else if (stack_peek(operation).type == 'o') {
    value.value = acos(a);
    value.type = '0';
    stack_push(num, value);
    stack_pop(operation);
  } else if (stack_peek(operation).type == 'a') {
    value.value = atan(a);
    value.type = '0';
    stack_push(num, value);
    stack_pop(operation);
  } else if (stack_peek(operation).type == 'q') {
    value.value = sqrt(a);
    value.type = '0';
    stack_push(num, value);
    stack_pop(operation);
  } else if (stack_peek(operation).type == 'l') {
    value.value = log(a);
    value.type = '0';
    stack_push(num, value);
    stack_pop(operation);
  } else if (stack_peek(operation).type == 'g') {
    value.value = log10(a);
    value.type = '0';
    stack_push(num, value);
    stack_pop(operation);
  }
  return 1;
}

void reading(char *src, stack_t **num, stack_t **operation, double xx) {
  int index = 0;
  char ch;
  lexema tmp = {0, 0};
  int flag_otric = 1;
  while ((ch = src[index]) != '\0') {
    if (ch == ' ') {
      index++;
      continue;
    }
    if (ch == 'X') {
      lexema temp_x = {xx, 0};
      stack_push(num, temp_x);
      index++;
      flag_otric = 0;
      continue;
    }
    if ((ch >= '0' && ch <= '9') || ((ch == '+' || ch == '-') && flag_otric == 1)) {
      stack_push(num, read_number(src, &index));
      flag_otric = 0;
      continue;
    }
    if (ch == 's' || ch == 'c' || ch == 't' || ch == 'a' || ch == 'l') {
      stack_push(operation, read_function(src, &index));
      continue;
    }
    if (ch == '+' || (ch == '-' && flag_otric == 0) || ch == '*' || ch == '/' ||
        ch == '^' || ch == 'm') {
      if (ch == 'm') {
        if (src[++index] == 'o' && src[++index] == 'd') {
          ch = '%';
        }
      }
      if (stack_size(operation) == 0) {
        tmp.type = ch;
        tmp.value = 0;
        stack_push(operation, tmp);
        index++;
        continue;
      }
      if (stack_size(operation) != 0 && getRang(ch) > getRang(stack_peek(operation).type)) {
        tmp.type = ch;
        tmp.value = 0;
        stack_push(operation, tmp);
        index++;
        continue;
      }
      if (stack_size(operation) != 0 && getRang(ch) <= getRang(stack_peek(operation).type)) {
        if (Maths(num, operation, tmp) == 0) {
          break;
        }
        continue;
      }
    }
    if (ch == '(') {
      flag_otric = 1;
      tmp.type = ch;
      tmp.value = 0;
      stack_push(operation, tmp);
      index++;
      continue;
    }
    if (ch == ')') {
      while (stack_peek(operation).type != '(') {
        if (Maths(num, operation, tmp) == 0) {
          break;
        } else {
          continue;
        }
      }
      stack_pop(operation);
      index++;
      continue;
    }
  }
  while (stack_size(operation) != 0) {
    if (Maths(num, operation, tmp) == 0) {
      break;
    } else {
      continue;
    }
  }
}

lexema read_function(char *src, int *index) {
    lexema result = {0, 0};
    char tmp[5] = "\0";
    int index_tmp = 0;
    char ch = src[*index];
    while (ch >= 'a' && ch <= 'z') {
      tmp[index_tmp++] = ch;
      *index += 1;
      ch = src[*index];
    }
    tmp[index_tmp] = '\0';
    if (!strcmp(tmp, "sin")) {
      result.type = 's';
    } else if (!strcmp(tmp, "cos")) {
      result.type = 'c';
    } else if (!strcmp(tmp, "tan")) {
      result.type = 't';
    } else if (!strcmp(tmp, "asin")) {
      result.type = 'i';
    } else if (!strcmp(tmp, "acos")) {
      result.type = 'o';
    } else if (!strcmp(tmp, "atan")) {
      result.type = 'a';
    } else if (!strcmp(tmp, "sqrt")) {
      result.type = 'q';
    } else if (!strcmp(tmp, "ln")) {
      result.type = 'l';
    } else if (!strcmp(tmp, "log")) {
      result.type = 'g';
    }
    return result;
}

lexema read_number(char *src, int *index) {
  lexema result = {0, 0};
  char tmp[256] = "\0";
  int index_tmp = 0;
  char ch = src[*index];
  while ((ch >= '0' && ch <= '9') || ch == '.') {
    tmp[index_tmp++] = ch;
    *index += 1;
    ch = src[*index];
  }
  tmp[index_tmp] = '\0';
  result.value = strtod(tmp, NULL);
  return result;
}

void error_memory() {
  fprintf(stderr, "%s", strerror(errno));
  exit(errno);
}

void stack_push(stack_t **stack, lexema value) {
  stack_t *tmp = malloc(sizeof(stack_t));
  if (tmp) {
    tmp->next = *stack;
    tmp->value = value;
    *stack = tmp;
  } else {
    error_memory();
  }
}

lexema stack_pop(stack_t **stack) {
  lexema value = {0, 0};
  if (*stack) {
    stack_t *out;
    out = *stack;
    *stack = (*stack)->next;
    value = out->value;
    free(out);
  } else {
    error_memory();
  }
  return value;
}

lexema stack_peek(stack_t **stack) {
  lexema value = {0, 0};
  value = (*stack)->value;
  return value;
}

int stack_size(stack_t **stack) {
  int size = 0;
  if (*stack) {
    size = 1;
    stack_t *tmp = *stack;
    while (tmp->next != NULL) {
      size++;
      tmp = tmp->next;
    }
  }
  return size;
}

void stack_free(stack_t **stack) {
  if (*stack) {
    stack_t *tmp = *stack;
    while ((*stack)->next != NULL) {
      *stack = (*stack)->next;
      free(tmp);
      tmp = *stack;
    }
    free(tmp);
  }
}

int getRang(char ch) {
  if (ch == 's' || ch == 'c' || ch == 't' || ch == 'g' || ch == 'i' ||
      ch == 'o' || ch == 'a' || ch == 'q' || ch == 'l')
    return 4;
  if (ch == '^') return 3;
  if (ch == '*' || ch == '/' || ch == '%') return 2;
  if (ch == '+' || ch == '-')
    return 1;
  else
    return 0;
}
// int main() {
//  stack_t *num = NULL;
//  stack_t *operation = NULL;
//  //char *tmp = "62 - 50*10";
//  char *tmp = "X * sin(2";
//  double x = 2;
//  reading(tmp, &num, &operation, x);
//  double result = stack_peek(&num).value;
//  printf("%f\n", result);
//  stack_free(&num);
//  stack_free(&operation);
//  return 0;
// }
