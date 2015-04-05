/*
 * This file is part of the zeta80 emulation library.
 * Copyright (c) 2015, Dani Rodríguez
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * * Redistributions of source code must retain the above copyright notice,
 *   this list of conditions and the following disclaimer.
 *
 * * Redistributions in binary form must reproduce the above copyright
 *   notice, this list of conditions and the following disclaimer in the
 *   documentation and/or other materials provided with the distribution.
 *
 * * Neither the name of the project's author nor the names of its
 *   contributors may be used to endorse or promote products derived from
 *   this software without specific prior written permission.
 */

#include <check.h>

#include <cpu.h>
#include <opcodes.h>

#include "../opcodes_test.h" // Testcase definitions.

START_TEST(inc_b_test)
{
    struct cpu_t* cpu = setup_cpu();
    cpu->mem[0] = 0x04;
    REG_B(*cpu) = 0x12;
    execute_opcode(cpu);
    ck_assert(REG_B(*cpu) == 0x13);
    teardown_cpu(cpu);
}
END_TEST

START_TEST(inc_c_test)
{
    struct cpu_t* cpu = setup_cpu();
    cpu->mem[0] = 0x0C;
    REG_C(*cpu) = 0x12;
    execute_opcode(cpu);
    ck_assert(REG_C(*cpu) == 0x13);
    teardown_cpu(cpu);
}
END_TEST

START_TEST(inc_d_test)
{
    struct cpu_t* cpu = setup_cpu();
    cpu->mem[0] = 0x14;
    REG_D(*cpu) = 0x12;
    execute_opcode(cpu);
    ck_assert(REG_D(*cpu) == 0x13);
    teardown_cpu(cpu);
}
END_TEST

START_TEST(inc_e_test)
{
    struct cpu_t* cpu = setup_cpu();
    cpu->mem[0] = 0x1C;
    REG_E(*cpu) = 0x12;
    execute_opcode(cpu);
    ck_assert(REG_E(*cpu) == 0x13);
    teardown_cpu(cpu);
}
END_TEST

START_TEST(inc_h_test)
{
    struct cpu_t* cpu = setup_cpu();
    cpu->mem[0] = 0x24;
    REG_H(*cpu) = 0x12;
    execute_opcode(cpu);
    ck_assert(REG_H(*cpu) == 0x13);
    teardown_cpu(cpu);
}
END_TEST

START_TEST(inc_l_test)
{
    struct cpu_t* cpu = setup_cpu();
    cpu->mem[0] = 0x2C;
    REG_L(*cpu) = 0x12;
    execute_opcode(cpu);
    ck_assert(REG_L(*cpu) == 0x13);
    teardown_cpu(cpu);
}
END_TEST

START_TEST(inc_hli_test)
{
    struct cpu_t* cpu = setup_cpu();
    cpu->mem[0] = 0x34;
    REG_HL(*cpu) = 0x8000;
    cpu->mem[0x8000] = 0x12;
    execute_opcode(cpu);
    ck_assert(cpu->mem[0x8000] == 0x13);
    teardown_cpu(cpu);
}
END_TEST

START_TEST(inc_a_test)
{
    struct cpu_t* cpu = setup_cpu();
    cpu->mem[0] = 0x3C;
    REG_A(*cpu) = 0x12;
    execute_opcode(cpu);
    ck_assert(REG_A(*cpu) == 0x13);
    teardown_cpu(cpu);
}
END_TEST

START_TEST(inc_r8_tstates_test)
{
    struct cpu_t* cpu = setup_cpu();
    cpu->mem[0] = 0x04;
    cpu->tstates = 1000;
    REG_B(*cpu) = 0x12;
    execute_opcode(cpu);
    ck_assert(cpu->tstates == 1004);
    teardown_cpu(cpu);
}
END_TEST

START_TEST(inc_r8_sign_test)
{
    struct cpu_t* cpu = setup_cpu();
    cpu->mem[0] = 0x04;
    for (byte val = 0; val <= 0xFF; val++) {
        REG_B(*cpu) = val;
        PC(*cpu) = 0;
        execute_opcode(cpu);
        if (val & 0x80) {
            ck_assert(GET_FLAG(REG_F(*cpu), FLAG_S) != 0);
        } else {
            ck_assert(GET_FLAG(REG_F(*cpu), FLAG_S) == 0);
        }
    }
    teardown_cpu(cpu);
}
END_TEST

START_TEST(inc_r8_zero_test)
{
    struct cpu_t* cpu = setup_cpu();
    cpu->mem[0] = 0x04;
    for (byte val = 0; val <= 0xFF; val++) {
        REG_B(*cpu) = val;
        PC(*cpu) = 0;
        execute_opcode(cpu);
        if (val == 0xFF)
            ck_assert(GET_FLAG(REG_F(*cpu), FLAG_Z) != 0);
        else
            ck_assert(GET_FLAG(REG_F(*cpu), FLAG_Z) == 0);
    }
    teardown_cpu(cpu);
}
END_TEST

START_TEST(inc_r8_half_test)
{
    struct cpu_t* cpu = setup_cpu();
    cpu->mem[0] = 0x04;
    for (byte val = 0; val <= 0xFF; val++) {
        REG_B(*cpu) = val;
        PC(*cpu) = 0;
        execute_opcode(cpu);
        if ((val & 0xF) == 0xF)
            ck_assert(GET_FLAG(REG_F(*cpu), FLAG_H));
        else
            ck_assert(!GET_FLAG(REG_F(*cpu), FLAG_H));
    }
    teardown_cpu(cpu);
}
END_TEST

START_TEST(inc_r8_parity_test)
{
    struct cpu_t* cpu = setup_cpu();
    cpu->mem[0] = 0x04;
    for (byte val = 0; val <= 0xFF; val++) {
        REG_B(*cpu) = val;
        PC(*cpu) = 0;
        execute_opcode(cpu);
        if (val == 0x7F)
            ck_assert(GET_FLAG(REG_F(*cpu), FLAG_P) != 0);
        else
            ck_assert(GET_FLAG(REG_F(*cpu), FLAG_P) == 0);
    }
    teardown_cpu(cpu);
}
END_TEST

START_TEST(inc_r8_daa_test)
{
    struct cpu_t* cpu = setup_cpu();
    cpu->mem[0] = 0x04;
    REG_B(*cpu) = 0x12;
    execute_opcode(cpu);
    ck_assert(GET_FLAG(REG_F(*cpu), FLAG_N) == 0);
    teardown_cpu(cpu);
}
END_TEST

TCase* gen_x0_z4_tcase(void)
{
    TCase* test = tcase_create("x=0 z=4 table");
    tcase_add_test(test, inc_b_test);
    tcase_add_test(test, inc_c_test);
    tcase_add_test(test, inc_d_test);
    tcase_add_test(test, inc_e_test);
    tcase_add_test(test, inc_h_test);
    tcase_add_test(test, inc_l_test);
    tcase_add_test(test, inc_hli_test);
    tcase_add_test(test, inc_a_test);

    tcase_add_test(test, inc_r8_tstates_test);
    tcase_add_test(test, inc_r8_sign_test);
    tcase_add_test(test, inc_r8_zero_test);
    tcase_add_test(test, inc_r8_half_test);
    tcase_add_test(test, inc_r8_parity_test);
    tcase_add_test(test, inc_r8_daa_test);

    return test;
}
