#include "s21_matrix.h"

void fill_matrix(matrix_t *result, double value){
    if (result == NULL) exit(EXIT_FAILURE);
    if (result->matrix == NULL) exit(EXIT_FAILURE);

    for (int i = 0; i < result->rows; i++){
        for (int j = 0; j < result->columns; j++){
            result->matrix[i][j] = value;
        }
    }
}

void fill_matrix_rand(matrix_t *result, double entropy){
    if (result == NULL) exit(EXIT_FAILURE);
    if (result->matrix == NULL) exit(EXIT_FAILURE);

    for (int i = 0; i < result->rows; i++){
        for (int j = 0; j < result->columns; j++){
            int sign = rand() %2 ? 1 : -1;
            result->matrix[i][j] = (double)rand() / ((double)RAND_MAX + 1) * entropy * sign;
        }
    }
}

void print_matrix(matrix_t *A){
    for (int i = 0; i < A->rows; i++){
        for (int j = 0; j < A->columns; j++){
            printf("%lf ", A->matrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

bool is_doubles_eq(double a, double b, double EPS){
    return (fabs(a - b) < EPS);
}

double accuracy_check(double a, double EPS){
    return fabs(a) < EPS ? 0 : a;
}

void split_to_sub(matrix_t A, matrix_t *sub, int row_to_skip, int col_to_skip){
    int row = 0, col = 0;
    for (int i = 0; i < A.rows; i++){
        if (i != row_to_skip){
            for (int j = 0; j < A.columns; j++){
                if (j != col_to_skip){;
                    sub->matrix[row][col] = A.matrix[i][j]; 
                    col++;     
                }
            }
            row++;
            col = 0;
        }
    }
}