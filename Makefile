# Compiler
CC = gcc

# Output binary name
OUT = benchmark.csv

# Source files (with proper path)
SRC = src/main.c src/naive.c src/cache_aware.c

# Object files derived from sources
OBJ = $(SRC:.c=.o)

## COMPILER FLAGS EXPLANATION:
# -O3              : Aggressive optimization (loop unrolling, inlining, etc.)
# -std=c11         : Use the C11 language standard
# -Wall            : Enable common warnings
# -Wextra          : Enable extra warning flags
# -ftree-vectorize : Enable auto-vectorization (SIMD)
# -fno-tree-vectorize : Disable vectorization for scalar comparison
# -DN=<value>      : Define matrix dimension N
# -DBLOCK=<value>  : Define block size for cache-aware multiplication
# -Isrc            : Add src/ to header search path

# Base compiler flags
CFLAGS = \
	-O3 \
	-std=c11 \
	-Wall \
	-Wextra

# Include header directory
CFLAGS += -Isrc

# Vectorization control (enable with `make VECTOR=1`)
ifdef VECTOR
	CFLAGS += -ftree-vectorize
else
	CFLAGS += -fno-tree-vectorize
endif


# Default target
all: $(OUT)


# Link step
$(OUT): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $@


# Compile step for each .c into .o
src/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@


# Clean up
clean:
	rm -f $(OUT) src/*.o

.PHONY: all clean

