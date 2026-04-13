#ifndef MEMORY_OPS_H
#define MEMORY_OPS_H

#include "common.h"

// CONCEPT: Static state management - persistent "memory" (Day 14)
void memory_store(const char *name, double val);
CalculationResult memory_recall(const char *name);
void memory_list(void (*callback)(const char*, double));
void memory_cleanup(void);

#endif // MEMORY_OPS_H
