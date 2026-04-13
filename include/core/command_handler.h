#ifndef COMMAND_HANDLER_H
#define COMMAND_HANDLER_H

#include "common.h"

// CONCEPT: Typedef for function pointers (Day 23)
typedef void (*CommandHandlerFunc)(const char *args);

// CONCEPT: Command dispatch and input parsing
void handle_command(const char *command_str);
CommandType identify_command(const char *cmd_name);

// Functions to handle each category
void handle_basic(const char *args);
void handle_scientific(const char *args);
// ... placeholders for others ...

#endif // COMMAND_HANDLER_H
