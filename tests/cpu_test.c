// CPU test case

#include "cpu.h"
#include "cpu_test.h"

START_TEST(register_t_test_word)
{
    union register_t reg;
    reg.WORD = 0x1234;
    ck_assert(reg.WORD == 0x1234);
    ck_assert(reg.BYTES.H == 0x12);
    ck_assert(reg.BYTES.L == 0x34);
}
END_TEST

START_TEST(register_t_test_bytes)
{
    union register_t reg;
    reg.BYTES.H = 0x56;
    reg.BYTES.L = 0x78;
    ck_assert(reg.WORD == 0x5678);
    ck_assert(reg.BYTES.H == 0x56);
    ck_assert(reg.BYTES.L == 0x78);
}
END_TEST

Suite*
gensuite_cpu(void)
{
    TCase* tc_register = tcase_create("Register");
    tcase_add_test(tc_register, register_t_test_word);
    tcase_add_test(tc_register, register_t_test_bytes);

    Suite* s = suite_create("CPU");
    suite_add_tcase(s, tc_register);
    return s;
}
