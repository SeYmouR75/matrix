#include "s21_test_matrix.h"

START_TEST(transpose_matrix){
    matrix_t A, result;

    s21_create_matrix(3, 2, &A);
    fill_matrix_rand(&A, rand() % 100);

    s21_transpose(&A, &result);

    print_matrix(&A);
    print_matrix(&result);

    s21_remove_matrix(&A);
    s21_remove_matrix(&result);
}
END_TEST

Suite *suite_s21_transpose(){
    Suite *suite = suite_create("suite_s21_transpose_matrix");

    TCase *normal_case = tcase_create("case_s21_transpose_matrix");
    tcase_add_test(normal_case, transpose_matrix);
    suite_add_tcase(suite, normal_case);

    return suite;
}