#include "s21_test_matrix.h"

static int normal_vals[] = {5, 5, 6, 7, 1, 1, 4, 5, 2, 5};

START_TEST(create_normal_test) {
  int rows = normal_vals[_i];
  _i++;
  int columns = normal_vals[_i];

  // printf("\n_________\n");
  // printf("iteration:%d start.rows:%d start.cols:%d\n", _i - 1, rows,
  // columns);

  matrix_t actual, expected;
  expected.rows = rows;
  expected.columns = columns;

  expected.matrix = malloc(expected.rows * sizeof(double));
  for (int i = 0; i < expected.rows; i++) {
    expected.matrix[i] = malloc(expected.columns * sizeof(double));
  }

  // printf("act.rows:%d act.cols:%d exp.rows:%d exp.cols:%d", actual.rows,
  // actual.columns, expected.rows, expected.columns); printf("\n_________\n");

  ck_assert_int_eq(0, s21_create_matrix(rows, columns, &actual));
  ck_assert_ptr_nonnull(actual.matrix);
  ck_assert_int_eq(expected.rows, actual.rows);
  ck_assert_int_eq(expected.columns, actual.columns);

  fill_matrix(&actual, 1.232);
  fill_matrix(&expected, 1.232);
  for (int i = 0; i < expected.rows; i++) {
    ck_assert_ptr_nonnull(actual.matrix[i]);
    for (int j = 0; j < expected.columns; j++) {
      ck_assert_double_eq(expected.matrix[i][j], actual.matrix[i][j]);
    }
  }

  s21_remove_matrix(&actual);
  s21_remove_matrix(&expected);
}
END_TEST

static int edge_vals[] = {-1, 0, 0, -3, -3, 4, 0.132, 2, 0.0001};

START_TEST(create_edge_test) {
  int rows = edge_vals[_i];
  _i++;
  int columns = edge_vals[_i];

  // printf("\n_________\n");
  // printf("iteration:%d start.rows:%d start.cols:%d\n", _i - 1, rows,
  // columns);

  matrix_t actual;
  int res = s21_create_matrix(rows, columns, &actual);

  // printf("act.rows:%d act.cols:%d", actual.rows, actual.columns);
  // printf("\n_________\n");

  ck_assert_int_eq(INVALID_MATRIX, res);
  ck_assert_int_eq(0, actual.rows);
  ck_assert_int_eq(0, actual.columns);
}
END_TEST

Suite *suite_s21_create_matrix() {
  Suite *suite = suite_create("suite_s21_create_matrix");

  TCase *normal_case = tcase_create("case_s21_create_matrix_normal");
  tcase_add_loop_test(normal_case, create_normal_test, 0,
                      sizeof(normal_vals) / sizeof(int) - 1);
  suite_add_tcase(suite, normal_case);

  TCase *edge_case = tcase_create("case_s21_create_matrix_edge");
  tcase_add_loop_test(edge_case, create_edge_test, 0,
                      sizeof(edge_vals) / sizeof(int) - 1);
  suite_add_tcase(suite, edge_case);

  return suite;
}