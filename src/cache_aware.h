#ifndef CACHE_AWARE_H
#define CACHE_AWARE_H

void cache_aware_matrix_mult(int N, const double A[N][N], const double B[N][N],
                             double C[N][N], int block_size);

#endif
