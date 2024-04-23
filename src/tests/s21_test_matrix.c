#include "s21_test_matrix.h"

void run_suite(Suite *suite) {
  SRunner *sr = srunner_create(suite);

  srunner_set_fork_status(sr, CK_NOFORK);
  srunner_run_all(sr, CK_NORMAL);  // CK_MINIMAL CK_NORMAL CK_VERBOSE

  srunner_free(sr);
}

void run_tests() {
  Suite *suites_core[] = {
      NULL};

  for (Suite **cur = suites_core; *cur != NULL; cur++) {
    printf("\n==================================\n");
    run_suite(*cur);
    printf("\n==================================\n");
  }
}

int main() {
  run_tests();
  return 0;
}