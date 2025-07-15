# Matrix Optimization for RISC-V - LFX Challenge

**Applicant:** Andre Luiz

A high-performance matrix multiplication implementation comparing naive and cache-aware approaches, with optional vectorization support for RISC-V architecture optimization.

## Overview

This project implements matrix multiplication (A × B = C) for square matrices using two different approaches:
- **Naive approach**: Standard triple-nested loop implementation
- **Cache-aware approach**: Loop tiling/blocking technique to improve cache locality

The program measures and compares performance between both methods, with optional compiler vectorization flags to demonstrate the impact of SIMD instructions.

## Features

- ✅ **Naive Matrix Multiplication**: Standard O(n³) implementation
- ✅ **Cache-Aware Matrix Multiplication**: Loop tiling with configurable block size
- ✅ **Performance Benchmarking**: Precise timing using `clock_gettime()`
- ✅ **Vectorization Support**: Compile-time flag to enable/disable SIMD optimization
- ✅ **CSV Output**: Results exported to `benchmark.csv` for analysis
- ✅ **Configurable Parameters**: Matrix size and block size via preprocessor definitions

## Performance Results

### With Vector Instructions (`make VECTOR=1`)
| Method      | Time(s)   | BlockSize |
|-------------|-----------|-----------|
| Naive       | 10.179695 | -         |
| Cache-Aware | 2.589908  | 32        |

**Speedup**: ~3.93x improvement with cache-aware approach

### Without Vector Instructions (`make`)
| Method      | Time(s)   | BlockSize |
|-------------|-----------|-----------|
| Naive       | 10.080521 | -         |
| Cache-Aware | 2.414282  | 32        |

**Speedup**: ~4.17x improvement with cache-aware approach

## Build Instructions

### Requirements
- GCC compiler with C11 support
- POSIX-compliant system (for `clock_gettime`)

### Compilation

```bash
# Default build (without vectorization)
make

# Build with vectorization enabled
make VECTOR=1

# Clean build artifacts
make clean
```

### Execution

```bash
# Run the benchmark
./matrix_benchmark

# View results
cat benchmark.csv
```

## Project Structure

```
matrix-opt-riskv-LFX-challenge/
├── src/
│   ├── main.c          # Main program and benchmarking logic
│   ├── naive.c         # Naive matrix multiplication implementation
│   ├── cache_aware.c   # Cache-aware matrix multiplication implementation
│   ├── naive.h         # Header for naive implementation
│   └── cache_aware.h   # Header for cache-aware implementation
├── Makefile            # Build configuration
├── benchmark.csv       # Generated performance results
└── README.md          # This file
```

## Algorithm Details

### Naive Approach
```c
// Standard triple-nested loop
for (i = 0; i < N; i++)
    for (j = 0; j < N; j++)
        for (k = 0; k < N; k++)
            C[i][j] += A[i][k] * B[k][j];
```

### Cache-Aware Approach (Loop Tiling)
```c
// Blocked/tiled loops for better cache locality with sum accumulation
for (int i0 = 0; i0 < N; i0 += block_size)
    for (int j0 = 0; j0 < N; j0 += block_size)
        for (int k0 = 0; k0 < N; k0 += block_size)
            for (int i = i0; i < i0 + block_size && i < N; i++)
                for (int j = j0; j < j0 + block_size && j < N; j++) {
                    double sum = 0.0;
                    for (int k = k0; k < k0 + block_size && k < N; k++)
                        sum += A[i][k] * B[k][j];
                    C[i][j] += sum;
                }
```

## Configuration

Default settings in `main.c`:
- **Matrix Size (N)**: 1024×1024
- **Block Size (BS)**: 32
- **Data Type**: `double`

To modify these values, edit the `#define` statements in `main.c`:
```c
#define N 1024    // Matrix dimension
#define BS 32     // Block size for cache-aware algorithm
```

## Compiler Optimizations

The Makefile includes several optimization flags:
- `-O3`: Aggressive optimization (loop unrolling, inlining)
- `-std=c11`: C11 language standard
- `-Wall -Wextra`: Enable comprehensive warnings
- `-ftree-vectorize`: Enable SIMD vectorization (when `VECTOR=1`)
- `-fno-tree-vectorize`: Disable vectorization (default)

## Performance Analysis

The cache-aware approach demonstrates significant performance improvements:
- **~4x speedup** over naive implementation
- **Better cache locality** through loop tiling
- **Reduced memory bandwidth** requirements
- **Consistent performance** across different system configurations

## Challenge Requirements

This implementation addresses all requirements from the LFX Port & Polish challenge:

- [x] Matrix multiplication (A × B = C) for square matrices
- [x] Naive implementation
- [x] Cache-aware implementation (loop tiling/blocking)
- [x] Performance measurement and comparison
- [x] **Bonus**: Vectorization control via compiler flags
- [x] **Bonus**: Public Git repository with code and benchmarks

## License

This project is developed as part of the LFX Mentorship Program challenge.

## Author

**Andre Luiz**  
LFX Challenge Applicant - Software Optimization for RISC-V
