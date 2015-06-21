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

START_TEST(test_RLCA)
{
    // Example from Z80 Manual: 1000 1000 -> 0001 0001 (CF = 1)
    cpu.mem[0] = 0x07;
    REG_A(cpu) = 0x88;
    
    execute_opcode(&cpu);
    
    ck_assert_uint_eq(0x11, REG_A(cpu));
    ck_assert_uint_ne(0, FLAG_GET(cpu, FLAG_C));
    ck_assert_uint_eq(0, FLAG_GET(cpu, FLAG_H));
    ck_assert_uint_eq(0, FLAG_GET(cpu, FLAG_N));
}
END_TEST

START_TEST(test_RLA)
{
    // Example from Z80 Manual: 0111 0110 (CF = 1) -> 1110 1101 (CF = 0)
    cpu.mem[0] = 0x17;
    REG_A(cpu) = 0x76;
    FLAG_SET(cpu, FLAG_C);
    
    execute_opcode(&cpu);
    
    ck_assert_uint_eq(0xED, REG_A(cpu));
    ck_assert_uint_eq(0, FLAG_GET(cpu, FLAG_C));
    ck_assert_uint_eq(0, FLAG_GET(cpu, FLAG_H));
    ck_assert_uint_eq(0, FLAG_GET(cpu, FLAG_N));
}
END_TEST

START_TEST(test_RRCA)
{
    // Example form Z80 Manual is broken and should be reported.
    // 0001 0001 -> 1000 1000 (CF = 1)
    cpu.mem[0] = 0x0F;
    REG_A(cpu) = 0x11;
    
    execute_opcode(&cpu);
    
    ck_assert_uint_eq(0x88, REG_A(cpu));
    ck_assert_uint_ne(0, FLAG_GET(cpu, FLAG_C));
    ck_assert_uint_eq(0, FLAG_GET(cpu, FLAG_H));
    ck_assert_uint_eq(0, FLAG_GET(cpu, FLAG_N));
}
END_TEST

START_TEST(test_RRA)
{
    // Example from Z80 Manual: 1110 0001 (CF = 0) -> 0111 0000 (CF = 1)
    cpu.mem[0] = 0x1F;
    REG_A(cpu) = 0xE1;
    FLAG_RST(cpu, FLAG_C);
    
    execute_opcode(&cpu);
    
    ck_assert_uint_eq(0x70, REG_A(cpu));
    ck_assert_uint_ne(0, FLAG_GET(cpu, FLAG_C));
    ck_assert_uint_eq(0, FLAG_GET(cpu, FLAG_H));
    ck_assert_uint_eq(0, FLAG_GET(cpu, FLAG_N));
}
END_TEST

START_TEST(test_CPL)
{
    // Example from Book: 1011 0100 -> 0100 1011
    cpu.mem[0] = 0x2F;
    REG_A(cpu) = 0xB4;
    
    execute_opcode(&cpu);
    
    ck_assert_uint_eq(0x4B, REG_A(cpu));
    ck_assert_uint_ne(0, FLAG_GET(cpu, FLAG_H));
    ck_assert_uint_ne(0, FLAG_GET(cpu, FLAG_N));
}
END_TEST

START_TEST(test_SCF)
{
    cpu.mem[0] = 0x37;
    
    execute_opcode(&cpu);
    
    ck_assert_uint_ne(0, FLAG_GET(cpu, FLAG_C));
    ck_assert_uint_eq(0, FLAG_GET(cpu, FLAG_H));
    ck_assert_uint_eq(0, FLAG_GET(cpu, FLAG_N));
}
END_TEST

START_TEST(test_CCF_reset)
{
    cpu.mem[0] = 0x3F;
    FLAG_SET(cpu, FLAG_C);
    
    execute_opcode(&cpu);
    
    ck_assert_uint_eq(0, FLAG_GET(cpu, FLAG_C));
    ck_assert_uint_ne(0, FLAG_GET(cpu, FLAG_H));
    ck_assert_uint_eq(0, FLAG_GET(cpu, FLAG_N));
}
END_TEST

START_TEST(test_CCF_set)
{
    cpu.mem[0] = 0x3F;
    FLAG_RST(cpu, FLAG_C);
    
    execute_opcode(&cpu);
    
    ck_assert_uint_ne(0, FLAG_GET(cpu, FLAG_C));
    ck_assert_uint_eq(0, FLAG_GET(cpu, FLAG_H));
    ck_assert_uint_eq(0, FLAG_GET(cpu, FLAG_N));
}
END_TEST

TCase* gen_x0_z7_tcase(void)
{
    TCase* test = tcase_create("x=0, z=7");
    tcase_add_checked_fixture(test, setup_cpu, teardown_cpu);
    tcase_add_test(test, test_RLCA);
    tcase_add_test(test, test_RLA);
    tcase_add_test(test, test_RRCA);
    tcase_add_test(test, test_RRA);
    tcase_add_test(test, test_CPL);
    tcase_add_test(test, test_SCF);
    tcase_add_test(test, test_CCF_reset);
    tcase_add_test(test, test_CCF_set);
    return test;
}
