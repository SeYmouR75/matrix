#include "s21_test_matrix.h"

START_TEST(calc_complements_test_2x2) {
    matrix_t m;
    s21_create_matrix(2, 2, &m);
    m.matrix[0][0] = 32.54;
    m.matrix[0][1] = 167.546;
    m.matrix[1][0] = 1368.67;
    m.matrix[1][1] = 134.032;

    matrix_t act_comp, exp_comp;

    s21_create_matrix(2, 2, &exp_comp);
    exp_comp.matrix[0][0] = 134.032;
    exp_comp.matrix[0][1] = -1368.67;
    exp_comp.matrix[1][0] = -167.546;
    exp_comp.matrix[1][1] = 32.54;

    int res = s21_calc_complements(&m, &act_comp);

    // print_matrix(&exp_comp);
    // print_matrix(&act_comp);

    ck_assert_int_eq(res, OK);

    for (int i = 0; i < exp_comp.rows; i++){
        for (int j = 0; j < exp_comp.columns; j++){
            ck_assert_double_eq_tol(act_comp.matrix[i][j], exp_comp.matrix[i][j], ACCURACY);
        }
    }

    s21_remove_matrix(&act_comp);
    s21_remove_matrix(&exp_comp);
    s21_remove_matrix(&m);
}
END_TEST

START_TEST(calc_complements_test_3x3) {
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

    matrix_t act_comp, exp_comp;

    s21_create_matrix(3, 3, &exp_comp);
    exp_comp.matrix[0][0] = 115.456955;
    exp_comp.matrix[0][1] = -48.824425;
    exp_comp.matrix[0][2] = -   29.89159;
    exp_comp.matrix[1][0] = 629.84317;
    exp_comp.matrix[1][1] = 166.990001;
    exp_comp.matrix[1][2] = -129.038284;
    exp_comp.matrix[2][0] = 118.845948;
    exp_comp.matrix[2][1] = 44.207386;
    exp_comp.matrix[2][2] = 1.625294;

    int res = s21_calc_complements(&m, &act_comp);

    // print_matrix(&exp_comp);
    // print_matrix(&act_comp);


    ck_assert_int_eq(res, OK);

    for (int i = 0; i < exp_comp.rows; i++){
        for (int j = 0; j < exp_comp.columns; j++){
            ck_assert_double_eq_tol(act_comp.matrix[i][j], exp_comp.matrix[i][j], ACCURACY);
        }
    }

    s21_remove_matrix(&act_comp);
    s21_remove_matrix(&exp_comp);
    s21_remove_matrix(&m);
}
END_TEST

START_TEST(calc_complements_test_4x4) {
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

    matrix_t act_comp, exp_comp;

    s21_create_matrix(4, 4, &exp_comp);
    exp_comp.matrix[0][0] = -725.510186;
    exp_comp.matrix[0][1] = 1452.578236;
    exp_comp.matrix[0][2] = 131.026434;
    exp_comp.matrix[0][3] = 117.446671;
    exp_comp.matrix[1][0] = 379.04997;
    exp_comp.matrix[1][1] = 926.456603;
    exp_comp.matrix[1][2] = 583.637265;
    exp_comp.matrix[1][3] = 35.811404;
    exp_comp.matrix[2][0] = 445.720194;
    exp_comp.matrix[2][1] = -2249.465138;
    exp_comp.matrix[2][2] = -412.621916;
    exp_comp.matrix[2][3] = -128.322523;
    exp_comp.matrix[3][0] = 175.052812;
    exp_comp.matrix[3][1] = 2238.213057;
    exp_comp.matrix[3][2] = 669.445621;
    exp_comp.matrix[3][3] = 380.790257;

    int res = s21_calc_complements(&m, &act_comp);

    // print_matrix(&exp_comp);
    // print_matrix(&act_comp);

    ck_assert_int_eq(res, OK);

    for (int i = 0; i < exp_comp.rows; i++){
        for (int j = 0; j < exp_comp.columns; j++){
            ck_assert_double_eq_tol(act_comp.matrix[i][j], exp_comp.matrix[i][j], ACCURACY);
        }
    }
    s21_remove_matrix(&act_comp);
    s21_remove_matrix(&exp_comp);
    s21_remove_matrix(&m);
}
END_TEST

Suite *suite_s21_calc_complements(){
    Suite *suite = suite_create("suite_s21_calc_complements");

    TCase *normal_case = tcase_create("case_s21_calc_complements");

    tcase_add_test(normal_case, calc_complements_test_2x2);
    tcase_add_test(normal_case, calc_complements_test_3x3);
    tcase_add_test(normal_case, calc_complements_test_4x4);

    suite_add_tcase(suite, normal_case);

    return suite;
}