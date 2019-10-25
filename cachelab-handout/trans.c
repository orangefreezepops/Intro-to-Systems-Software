/*
 * Keegan Fouse
 * kdf11@pitt.edu
 * 4032113
Part B - Matrix Transposes
*/

/* 
 * trans.c - Natrix transpose B = A^T
 *
 * Each transpose function must have a prototype of the form:
 * void trans(int M, int N, int A[M][N], int B[N][M]);
 *
 * A transpose function is evaluated by counting the number of misses
 * on a 1 KiB direct mapped cache with a block size of 32 bytes.
 */ 
#include <stdio.h>
#include "support/cachelab.h"

int is_transpose(int M, int N, int A[M][N], int B[N][M]);
void transpose_32(int M, int N, int A[M][N], int B[N][M]);
void transpose_64(int M, int N, int A[M][N], int B[N][M]);

/* 
 * transpose_submit - This is the solution transpose function that you
 *     will be graded on for Part I of the assignment. Do not change
 *     the description string "Transpose submission", as the driver
 *     searches for that string to identify the transpose function to
 *     be graded. 
 */
char transpose_submit_desc[] = "Transpose submission";
void transpose_submit(int M, int N, int A[M][N], int B[N][M]) {
	if (N == 32 && M == 32){
		transpose_32(M, N, A, B);
	} else if (N == 64 && M == 64){
		transpose_64(M, N, A, B);
	}
}

/* 
 * You can define additional transpose functions below. We've defined
 * a simple one below to help you get started. 
 */ 

/* 
 * trans - A simple baseline transpose function, not optimized for the cache.
 */
char trans_desc[] = "Simple row-wise scan transpose";
void trans(int M, int N, int A[M][N], int B[N][M]) {
    int i, j, tmp;

    for (i = 0; i < M; i++) {
        for (j = 0; j < N; j++) {
            tmp = A[i][j];
            B[j][i] = tmp;
        }
    }
}

char trans_column_desc[] = "Simple Column-wise scan transpose";
void trans_column(int M, int N, int A[M][N], int B[N][M]){
	int i, j, temp;
	for (j = 0; j < M; j ++){
		for(i = 0; i < N; i ++){
			temp = A[i][j];
			B[j][i] = temp;
		}
	}
}
/*
 *helper methods for the submission
 */ 
char transpose_32_desc[] = "Transpose Function for 32x32 matrix";
void transpose_32(int M, int N, int A[M][N], int B[N][M]){
	int blockRow, blockColumn, r, c, blockSize, temp, diagonal;
	blockSize = 8;
	//iterate across blocks column wise
	for (blockColumn = 0; blockColumn < N; blockColumn += blockSize){
		for (blockRow = 0; blockRow < N; blockRow += blockSize){
			//iterate through each block row wise
			for (r = blockRow; r < blockRow + blockSize; r++){
				for (c = blockColumn; c < blockColumn + blockSize; c++){
					if (r != c){
						B[c][r] = A[r][c];
					} else {
						temp = A[r][c];
						diagonal = r;
					}
				}
				if (blockRow == blockColumn){
					B[diagonal][diagonal] = temp;
				}
			}
		}
	}
}

char transpose_64_desc[] = "Transpose function for 64x64 matrix";
void transpose_64(int M, int N, int A[M][N], int B[N][M]){
	int blockRow, blockColumn, r, c, blockSize, temp, diagonal;
	blockSize = 4;
	//iterate across blocks column wise
	for (blockColumn = 0; blockColumn < N; blockColumn += blockSize){
		for (blockRow = 0; blockRow < N; blockRow += blockSize){
			//iterate through each block row wise
			for (r = blockRow; r < blockRow + blockSize; r++){
				for (c = blockColumn; c < blockColumn + blockSize; c++){
					if (r != c){
						B[c][r] = A[r][c];
					} else {
						temp = A[r][c];
						diagonal = r;
					}
				}
				if (blockRow == blockColumn){
					B[diagonal][diagonal] = temp;
				}
			}
		}
	}
}

/*
 * registerFunctions - This function registers your transpose
 *     functions with the driver.  At runtime, the driver will
 *     evaluate each of the registered functions and summarize their
 *     performance. This is a handy way to experiment with different
 *     transpose strategies.
 */
void registerFunctions() {
    /* Register your solution function */
    registerTransFunction(transpose_submit, transpose_submit_desc);

    /* Register any additional transpose functions */
    registerTransFunction(trans, trans_desc);
    registerTransFunction(trans_column, trans_column_desc);
    registerTransFunction(transpose_32, transpose_32_desc);
    registerTransFunction(transpose_64, transpose_64_desc);
	
}

/* 
 * is_transpose - This helper function checks if B is the transpose of
 *     A. You can check the correctness of your transpose by calling
 *     it before returning from the transpose function.
 */
int is_transpose(int M, int N, int A[M][N], int B[N][M]) {
    int i, j;

    for (i = 0; i < M; i++) {
        for (j = 0; j < N; ++j) {
            if (A[i][j] != B[j][i]) {
                return 0;
            }
        }
    }
    return 1;
}

