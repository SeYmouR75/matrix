#include "s21_test_matrix.h"

START_TEST(inverse_matrix_test_2x2) {
    matrix_t m;
    s21_create_matrix(2, 2, &m);
    m.matrix[0][0] = 32.54;
    m.matrix[0][1] = 67.546;
    m.matrix[1][0] = 13.67;
    m.matrix[1][1] = 34.032;

    matrix_t act_inv, exp_inv;

    s21_create_matrix(2, 2, &exp_inv);
    exp_inv.matrix[0][0] = 0.184909;
    exp_inv.matrix[0][1] = -0.367003;
    exp_inv.matrix[1][0] = -0.074274;
    exp_inv.matrix[1][1] = 0.176802;

    int res = s21_inverse_matrix(&m, &act_inv);

    // print_matrix(&exp_inv);
    // print_matrix(&act_inv);

    ck_assert_int_eq(res, OK);

    for (int i = 0; i < exp_inv.rows; i++){
        for (int j = 0; j < exp_inv.columns; j++){
            ck_assert_double_eq_tol(act_inv.matrix[i][j], exp_inv.matrix[i][j], ACCURACY);
        }
    }

    s21_remove_matrix(&act_inv);
    s21_remove_matrix(&exp_inv);
    s21_remove_matrix(&m);
}
END_TEST

START_TEST(inverse_matrix_test_3x3) {
    matrix_t m;
    s21_create_matrix(3, 3, &m);
    m.matrix[0][0] = -5.345761;
    m.matrix[0][1] = 14.634432;
    m.matrix[0][2] = -7.154367;
    m.matrix[1][0] = 1.111111;
    m.matrix[1][1] = -3.345786;
    m.matrix[1][2] = 9.756643;
    m.matrix[2][0] = -10.101211;
    m.matrix[2][1] = 3.514411;
    m.matrix[2][2] = -44.756541;

    matrix_t act_inv, exp_inv;

    s21_create_matrix(3, 3, &exp_inv);
    exp_inv.matrix[0][0] = -0.103283;
    exp_inv.matrix[0][1] = -0.563433;
    exp_inv.matrix[0][2] = -0.106315;
    exp_inv.matrix[1][0] = 0.043676;
    exp_inv.matrix[1][1] = -0.149383;
    exp_inv.matrix[1][2] = -0.039546;
    exp_inv.matrix[2][0] = 0.02674;
    exp_inv.matrix[2][1] = 0.115433;
    exp_inv.matrix[2][2] = -0.001454;

    int res = s21_inverse_matrix(&m, &act_inv);

    // print_matrix(&exp_inv);
    // print_matrix(&act_inv);


    ck_assert_int_eq(res, OK);

    for (int i = 0; i < exp_inv.rows; i++){
        for (int j = 0; j < exp_inv.columns; j++){
            ck_assert_double_eq_tol(act_inv.matrix[i][j], exp_inv.matrix[i][j], ACCURACY);
        }
    }

    s21_remove_matrix(&act_inv);
    s21_remove_matrix(&exp_inv);
    s21_remove_matrix(&m);
}
END_TEST

START_TEST(inverse_matrix_test_4x4) {
    matrix_t m;
    s21_create_matrix(4, 4, &m);
    m.matrix[0][0] = 14.532;
    m.matrix[0][1] = 7.453;
    m.matrix[0][2] = -20.368;
    m.matrix[0][3] = -14.680;
    m.matrix[1][0] = 5.757;
    m.matrix[1][1] = 4.145;
    m.matrix[1][2] = -17.602;
    m.matrix[1][3] = 3.935;
    m.matrix[2][0] = 10.165;
    m.matrix[2][1] = 8.533;
    m.matrix[2][2] = -18.812;
    m.matrix[2][3] = -21.756;
    m.matrix[3][0] = -1.598;
    m.matrix[3][1] = 0.187;
    m.matrix[3][2] = 1.598;
    m.matrix[3][3] = -13.967;

    matrix_t act_inv, exp_inv;

    s21_create_matrix(4, 4, &exp_inv);
    exp_inv.matrix[0][0] = 0.176527;
    exp_inv.matrix[0][1] = -0.092228;
    exp_inv.matrix[0][2] = -0.10845;
    exp_inv.matrix[0][3] = -0.042593;
    exp_inv.matrix[1][0] = -0.353433;
    exp_inv.matrix[1][1] = -0.22542;
    exp_inv.matrix[1][2] = 0.547327;
    exp_inv.matrix[1][3] = -0.544589;
    exp_inv.matrix[2][0] = -0.031881;
    exp_inv.matrix[2][1] = -0.142007;
    exp_inv.matrix[2][2] = 0.100397;
    exp_inv.matrix[2][3] = -0.162886;
    exp_inv.matrix[3][0] = -0.028576;
    exp_inv.matrix[3][1] = -0.008713;
    exp_inv.matrix[3][2] = 0.031223;
    exp_inv.matrix[3][3] = -0.092652;

    int res = s21_inverse_matrix(&m, &act_inv);

    // print_matrix(&exp_inv);
    // print_matrix(&act_inv);

    ck_assert_int_eq(res, OK);

    for (int i = 0; i < exp_inv.rows; i++){
        for (int j = 0; j < exp_inv.columns; j++){
            ck_assert_double_eq_tol(act_inv.matrix[i][j], exp_inv.matrix[i][j], ACCURACY);
        }
    }
    s21_remove_matrix(&act_inv);
    s21_remove_matrix(&exp_inv);
    s21_remove_matrix(&m);
}
END_TEST

Suite *suite_s21_inverse_matrix(){
    Suite *suite = suite_create("suite_s21_inverse_matrix");

    TCase *normal_case = tcase_create("case_s21_inverse_matrix");

    tcase_add_test(normal_case, inverse_matrix_test_2x2);
    tcase_add_test(normal_case, inverse_matrix_test_3x3);
    tcase_add_test(normal_case, inverse_matrix_test_4x4);

    suite_add_tcase(suite, normal_case);

    return suite;
}