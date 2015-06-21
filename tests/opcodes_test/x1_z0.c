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

START_TEST(test_LD_B_B)
{
    cpu.mem[0] = 0x40;
    REG_B(cpu) = 0x12;
    execute_opcode(&cpu);
    ck_assert_uint_eq(0x12, REG_B(cpu));
    ck_assert_uint_eq(4, cpu.tstates);
}
END_TEST

START_TEST(test_LD_B_C)
{
    cpu.mem[0] = 0x41;
    REG_C(cpu) = 0x12;
    execute_opcode(&cpu);
    ck_assert_uint_eq(0x12, REG_B(cpu));
    ck_assert_uint_eq(4, cpu.tstates);
}
END_TEST

START_TEST(test_LD_B_D)
{
    cpu.mem[0] = 0x42;
    REG_D(cpu) = 0x12;
    execute_opcode(&cpu);
    ck_assert_uint_eq(0x12, REG_B(cpu));
    ck_assert_uint_eq(4, cpu.tstates);
}
END_TEST

START_TEST(test_LD_B_E)
{
    cpu.mem[0] = 0x43;
    REG_E(cpu) = 0x12;
    execute_opcode(&cpu);
    ck_assert_uint_eq(0x12, REG_B(cpu));
    ck_assert_uint_eq(4, cpu.tstates);
}
END_TEST

START_TEST(test_LD_B_H)
{
    cpu.mem[0] = 0x44;
    REG_H(cpu) = 0x12;
    execute_opcode(&cpu);
    ck_assert_uint_eq(0x12, REG_B(cpu));
    ck_assert_uint_eq(4, cpu.tstates);
}
END_TEST

START_TEST(test_LD_B_L)
{
    cpu.mem[0] = 0x45;
    REG_L(cpu) = 0x12;
    execute_opcode(&cpu);
    ck_assert_uint_eq(0x12, REG_B(cpu));
    ck_assert_uint_eq(4, cpu.tstates);
}
END_TEST

START_TEST(test_LD_B_iHL)
{
    cpu.mem[0] = 0x46;
    REG_HL(cpu) = 0x8000;
    cpu.mem[0x8000] = 0x12;
    execute_opcode(&cpu);
    ck_assert_uint_eq(0x12, REG_B(cpu));
    ck_assert_uint_eq(7, cpu.tstates);
}
END_TEST

START_TEST(test_LD_B_A)
{
    cpu.mem[0] = 0x47;
    REG_A(cpu) = 0x12;
    execute_opcode(&cpu);
    ck_assert_uint_eq(0x12, REG_B(cpu));
    ck_assert_uint_eq(4, cpu.tstates);
}
END_TEST

TCase* gen_x1_z0_tcase()
{
    TCase* test = tcase_create("x=1, z=0");
    tcase_add_checked_fixture(test, setup_cpu, teardown_cpu);
    tcase_add_test(test, test_LD_B_B);
    tcase_add_test(test, test_LD_B_C);
    tcase_add_test(test, test_LD_B_D);
    tcase_add_test(test, test_LD_B_E);
    tcase_add_test(test, test_LD_B_H);
    tcase_add_test(test, test_LD_B_L);
    tcase_add_test(test, test_LD_B_iHL);
    tcase_add_test(test, test_LD_B_A);
    return test;
}