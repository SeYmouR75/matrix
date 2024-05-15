#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define ACCURACY 1e-6

typedef enum res_code {
  OK = 0,
  INVALID_MATRIX = 1,
  INVALID_CALCULATIONS = 2
} res_code;

typedef struct matrix_struct {
  double **matrix;
  int rows;
  int columns;
} matrix_t;

// core

int s21_create_matrix(int rows, int columns, matrix_t *result);
void s21_remove_matrix(matrix_t *A);
int s21_eq_matrix(matrix_t *A, matrix_t *B);
int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_mult_number(matrix_t *A, double number, matrix_t *result);
int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_transpose(matrix_t *A, matrix_t *result);
int s21_calc_complements(matrix_t *A, matrix_t *result);
int s21_determinant(matrix_t *A, double *result);
int s21_inverse_matrix(matrix_t *A, matrix_t *result);

// utils

void fill_matrix(matrix_t *result, double value);
void fill_matrix_rand(matrix_t *result, double entropy);
void print_matrix(matrix_t *A);
bool is_doubles_eq(double a, double b, double EPS);
double accuracy_check(double a, double EPS);
void split_to_sub(matrix_t A, matrix_t *sub, int row_to_skip, int col_to_skip);