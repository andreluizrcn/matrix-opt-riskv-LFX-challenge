#define _POSIX_C_SOURCE 199309L
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "cache_aware.h"
#include "naive.h"

#define N 1024
#define BS 32 /* block size */

double A[N][N], B[N][N], C[N][N];

void fill_empty_matrix(double M[N][N]) {
  for (int i = 0; i < N; i++)
    for (int j = 0; j < N; j++)
      M[i][j] = rand() % 10;
}

void zero_matrix(double M[N][N]) {
  for (int i = 0; i < N; i++)
    for (int j = 0; j < N; j++)
      M[i][j] = 0.0;
}

void print_to_file(double naive_time, double cache_time, int block_size) {
  FILE *f = fopen("benchmark", "w");

  if (f == NULL) {
    perror("Failed to open benchmark.csv");
    return;
  }

  // Write CSV header and results
  fprintf(f, "Method, Time(s) ,  BlockSize\n");
  fprintf(f, "Naive: ,  %.6f   ,\n", naive_time);
  fprintf(f, "Cache-Aware:  ,  %.6f  ,  %d\n", cache_time, block_size);

  fclose(f);
}

double time_in_seconds() {
  struct timespec t;
  clock_gettime(CLOCK_MONOTONIC, &t);
  return t.tv_sec + t.tv_nsec * 1e-9;
}

int main() {

  fill_empty_matrix(A);
  fill_empty_matrix(B);

  /* naive */
  zero_matrix(C);
  double t1 = time_in_seconds();
  naive_matrix_mult(N, A, B, C);
  double t2 = time_in_seconds();

  /* cache-aware */
  zero_matrix(C);
  double t3 = time_in_seconds();
  cache_aware_matrix_mult(N, A, B, C, BS);
  double t4 = time_in_seconds();
  print_to_file(t2 - t1, t4 - t3, BS);

  return 0;
}
