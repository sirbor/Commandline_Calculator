#ifndef MEMORY_OPS_H
#define MEMORY_OPS_H

#include "common.h"

// CONCEPT: Static state management - persistent "memory" (Day 14)
void memory_store(double val);
CalculationResult memory_recall();
void memory_cleanup();

#endif // MEMORY_OPS_H
