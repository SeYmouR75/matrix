#include "s21_test_matrix.h"

static int rows_A[] = {5, 3, 2, 5, 7, 5, 1, 2};
static int cols_A[] = {3, 4, 1, 5, 4, 6, 3, 2};
static int rows_B[] = {3, 4, 1, 5, 4, 6, 3, 2};
static int cols_B[] = {1, 4, 2, 6, 4, 2, 2, 2};

START_TEST(mult_matrix_test) {
  matrix_t A, B, actual, expected;

  s21_create_matrix(rows_A[_i], cols_A[_i], &A);
  s21_create_matrix(rows_B[_i], cols_B[_i], &B);

  fill_matrix_rand(&A, rand() / 1000000);
  fill_matrix_rand(&B, rand() / 1000000);

  s21_mult_matrix(&A, &B, &actual);
  s21_create_matrix(A.rows, B.columns, &expected);

  ck_assert_int_eq(expected.rows, actual.rows);
  ck_assert_int_eq(expected.columns, actual.columns);

  for (int i = 0; i < A.rows; i++) {
    for (int j = 0; j < B.columns; j++) {
      for (int k = 0; k < A.columns; k++) {
        expected.matrix[i][j] += accuracy_check(A.matrix[i][k], ACCURACY) *
                                 accuracy_check(B.matrix[k][j], ACCURACY);
      }
    }
  }

  // printf("\n_________\n");
  // print_matrix(&A);
  // print_matrix(&B);
  // print_matrix(&expected);
  // printf("\n_________\n");

  for (int i = 0; i < expected.rows; i++) {
    for (int j = 0; j < expected.columns; j++) {
      ck_assert_double_eq_tol(expected.matrix[i][j], actual.matrix[i][j],
                              ACCURACY);
    }
  }

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&actual);
  s21_remove_matrix(&expected);
}

Suite *suite_s21_mult_matrix() {
  Suite *suite = suite_create("suite_s21_mult_matrix");

  TCase *normal_case = tcase_create("case_s21_mult_matrix");
  tcase_add_loop_test(normal_case, mult_matrix_test, 0,
                      sizeof(rows_A) / sizeof(int));
  suite_add_tcase(suite, normal_case);

  return suite;
}