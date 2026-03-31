#include "cleanup.h"
#include "ops/memory_ops.h"
#include "utils/utils.h"

void cleanup_calculator() {
    // CONCEPT: Free all dynamic memory at program exit (Day 14)
    log_info("Cleaning up resources...");
    memory_cleanup();
}
