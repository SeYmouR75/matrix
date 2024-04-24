#include "s21_matrix.h"

int s21_create_matrix(int rows, int columns, matrix_t *result){
    int flag = 0;
    if(rows <= 0 || columns <= 0){
        flag = INVALID_MATRIX;
    }
    result->matrix = NULL;
    result->rows = rows;
    result->columns = columns;
    result->matrix = (double **)malloc(rows * sizeof(double *));
    if(result->matrix == NULL)
        flag = INVALID_MATRIX;
    for(int i = 0; i < rows; i++){
        result->matrix[i] = (double *)malloc(columns * sizeof(double));
        if(result->matrix[i] == NULL)
            flag = INVALID_MATRIX;    
    }

    return flag;
}