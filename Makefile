# CONCEPT: Makefile for modular C development
CC = gcc
# CONCEPT: Compiler flags for quality and debugging
# -Wall, -Wextra: Show most common warnings
# -Werror: Treat warnings as errors (production quality)
# -std=c99: Use C99 standard as per README
# -g: Include debugging symbols for GDB
# -I.: Include current directory in search path
CFLAGS = -Wall -Wextra -Werror -std=c99 -g -I.
LIBS = -lm

# Project target name
TARGET = calculator

# CONCEPT: Object file compilation for separate translation units
# We will add more object files as we develop the modules
OBJS = main.o command_handler.o ops/basic_ops.o ops/scientific_ops.o ops/memory_ops.o ops/statistical_ops.o ops/converter_ops.o ops/graphical_ops.o ops/calculus_ops.o ops/solver_ops.o ops/extra_ops.o ops/complex_ops.o ops/financial_ops.o ops/programming_ops.o evaluation.o data_structs/linked_list.o data_structs/stack.o data_structs/bst.o data_structs/queue.o data_structs/graph.o initialization.o cleanup.o utils/utils.o utils/signals.o

# Default rule
all: $(TARGET)

# Link the executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS) $(LIBS)

# Compile C source files to object files
%.o: %.c common.h
	$(CC) $(CFLAGS) -c $< -o $@

# CONCEPT: Clean rule for build maintenance
clean:
	rm -f $(TARGET) $(OBJS)

# CONCEPT: Valgrind for memory leak detection
valgrind: $(TARGET)
	valgrind --leak-check=full --show-leak-kinds=all ./$(TARGET)

.PHONY: all clean valgrind
