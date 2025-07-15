#include "cache_aware.h"

void cache_aware_matrix_mult(int N, const double A[N][N], const double B[N][N],
                             double C[N][N], int block_size) {

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
}
