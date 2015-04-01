#include <check.h>

#include <cpu.h>
#include <opcodes.h>

#include "../opcodes_test.h"

START_TEST(inc_bc_test)
{
    struct cpu_t* cpu = setup_cpu();
    cpu->mem[0] = 0x03;
    cpu->tstates = 1000;
    REG_BC(*cpu) = 0x1234;
    execute_opcode(cpu);
    ck_assert(REG_BC(*cpu) == 0x1235);
    ck_assert(cpu->tstates == 1006);
}
END_TEST

START_TEST(inc_de_test)
{
    struct cpu_t* cpu = setup_cpu();
    cpu->mem[0] = 0x13;
    cpu->tstates = 1000;
    REG_DE(*cpu) = 0x1234;
    execute_opcode(cpu);
    ck_assert(REG_DE(*cpu) == 0x1235);
    ck_assert(cpu->tstates == 1006);
}
END_TEST

START_TEST(inc_hl_test)
{
    struct cpu_t* cpu = setup_cpu();
    cpu->mem[0] = 0x23;
    cpu->tstates = 1000;
    REG_HL(*cpu) = 0x1234;
    execute_opcode(cpu);
    ck_assert(REG_HL(*cpu) == 0x1235);
    ck_assert(cpu->tstates == 1006);
}
END_TEST

START_TEST(inc_sp_test)
{
    struct cpu_t* cpu = setup_cpu();
    cpu->mem[0] = 0x33;
    cpu->tstates = 1000;
    SP(*cpu) = 0x1234;
    execute_opcode(cpu);
    ck_assert(SP(*cpu) == 0x1235);
    ck_assert(cpu->tstates == 1006);
}
END_TEST

START_TEST(dec_bc_test)
{
    struct cpu_t* cpu = setup_cpu();
    cpu->mem[0] = 0x0B;
    cpu->tstates = 1000;
    REG_BC(*cpu) = 0x1234;
    execute_opcode(cpu);
    ck_assert(REG_BC(*cpu) == 0x1233);
    ck_assert(cpu->tstates == 1006);
}
END_TEST

START_TEST(dec_de_test)
{
    struct cpu_t* cpu = setup_cpu();
    cpu->mem[0] = 0x1B;
    cpu->tstates = 1000;
    REG_DE(*cpu) = 0x1234;
    execute_opcode(cpu);
    ck_assert(REG_DE(*cpu) == 0x1233);
    ck_assert(cpu->tstates == 1006);
}
END_TEST

START_TEST(dec_hl_test)
{
    struct cpu_t* cpu = setup_cpu();
    cpu->mem[0] = 0x2B;
    cpu->tstates = 1000;
    REG_HL(*cpu) = 0x1234;
    execute_opcode(cpu);
    ck_assert(REG_HL(*cpu) == 0x1233);
    ck_assert(cpu->tstates == 1006);
}
END_TEST

START_TEST(dec_sp_test)
{
    struct cpu_t* cpu = setup_cpu();
    cpu->mem[0] = 0x3B;
    cpu->tstates = 1000;
    SP(*cpu) = 0x1234;
    execute_opcode(cpu);
    ck_assert(SP(*cpu) == 0x1233);
    ck_assert(cpu->tstates == 1006);
}
END_TEST

TCase* gen_x0_z3_tcase(void)
{
    TCase* test = tcase_create("x=0 z=3 table");
    tcase_add_test(test, inc_bc_test);
    tcase_add_test(test, inc_de_test);
    tcase_add_test(test, inc_hl_test);
    tcase_add_test(test, inc_sp_test);
    tcase_add_test(test, dec_bc_test);
    tcase_add_test(test, dec_de_test);
    tcase_add_test(test, dec_hl_test);
    tcase_add_test(test, dec_sp_test);
    return test;
}
