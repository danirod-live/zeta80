#include <check.h>

#include "cpu_test.h"
#include "opcodes_test.h"

int
main(int argc, char** argv)
{
    SRunner* suite_runner = srunner_create(gensuite_cpu());
    srunner_add_suite(suite_runner, gensuite_opcodes());

    srunner_run_all(suite_runner, CK_NORMAL);
    int failed = srunner_ntests_failed(suite_runner);
    srunner_free(suite_runner);

    return (failed > 0);
}
