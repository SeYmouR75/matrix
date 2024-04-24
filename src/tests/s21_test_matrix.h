#ifndef S21_TEST_matrix_H
#define S21_TEST_matrix_H

#include <check.h>
#include <stdlib.h>

#include "../s21_matrix.h"

Suite *suite_s21_create_matrix();
Suite *suite_s21_remove_matrix();
Suite *suite_s21_eq_matrix();
Suite *suite_s21_sum_matrix();
Suite *suite_s21_sub_matrix();
Suite *suite_s21_mult_number();
Suite *suite_s21_mult_matrix();
Suite *suite_s21_transpose();
Suite *suite_s21_calc_complements();
Suite *suite_s21_determinant();
Suite *suite_s21_inverse_matrix();

#endif  // S21_TEST_matrix_H