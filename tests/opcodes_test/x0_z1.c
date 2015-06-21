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

START_TEST(test_LC_BC_NN)
{
    cpu.mem[0] = 0x01;
    cpu.mem[1] = 0x34;
    cpu.mem[2] = 0x12;
    
    execute_opcode(&cpu);
    
    ck_assert_uint_eq(0x1234, REG_BC(cpu));
    ck_assert_uint_eq(10, cpu.tstates);
}
END_TEST

START_TEST(test_LD_DE_NN)
{
    cpu.mem[0] = 0x11;
    cpu.mem[1] = 0x34;
    cpu.mem[2] = 0x12;
    
    execute_opcode(&cpu);
    
    ck_assert_uint_eq(0x1234, REG_DE(cpu));
    ck_assert_uint_eq(10, cpu.tstates);
}
END_TEST

START_TEST(test_LD_HL_NN)
{
    cpu.mem[0] = 0x21;
    cpu.mem[1] = 0x34;
    cpu.mem[2] = 0x12;
    
    execute_opcode(&cpu);
    
    ck_assert_uint_eq(0x1234, REG_HL(cpu));
    ck_assert_uint_eq(10, cpu.tstates);
}
END_TEST

START_TEST(test_LD_SP_NN)
{
    cpu.mem[0] = 0x31;
    cpu.mem[1] = 0x34;
    cpu.mem[2] = 0x12;
    
    execute_opcode(&cpu);
    
    ck_assert_uint_eq(0x1234, SP(cpu));
    ck_assert_uint_eq(10, cpu.tstates);
}
END_TEST

START_TEST(test_ADD_HL_BC)
{
    cpu.mem[0] = 0x09; // ADD HL, BC
    REG_HL(cpu) = 0x4242;
    REG_BC(cpu) = 0x1111;
    
    execute_opcode(&cpu);
    
    ck_assert_uint_eq(0x5353, REG_HL(cpu));
    ck_assert_uint_eq(FLAG_GET(cpu, FLAG_C), 0);
    ck_assert_uint_eq(FLAG_GET(cpu, FLAG_H), 0);
    ck_assert_uint_eq(FLAG_GET(cpu, FLAG_N), 0);
    ck_assert_uint_eq(11, cpu.tstates);
}
END_TEST

START_TEST(test_ADD_HL_BC_hf)
{
    cpu.mem[0] = 0x09; // ADD HL, BC
    REG_HL(cpu) = 0x0800;
    REG_BC(cpu) = 0x0800;
    
    execute_opcode(&cpu);
    
    ck_assert_uint_eq(0x1000, REG_HL(cpu));
    ck_assert_uint_eq(FLAG_GET(cpu, FLAG_C), 0);
    ck_assert_uint_ne(FLAG_GET(cpu, FLAG_H), 0);
    ck_assert_uint_eq(FLAG_GET(cpu, FLAG_N), 0);
    ck_assert_uint_eq(11, cpu.tstates);
}
END_TEST

START_TEST(test_ADD_HL_BC_cf)
{
    cpu.mem[0] = 0x09; // ADD HL, BC
    REG_HL(cpu) = 0x8000;
    REG_BC(cpu) = 0x8000;
    
    execute_opcode(&cpu);
    
    ck_assert_uint_eq(0x0000, REG_HL(cpu));
    ck_assert_uint_ne(FLAG_GET(cpu, FLAG_C), 0);
    ck_assert_uint_eq(FLAG_GET(cpu, FLAG_H), 0);
    ck_assert_uint_eq(FLAG_GET(cpu, FLAG_N), 0);
    ck_assert_uint_eq(11, cpu.tstates);
}
END_TEST

START_TEST(test_ADD_HL_BC_hcf)
{
    cpu.mem[0] = 0x09; // ADD HL, BC
    REG_HL(cpu) = 0x8800;
    REG_BC(cpu) = 0x8800;
    
    execute_opcode(&cpu);
    
    ck_assert_uint_eq(0x1000, REG_HL(cpu));
    ck_assert_uint_ne(FLAG_GET(cpu, FLAG_C), 0);
    ck_assert_uint_ne(FLAG_GET(cpu, FLAG_H), 0);
    ck_assert_uint_eq(FLAG_GET(cpu, FLAG_N), 0);
    ck_assert_uint_eq(11, cpu.tstates);
}
END_TEST

START_TEST(test_ADD_HL_DE)
{
    cpu.mem[0] = 0x19; // ADD HL, DE
    REG_HL(cpu) = 0x4242;
    REG_DE(cpu) = 0x1111;
    
    execute_opcode(&cpu);
    
    ck_assert_uint_eq(0x5353, REG_HL(cpu));
    ck_assert_uint_eq(FLAG_GET(cpu, FLAG_C), 0);
    ck_assert_uint_eq(FLAG_GET(cpu, FLAG_H), 0);
    ck_assert_uint_eq(FLAG_GET(cpu, FLAG_N), 0);
    ck_assert_uint_eq(11, cpu.tstates);
}
END_TEST

START_TEST(test_ADD_HL_DE_hf)
{
    cpu.mem[0] = 0x19; // ADD HL, DE
    REG_HL(cpu) = 0x0800;
    REG_DE(cpu) = 0x0800;
    
    execute_opcode(&cpu);
    
    ck_assert_uint_eq(0x1000, REG_HL(cpu));
    ck_assert_uint_eq(FLAG_GET(cpu, FLAG_C), 0);
    ck_assert_uint_ne(FLAG_GET(cpu, FLAG_H), 0);
    ck_assert_uint_eq(FLAG_GET(cpu, FLAG_N), 0);
    ck_assert_uint_eq(11, cpu.tstates);
}
END_TEST

START_TEST(test_ADD_HL_DE_cf)
{
    cpu.mem[0] = 0x19; // ADD HL, DE
    REG_HL(cpu) = 0x8000;
    REG_DE(cpu) = 0x8000;
    
    execute_opcode(&cpu);
    
    ck_assert_uint_eq(0x0000, REG_HL(cpu));
    ck_assert_uint_ne(FLAG_GET(cpu, FLAG_C), 0);
    ck_assert_uint_eq(FLAG_GET(cpu, FLAG_H), 0);
    ck_assert_uint_eq(FLAG_GET(cpu, FLAG_N), 0);
    ck_assert_uint_eq(11, cpu.tstates);
}
END_TEST

START_TEST(test_ADD_HL_DE_hcf)
{
    cpu.mem[0] = 0x19; // ADD HL, DE
    REG_HL(cpu) = 0x8800;
    REG_DE(cpu) = 0x8800;
    
    execute_opcode(&cpu);
    
    ck_assert_uint_eq(0x1000, REG_HL(cpu));
    ck_assert_uint_ne(FLAG_GET(cpu, FLAG_C), 0);
    ck_assert_uint_ne(FLAG_GET(cpu, FLAG_H), 0);
    ck_assert_uint_eq(FLAG_GET(cpu, FLAG_N), 0);
    ck_assert_uint_eq(11, cpu.tstates);
}
END_TEST

START_TEST(test_ADD_HL_HL)
{
    cpu.mem[0] = 0x29; // ADD HL, HL
    REG_HL(cpu) = 0x4242;
    
    execute_opcode(&cpu);
    
    ck_assert_uint_eq(0x8484, REG_HL(cpu));
    ck_assert_uint_eq(FLAG_GET(cpu, FLAG_C), 0);
    ck_assert_uint_eq(FLAG_GET(cpu, FLAG_H), 0);
    ck_assert_uint_eq(FLAG_GET(cpu, FLAG_N), 0);
    ck_assert_uint_eq(11, cpu.tstates);
}
END_TEST

START_TEST(test_ADD_HL_HL_hf)
{
    cpu.mem[0] = 0x29; // ADD HL, HL
    REG_HL(cpu) = 0x0800;
    
    execute_opcode(&cpu);
    
    ck_assert_uint_eq(0x1000, REG_HL(cpu));
    ck_assert_uint_eq(FLAG_GET(cpu, FLAG_C), 0);
    ck_assert_uint_ne(FLAG_GET(cpu, FLAG_H), 0);
    ck_assert_uint_eq(FLAG_GET(cpu, FLAG_N), 0);
    ck_assert_uint_eq(11, cpu.tstates);
}
END_TEST

START_TEST(test_ADD_HL_HL_cf)
{
    cpu.mem[0] = 0x29; // ADD HL, HL
    REG_HL(cpu) = 0x8000;
    
    execute_opcode(&cpu);
    
    ck_assert_uint_eq(0x0000, REG_HL(cpu));
    ck_assert_uint_ne(FLAG_GET(cpu, FLAG_C), 0);
    ck_assert_uint_eq(FLAG_GET(cpu, FLAG_H), 0);
    ck_assert_uint_eq(FLAG_GET(cpu, FLAG_N), 0);
    ck_assert_uint_eq(11, cpu.tstates);
}
END_TEST

START_TEST(test_ADD_HL_HL_hcf)
{
    cpu.mem[0] = 0x29; // ADD HL, HL
    REG_HL(cpu) = 0x8800;
    
    execute_opcode(&cpu);
    
    ck_assert_uint_eq(0x1000, REG_HL(cpu));
    ck_assert_uint_ne(FLAG_GET(cpu, FLAG_C), 0);
    ck_assert_uint_ne(FLAG_GET(cpu, FLAG_H), 0);
    ck_assert_uint_eq(FLAG_GET(cpu, FLAG_N), 0);
    ck_assert_uint_eq(11, cpu.tstates);
}
END_TEST

START_TEST(test_ADD_HL_SP)
{
    cpu.mem[0] = 0x39; // ADD HL, SP
    REG_HL(cpu) = 0x4242;
    SP(cpu) = 0x1111;
    
    execute_opcode(&cpu);
    
    ck_assert_uint_eq(0x5353, REG_HL(cpu));
    ck_assert_uint_eq(FLAG_GET(cpu, FLAG_C), 0);
    ck_assert_uint_eq(FLAG_GET(cpu, FLAG_H), 0);
    ck_assert_uint_eq(FLAG_GET(cpu, FLAG_N), 0);
    ck_assert_uint_eq(11, cpu.tstates);
}
END_TEST

START_TEST(test_ADD_HL_SP_hf)
{
    cpu.mem[0] = 0x39; // ADD HL, SP
    REG_HL(cpu) = 0x0800;
    SP(cpu) = 0x0800;
    
    execute_opcode(&cpu);
    
    ck_assert_uint_eq(0x1000, REG_HL(cpu));
    ck_assert_uint_eq(FLAG_GET(cpu, FLAG_C), 0);
    ck_assert_uint_ne(FLAG_GET(cpu, FLAG_H), 0);
    ck_assert_uint_eq(FLAG_GET(cpu, FLAG_N), 0);
    ck_assert_uint_eq(11, cpu.tstates);
}
END_TEST

START_TEST(test_ADD_HL_SP_cf)
{
    cpu.mem[0] = 0x39; // ADD HL, SP
    REG_HL(cpu) = 0x8000;
    SP(cpu) = 0x8000;
    
    execute_opcode(&cpu);
    
    ck_assert_uint_eq(0x0000, REG_HL(cpu));
    ck_assert_uint_ne(FLAG_GET(cpu, FLAG_C), 0);
    ck_assert_uint_eq(FLAG_GET(cpu, FLAG_H), 0);
    ck_assert_uint_eq(FLAG_GET(cpu, FLAG_N), 0);
    ck_assert_uint_eq(11, cpu.tstates);
}
END_TEST

START_TEST(test_ADD_HL_SP_hcf)
{
    cpu.mem[0] = 0x39; // ADD HL, SP
    REG_HL(cpu) = 0x8800;
    SP(cpu) = 0x8800;
    
    execute_opcode(&cpu);
    
    ck_assert_uint_eq(0x1000, REG_HL(cpu));
    ck_assert_uint_ne(FLAG_GET(cpu, FLAG_C), 0);
    ck_assert_uint_ne(FLAG_GET(cpu, FLAG_H), 0);
    ck_assert_uint_eq(FLAG_GET(cpu, FLAG_N), 0);
    ck_assert_uint_eq(11, cpu.tstates);
}
END_TEST

TCase* gen_x0_z1_tcase(void)
{
    TCase* test = tcase_create("x=0, z=1");
    tcase_add_checked_fixture(test, setup_cpu, teardown_cpu);
    tcase_add_test(test, test_LC_BC_NN);
    tcase_add_test(test, test_LD_DE_NN);
    tcase_add_test(test, test_LD_HL_NN);
    tcase_add_test(test, test_LD_SP_NN);
    tcase_add_test(test, test_ADD_HL_BC);
    tcase_add_test(test, test_ADD_HL_BC_hf);
    tcase_add_test(test, test_ADD_HL_BC_cf);
    tcase_add_test(test, test_ADD_HL_BC_hcf);
    tcase_add_test(test, test_ADD_HL_DE);
    tcase_add_test(test, test_ADD_HL_DE_hf);
    tcase_add_test(test, test_ADD_HL_DE_cf);
    tcase_add_test(test, test_ADD_HL_DE_hcf);
    tcase_add_test(test, test_ADD_HL_HL);
    tcase_add_test(test, test_ADD_HL_HL_hf);
    tcase_add_test(test, test_ADD_HL_HL_cf);
    tcase_add_test(test, test_ADD_HL_HL_hcf);
    tcase_add_test(test, test_ADD_HL_SP);
    tcase_add_test(test, test_ADD_HL_SP_hf);
    tcase_add_test(test, test_ADD_HL_SP_cf);
    tcase_add_test(test, test_ADD_HL_SP_hcf);
    return test;
}
