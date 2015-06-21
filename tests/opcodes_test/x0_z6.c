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

START_TEST(test_LD_B_NN)
{
    cpu.mem[0] = 0x06;
    cpu.mem[1] = 0x55;
    
    execute_opcode(&cpu);
    
    ck_assert_uint_eq(0x55, REG_B(cpu));
}
END_TEST

START_TEST(test_LD_C_NN)
{
    cpu.mem[0] = 0x0E;
    cpu.mem[1] = 0x55;
    
    execute_opcode(&cpu);
    
    ck_assert_uint_eq(0x55, REG_C(cpu));
}
END_TEST

START_TEST(test_LD_D_NN)
{
    cpu.mem[0] = 0x16;
    cpu.mem[1] = 0x55;
    
    execute_opcode(&cpu);
    
    ck_assert_uint_eq(0x55, REG_D(cpu));
}
END_TEST

START_TEST(test_LD_E_NN)
{
    cpu.mem[0] = 0x1E;
    cpu.mem[1] = 0x55;
    
    execute_opcode(&cpu);
    
    ck_assert_uint_eq(0x55, REG_E(cpu));
}
END_TEST

START_TEST(test_LD_H_NN)
{
    cpu.mem[0] = 0x26;
    cpu.mem[1] = 0x55;
    
    execute_opcode(&cpu);
    
    ck_assert_uint_eq(0x55, REG_H(cpu));
}
END_TEST

START_TEST(test_LD_L_NN)
{
    cpu.mem[0] = 0x2E;
    cpu.mem[1] = 0x55;
    
    execute_opcode(&cpu);
    
    ck_assert_uint_eq(0x55, REG_L(cpu));
}
END_TEST

START_TEST(test_LD_iHL_NN)
{
    cpu.mem[0] = 0x36;
    cpu.mem[1] = 0x55;
    REG_HL(cpu) = 0x8000;
    
    execute_opcode(&cpu);
    
    ck_assert_uint_eq(0x55, cpu.mem[0x8000]);
}
END_TEST

START_TEST(test_LD_A_NN)
{
    cpu.mem[0] = 0x3E;
    cpu.mem[1] = 0x55;
    
    execute_opcode(&cpu);
    
    ck_assert_uint_eq(0x55, REG_A(cpu));
}
END_TEST

TCase* gen_x0_z6_tcase(void)
{
    TCase* test = tcase_create("x=0, z=6");
    tcase_add_checked_fixture(test, setup_cpu, teardown_cpu);
    tcase_add_test(test, test_LD_B_NN);
    tcase_add_test(test, test_LD_C_NN);
    tcase_add_test(test, test_LD_D_NN);
    tcase_add_test(test, test_LD_E_NN);
    tcase_add_test(test, test_LD_H_NN);
    tcase_add_test(test, test_LD_L_NN);
    tcase_add_test(test, test_LD_iHL_NN);
    tcase_add_test(test, test_LD_A_NN);
    return test;
}
