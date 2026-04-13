#ifndef HISTORY_OPS_H
#define HISTORY_OPS_H

#include "common.h"

// CONCEPT: Queue-based history storage (Day 26)
void history_add(double val);
void history_show(void);
void history_clear(void);
CalculationResult history_last(void);
void history_cleanup(void);

#endif // HISTORY_OPS_H
