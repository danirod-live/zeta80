#include <check.h>

#include "cpu_test.h"

int
main(int argc, char** argv)
{
    int failed_tests = 0;

    // Test CPU
    Suite* cpu_suite = gensuite_cpu();
    SRunner* cpu_runner = srunner_create(cpu_suite);
    srunner_run_all(cpu_runner, CK_NORMAL);
    failed_tests += srunner_ntests_failed(cpu_runner);
    srunner_free(cpu_runner);

    return (failed_tests > 0);
}
