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

START_TEST(ld_b_nn_test)
{
    struct cpu_t* cpu = setup_cpu();
    cpu->mem[0] = 0x06;
    cpu->mem[1] = 0x55;
    execute_opcode(cpu);
    ck_assert(REG_B(*cpu) == 0x55);
    teardown_cpu(cpu);
}
END_TEST

START_TEST(ld_c_nn_test)
{
    struct cpu_t* cpu = setup_cpu();
    cpu->mem[0] = 0x0e;
    cpu->mem[1] = 0x55;
    execute_opcode(cpu);
    ck_assert(REG_C(*cpu) == 0x55);
    teardown_cpu(cpu);
}
END_TEST

START_TEST(ld_d_nn_test)
{
    struct cpu_t* cpu = setup_cpu();
    cpu->mem[0] = 0x16;
    cpu->mem[1] = 0x55;
    execute_opcode(cpu);
    ck_assert(REG_D(*cpu) == 0x55);
    teardown_cpu(cpu);
}
END_TEST

START_TEST(ld_e_nn_test)
{
    struct cpu_t* cpu = setup_cpu();
    cpu->mem[0] = 0x1e;
    cpu->mem[1] = 0x55;
    execute_opcode(cpu);
    ck_assert(REG_E(*cpu) == 0x55);
    teardown_cpu(cpu);
}
END_TEST

START_TEST(ld_h_nn_test)
{
    struct cpu_t* cpu = setup_cpu();
    cpu->mem[0] = 0x26;
    cpu->mem[1] = 0x55;
    execute_opcode(cpu);
    ck_assert(REG_H(*cpu) == 0x55);
    teardown_cpu(cpu);
}
END_TEST

START_TEST(ld_l_nn_test)
{
    struct cpu_t* cpu = setup_cpu();
    cpu->mem[0] = 0x2e;
    cpu->mem[1] = 0x55;
    execute_opcode(cpu);
    ck_assert(REG_L(*cpu) == 0x55);
    teardown_cpu(cpu);
}
END_TEST

START_TEST(ld_hli_nn_test)
{
    struct cpu_t* cpu = setup_cpu();
    cpu->mem[0] = 0x36;
    cpu->mem[1] = 0x55;
    REG_HL(*cpu) = 0x8000;
    execute_opcode(cpu);
    ck_assert(cpu->mem[0x8000] == 0x55);
    teardown_cpu(cpu);
}
END_TEST

START_TEST(ld_a_nn_test)
{
    struct cpu_t* cpu = setup_cpu();
    cpu->mem[0] = 0x3e;
    cpu->mem[1] = 0x55;
    execute_opcode(cpu);
    ck_assert(REG_A(*cpu) == 0x55);
    teardown_cpu(cpu);
}
END_TEST

TCase* gen_x0_z6_tcase(void)
{
    TCase* test = tcase_create("x=0 z=6 table");
    tcase_add_test(test, ld_b_nn_test);
    tcase_add_test(test, ld_c_nn_test);
    tcase_add_test(test, ld_d_nn_test);
    tcase_add_test(test, ld_e_nn_test);
    tcase_add_test(test, ld_h_nn_test);
    tcase_add_test(test, ld_l_nn_test);
    tcase_add_test(test, ld_hli_nn_test);
    tcase_add_test(test, ld_a_nn_test);
    return test;
}
