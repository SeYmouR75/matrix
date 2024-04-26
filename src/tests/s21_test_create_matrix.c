#include "s21_test_matrix.h"

int normal_vals[] = {5, 5, 10, 10, 1, 1, 4, 51, 13, 5};

START_TEST(test_normal){
    int rows = normal_vals[_i];
    _i++;
    int columns = normal_vals[_i];

    matrix_t actual, expected;
    expected.rows = rows;
    expected.columns = columns;

    expected.matrix = malloc(expected.rows * sizeof(double));
    for(int i = 0; i < expected.rows; i++){
        expected.matrix[i] = malloc(expected.columns * sizeof(double));
    }

    ck_assert_int_eq(0, s21_create_matrix(rows, columns, &actual));
    ck_assert_ptr_nonnull(actual.matrix);
    ck_assert_int_eq(expected.rows, actual.rows);
    ck_assert_int_eq(expected.columns, actual.columns);
    
    s21_fill_matrix(&actual, 1.232);
    s21_fill_matrix(&expected, 1.232);
    for(int i = 0; i < expected.rows; i++){
        ck_assert_ptr_nonnull(actual.matrix[i]);
        for(int j = 0; j < expected.columns; j++){
            ck_assert_double_eq(expected.matrix[i][j], actual.matrix[i][j]);
        }
    }
}
END_TEST

int edge_vals[] = {};


// START_TEST(test_edge){
//     int rows = 
// }


Suite *suite_s21_create_matrix(){
    Suite *suite = suite_create("suite_s21_create_matrix");
    TCase *normal_case = tcase_create("case_s21_create_matrix");
    tcase_add_loop_test(normal_case, test_normal, 0, sizeof(normal_vals) / sizeof(int));
    suite_add_tcase(suite, normal_case);

    return suite;
}