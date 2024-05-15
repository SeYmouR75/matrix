#include "s21_test_matrix.h"

static int rows[] = {3, 4, 2, 3, 5, 4, 2, 1};
static int cols[] = {3, 2, 2, 5, 7, 5, 5, 1};

START_TEST(transpose_matrix) {
  matrix_t A, result;

  s21_create_matrix(rows[_i], cols[_i], &A);
  fill_matrix_rand(&A, rand() / 100);

  s21_transpose(&A, &result);

  // printf("\n_________\n");
  // print_matrix(&A);
  // print_matrix(&result);
  // printf("\n_________\n");

  for (int i = 0; i < A.rows; i++) {
    for (int j = 0; j < A.columns; j++) {
      ck_assert_double_eq_tol(A.matrix[i][j], result.matrix[j][i], ACCURACY);
    }
  }

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

Suite *suite_s21_transpose() {
  Suite *suite = suite_create("suite_s21_transpose_matrix");

  TCase *normal_case = tcase_create("case_s21_transpose_matrix");
  tcase_add_loop_test(normal_case, transpose_matrix, 0,
                      sizeof(rows) / sizeof(int));
  suite_add_tcase(suite, normal_case);

  return suite;
}