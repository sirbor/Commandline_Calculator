#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX_CMD_LEN 1024
#define VERSION "0.1.0"

#define COLOR_GREEN "\033[0; 32m"
#define COLOR_RED "\033[0; 31m"
#define COLOR_RESET "\033[0m"

typedef struct 
{
  double value;
  bool is_error;
  char error_msg[256];

} CalculationResult;

#endif
