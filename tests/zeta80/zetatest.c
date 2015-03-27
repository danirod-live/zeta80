#include <check.h>

#include "cpu.h"

START_TEST(test_register_wordbyte)
{
    union register_t reg;
    
    /*
     * When assigning a 16 bit value, upper and lower 8 bit subregisters
     * should be properly splitted. This depends on whether host CPU
     * architecture is big endian or little endian.
     */
    reg.WORD = 0x1234;
    ck_assert(reg.WORD == 0x1234);
    ck_assert(reg.BYTES.H == 0x12);
    ck_assert(reg.BYTES.L == 0x34);

    /*
     * If we update one of the 8 bit subregister, 16 bit value should
     * be updated. First we will test upper 8 bit subregister. We expect
     * 8 most significant bits of word register to change.
     */
    reg.BYTES.H = 0x56;
    ck_assert(reg.WORD == 0x5634);
    ck_assert(reg.BYTES.H == 0x56);
    ck_assert(reg.BYTES.L == 0x34);
    
    /*
     * In the same fashion we can expect 8 least significant bits of word
     * register to change when we update the other subregister.
     */
    reg.BYTES.L = 0x78;
    ck_assert(reg.WORD == 0x5678);
    ck_assert(reg.BYTES.H == 0x56);
    ck_assert(reg.BYTES.L == 0x78);
}
END_TEST

Suite* cpu_suite(void)
{
    TCase* tc_register = tcase_create("Register");
    tcase_add_test(tc_register, test_register_wordbyte);

    Suite* s = suite_create("CPU");
    suite_add_tcase(s, tc_register);
    return s;
}

int
main(int argc, char** argv)
{
    int failed_tests = 0;

    // Test CPU
    Suite* cpuS = cpu_suite();
    SRunner* cpuSR = srunner_create(cpuS);
    srunner_run_all(cpuSR, CK_NORMAL);
    failed_tests += srunner_ntests_failed(cpuSR);
    srunner_free(cpuSR);

    return (failed_tests > 0);
}
