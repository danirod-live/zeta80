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

START_TEST(test_LD_D_B)
{
    cpu.mem[0] = 0x50;
    REG_B(cpu) = 0x12;
    execute_opcode(&cpu);
    ck_assert_uint_eq(0x12, REG_D(cpu));
    ck_assert_uint_eq(4, cpu.tstates);
}
END_TEST

START_TEST(test_LD_D_C)
{
    cpu.mem[0] = 0x51;
    REG_C(cpu) = 0x12;
    execute_opcode(&cpu);
    ck_assert_uint_eq(0x12, REG_D(cpu));
    ck_assert_uint_eq(4, cpu.tstates);
}
END_TEST

START_TEST(test_LD_D_D)
{
    cpu.mem[0] = 0x52;
    REG_D(cpu) = 0x12;
    execute_opcode(&cpu);
    ck_assert_uint_eq(0x12, REG_D(cpu));
    ck_assert_uint_eq(4, cpu.tstates);
}
END_TEST

START_TEST(test_LD_D_E)
{
    cpu.mem[0] = 0x53;
    REG_E(cpu) = 0x12;
    execute_opcode(&cpu);
    ck_assert_uint_eq(0x12, REG_D(cpu));
    ck_assert_uint_eq(4, cpu.tstates);
}
END_TEST

START_TEST(test_LD_D_H)
{
    cpu.mem[0] = 0x54;
    REG_H(cpu) = 0x12;
    execute_opcode(&cpu);
    ck_assert_uint_eq(0x12, REG_D(cpu));
    ck_assert_uint_eq(4, cpu.tstates);
}
END_TEST

START_TEST(test_LD_D_L)
{
    cpu.mem[0] = 0x55;
    REG_L(cpu) = 0x12;
    execute_opcode(&cpu);
    ck_assert_uint_eq(0x12, REG_D(cpu));
    ck_assert_uint_eq(4, cpu.tstates);
}
END_TEST

START_TEST(test_LD_D_iHL)
{
    cpu.mem[0] = 0x56;
    REG_HL(cpu) = 0x8000;
    cpu.mem[0x8000] = 0x12;
    execute_opcode(&cpu);
    ck_assert_uint_eq(0x12, REG_D(cpu));
    ck_assert_uint_eq(7, cpu.tstates);
}
END_TEST

START_TEST(test_LD_D_A)
{
    cpu.mem[0] = 0x57;
    REG_A(cpu) = 0x12;
    execute_opcode(&cpu);
    ck_assert_uint_eq(0x12, REG_D(cpu));
    ck_assert_uint_eq(4, cpu.tstates);
}
END_TEST

TCase* gen_x1_z2_tcase()
{
    TCase* test = tcase_create("x=1, z=2");
    tcase_add_checked_fixture(test, setup_cpu, teardown_cpu);
    tcase_add_test(test, test_LD_D_B);
    tcase_add_test(test, test_LD_D_C);
    tcase_add_test(test, test_LD_D_D);
    tcase_add_test(test, test_LD_D_E);
    tcase_add_test(test, test_LD_D_H);
    tcase_add_test(test, test_LD_D_L);
    tcase_add_test(test, test_LD_D_iHL);
    tcase_add_test(test, test_LD_D_A);
    return test;
}
