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

START_TEST(rlca_test)
{
    struct cpu_t* cpu = setup_cpu();
    cpu->mem[0] = 0x07;
    REG_A(*cpu) = 0x88;
    execute_opcode(cpu);
    ck_assert(REG_A(*cpu) == 0x11);
    ck_assert(GET_FLAG(REG_F(*cpu), FLAG_C) != 0);
    ck_assert(GET_FLAG(REG_F(*cpu), FLAG_H) == 0);
    ck_assert(GET_FLAG(REG_F(*cpu), FLAG_N) == 0);
    teardown_cpu(cpu);
}
END_TEST

START_TEST(rla_test)
{
    struct cpu_t* cpu = setup_cpu();
    cpu->mem[0] = 0x17;
    REG_A(*cpu) = 0x76;
    SET_FLAG(REG_F(*cpu), FLAG_C);
    execute_opcode(cpu);
    ck_assert(REG_A(*cpu) == 0xED);
    ck_assert(GET_FLAG(REG_F(*cpu), FLAG_C) == 0);
    ck_assert(GET_FLAG(REG_F(*cpu), FLAG_H) == 0);
    ck_assert(GET_FLAG(REG_F(*cpu), FLAG_N) == 0);
    teardown_cpu(cpu);
}
END_TEST

START_TEST(rrca_test)
{
    struct cpu_t* cpu = setup_cpu();
    cpu->mem[0] = 0x0f;
    REG_A(*cpu) = 0x66;
    execute_opcode(cpu);
    ck_assert(REG_A(*cpu) == 0xCC);
    ck_assert(GET_FLAG(REG_F(*cpu), FLAG_C) != 0);
    ck_assert(GET_FLAG(REG_F(*cpu), FLAG_H) == 0);
    ck_assert(GET_FLAG(REG_F(*cpu), FLAG_N) == 0);
    teardown_cpu(cpu);
}
END_TEST

START_TEST(rra_test)
{
    struct cpu_t* cpu = setup_cpu();
    cpu->mem[0] = 0x1f;
    REG_A(*cpu) = 0xe1;
    RESET_FLAG(REG_F(*cpu), FLAG_C);
    execute_opcode(cpu);
    ck_assert(REG_A(*cpu) == 0x70);
    ck_assert(GET_FLAG(REG_F(*cpu), FLAG_C) != 0);
    ck_assert(GET_FLAG(REG_F(*cpu), FLAG_H) == 0);
    ck_assert(GET_FLAG(REG_F(*cpu), FLAG_N) == 0);
    teardown_cpu(cpu);
}
END_TEST

START_TEST(cpl_test)
{
    struct cpu_t* cpu = setup_cpu();
    cpu->mem[0] = 0x2f;
    REG_A(*cpu) = 0xa5;
    execute_opcode(cpu);
    ck_assert(REG_A(*cpu) == 0x5a);
    ck_assert(GET_FLAG(REG_F(*cpu), FLAG_H) != 0);
    ck_assert(GET_FLAG(REG_F(*cpu), FLAG_N) != 0);
    teardown_cpu(cpu);
}
END_TEST

START_TEST(scf_test)
{
    struct cpu_t* cpu = setup_cpu();
    cpu->mem[0] = 0x37;
    execute_opcode(cpu);
    ck_assert(GET_FLAG(REG_F(*cpu), FLAG_C) != 0);
    ck_assert(GET_FLAG(REG_F(*cpu), FLAG_H) == 0);
    ck_assert(GET_FLAG(REG_F(*cpu), FLAG_N) == 0);
    teardown_cpu(cpu);
}
END_TEST

START_TEST(ccf_reset_test)
{
    struct cpu_t* cpu = setup_cpu();
    cpu->mem[0] = 0x3f;
    SET_FLAG(REG_F(*cpu), FLAG_C);
    execute_opcode(cpu);
    ck_assert(GET_FLAG(REG_F(*cpu), FLAG_C) == 0);
    ck_assert(GET_FLAG(REG_F(*cpu), FLAG_H) != 0);
    ck_assert(GET_FLAG(REG_F(*cpu), FLAG_N) == 0);
    teardown_cpu(cpu);
}
END_TEST

START_TEST(ccf_set_test)
{
    struct cpu_t* cpu = setup_cpu();
    cpu->mem[0] = 0x3f;
    RESET_FLAG(REG_F(*cpu), FLAG_C);
    execute_opcode(cpu);
    ck_assert(GET_FLAG(REG_F(*cpu), FLAG_C) != 0);
    ck_assert(GET_FLAG(REG_F(*cpu), FLAG_H) == 0);
    ck_assert(GET_FLAG(REG_F(*cpu), FLAG_N) == 0);
    teardown_cpu(cpu);
}
END_TEST

TCase* gen_x0_z7_tcase(void)
{
    TCase* test = tcase_create("x=0 z=7 table");
    tcase_add_test(test, rlca_test);
    tcase_add_test(test, rla_test);
    tcase_add_test(test, rrca_test);
    tcase_add_test(test, rra_test);
    tcase_add_test(test, cpl_test);
    tcase_add_test(test, scf_test);
    tcase_add_test(test, ccf_reset_test);
    tcase_add_test(test, ccf_set_test);
    return test;
}
