#include <stdbool.h>

#include "s21_matrix.h"

int s21_create_matrix(int rows, int columns, matrix_t *result){
    if (rows <= 0 || columns <= 0){
        return INVALID_MATRIX;
    }
    
    res_code res = OK;

    result->rows = rows;
    result->columns = columns;

    result->matrix = (double **)malloc(rows * sizeof(double *));

    if (result->matrix == NULL) res = INVALID_MATRIX;

    for (int i = 0; (i < rows) && (res == OK); i++){
        result->matrix[i] = (double *)malloc(columns * sizeof(double));

        if(result->matrix[i] == NULL)
            res = INVALID_MATRIX;    
    }

    return res;
}

void s21_remove_matrix(matrix_t *A){
    for (int i = 0; i < A->rows; i++){
        free(A->matrix[i]);
    }

    free(A->matrix);

    A->rows = 0;
    A->columns = 0;
}

int s21_eq_matrix(matrix_t *A, matrix_t *B){
    if (A->rows != B->rows) return false;
    if (A->columns != B->columns) return false;

    bool res = true;

    for (int i = 0; (i < A->rows) && (res == true); i++){
        for (int j = 0; (j < A->columns) && (res == true); j++){
            if (A->matrix[i][j] != B->matrix[i][j]) res = false;
        }
    }

    return res;
}