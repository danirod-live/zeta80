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

START_TEST(test_LD_iBC_A)
{
    cpu.mem[0] = 0x02; // LD (BC), A
    REG_BC(cpu) = 0x8000;
    REG_A(cpu) = 0x55;
    
    execute_opcode(&cpu);
    
    ck_assert_uint_eq(0x55, cpu.mem[0x8000]);
    ck_assert_uint_eq(7, cpu.tstates);
}
END_TEST

START_TEST(test_LD_iDE_A)
{
    cpu.mem[0] = 0x12; // LD (DE), A
    REG_DE(cpu) = 0x8000;
    REG_A(cpu) = 0x55;
    
    execute_opcode(&cpu);
    
    ck_assert_uint_eq(0x55, cpu.mem[0x8000]);
    ck_assert_uint_eq(7, cpu.tstates);
}
END_TEST

START_TEST(test_LD_iNN_HL)
{
    cpu.mem[0] = 0x22; // LD (NN), HL
    cpu.mem[1] = 0x00;
    cpu.mem[2] = 0x80;
    REG_HL(cpu) = 0x1234;
    
    execute_opcode(&cpu);
    
    ck_assert_uint_eq(0x34, cpu.mem[0x8000]);
    ck_assert_uint_eq(0x12, cpu.mem[0x8001]);
    ck_assert_uint_eq(16, cpu.tstates);
}
END_TEST

START_TEST(test_LD_iNN_A)
{
    cpu.mem[0] = 0x32;
    cpu.mem[1] = 0x00;
    cpu.mem[2] = 0x80;
    REG_A(cpu) = 0x55;
    
    execute_opcode(&cpu);
    
    ck_assert_uint_eq(0x55, cpu.mem[0x8000]);
    ck_assert_uint_eq(13, cpu.tstates);
}
END_TEST

START_TEST(test_LD_A_iBC)
{
    cpu.mem[0] = 0x0A; // LD A, (BC)
    cpu.mem[0x8000] = 0x55;
    REG_BC(cpu) = 0x8000;
    
    execute_opcode(&cpu);
    
    ck_assert_uint_eq(0x55, REG_A(cpu));
    ck_assert_uint_eq(7, cpu.tstates);
}
END_TEST

START_TEST(test_LD_A_iDE)
{
    cpu.mem[0] = 0x1A; // LD A, (DE)
    cpu.mem[0x8000] = 0x55;
    REG_DE(cpu) = 0x8000;
    
    execute_opcode(&cpu);
    
    ck_assert_uint_eq(0x55, REG_A(cpu));
    ck_assert_uint_eq(7, cpu.tstates);
}
END_TEST

/* Test for LD HL, (NN) instruction. */
START_TEST(test_LD_HL_iNN)
{
    cpu.mem[0] = 0x2A; // LD HL, (NN)
    cpu.mem[1] = 0x00;
    cpu.mem[2] = 0x80;
    cpu.mem[0x8000] = 0x34;
    cpu.mem[0x8001] = 0x12;
    
    execute_opcode(&cpu);
    
    ck_assert_uint_eq(0x1234, REG_HL(cpu));
    ck_assert_uint_eq(16, cpu.tstates);
}
END_TEST

START_TEST(test_LD_A_iNN)
{
    cpu.mem[0] = 0x3A;
    cpu.mem[1] = 0x00;
    cpu.mem[2] = 0x80;
    cpu.mem[0x8000] = 0x55;

    execute_opcode(&cpu);
    
    ck_assert_uint_eq(0x55, REG_A(cpu));
    ck_assert_uint_eq(13, cpu.tstates);
}
END_TEST

TCase* gen_x0_z2_tcase(void)
{
    TCase* test = tcase_create("x=0, z=2");
    tcase_add_test(test, test_LD_iBC_A);
    tcase_add_test(test, test_LD_iDE_A);
    tcase_add_test(test, test_LD_A_iBC);
    tcase_add_test(test, test_LD_A_iDE);
    tcase_add_test(test, test_LD_iNN_HL);
    tcase_add_test(test, test_LD_iNN_A);
    tcase_add_test(test, test_LD_HL_iNN);
    tcase_add_test(test, test_LD_A_iNN);
    return test;
}
