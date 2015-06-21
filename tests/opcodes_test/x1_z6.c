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

START_TEST(test_LD_iHL_B)
{
    cpu.mem[0] = 0x70;
    REG_HL(cpu) = 0x8000;
    REG_B(cpu) = 0x12;
    execute_opcode(&cpu);
    ck_assert_uint_eq(0x12, cpu.mem[0x8000]);
    ck_assert_uint_eq(7, cpu.tstates);
}
END_TEST

START_TEST(test_LD_iHL_C)
{
    cpu.mem[0] = 0x71;
    REG_HL(cpu) = 0x8000;
    REG_C(cpu) = 0x12;
    execute_opcode(&cpu);
    ck_assert_uint_eq(0x12, cpu.mem[0x8000]);
    ck_assert_uint_eq(7, cpu.tstates);
}
END_TEST

START_TEST(test_LD_iHL_D)
{
    cpu.mem[0] = 0x72;
    REG_HL(cpu) = 0x8000;
    REG_D(cpu) = 0x12;
    execute_opcode(&cpu);
    ck_assert_uint_eq(0x12, cpu.mem[0x8000]);
    ck_assert_uint_eq(7, cpu.tstates);
}
END_TEST

START_TEST(test_LD_iHL_E)
{
    cpu.mem[0] = 0x73;
    REG_HL(cpu) = 0x8000;
    REG_E(cpu) = 0x12;
    execute_opcode(&cpu);
    ck_assert_uint_eq(0x12, cpu.mem[0x8000]);
    ck_assert_uint_eq(7, cpu.tstates);
}
END_TEST

START_TEST(test_LD_iHL_H)
{
    cpu.mem[0] = 0x74;
    REG_HL(cpu) = 0x1234;
    execute_opcode(&cpu);
    ck_assert_uint_eq(0x12, cpu.mem[0x1234]);
    ck_assert_uint_eq(7, cpu.tstates);
}
END_TEST

START_TEST(test_LD_iHL_L)
{
    cpu.mem[0] = 0x75;
    REG_HL(cpu) = 0x1234;
    execute_opcode(&cpu);
    ck_assert_uint_eq(0x34, cpu.mem[0x1234]);
    ck_assert_uint_eq(7, cpu.tstates);
}
END_TEST

START_TEST(test_LD_iHL_A)
{
    cpu.mem[0] = 0x77;
    REG_HL(cpu) = 0x8000;
    REG_A(cpu) = 0x12;
    execute_opcode(&cpu);
    ck_assert_uint_eq(0x12, cpu.mem[0x8000]);
    ck_assert_uint_eq(7, cpu.tstates);
}
END_TEST

TCase* gen_x1_z6_tcase()
{
    TCase* test = tcase_create("x=1, z=6");
    tcase_add_checked_fixture(test, setup_cpu, teardown_cpu);
    tcase_add_test(test, test_LD_iHL_B);
    tcase_add_test(test, test_LD_iHL_C);
    tcase_add_test(test, test_LD_iHL_D);
    tcase_add_test(test, test_LD_iHL_E);
    tcase_add_test(test, test_LD_iHL_H);
    tcase_add_test(test, test_LD_iHL_L);
    tcase_add_test(test, test_LD_iHL_A);
    return test;
}
