#include "s21_matrix.h"

void s21_fill_matrix(matrix_t *result, double value){
    for(int i = 0; i < result->rows; i++){
        for(int j = 0; j < result->columns; j++){
            result->matrix[i][j] = value;
        }
    }
}