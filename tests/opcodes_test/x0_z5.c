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

START_TEST(test_DEC_B)
{
    cpu.mem[0] = 0x05;
    REG_B(cpu) = 0x12;
    
    execute_opcode(&cpu);
    
    ck_assert_uint_eq(0x11, REG_B(cpu));
    ck_assert_uint_eq(4, cpu.tstates);
}
END_TEST

START_TEST(test_DEC_C)
{
    cpu.mem[0] = 0x0D;
    REG_C(cpu) = 0x12;
    
    execute_opcode(&cpu);
    
    ck_assert_uint_eq(0x11, REG_C(cpu));
    ck_assert_uint_eq(4, cpu.tstates);
}
END_TEST

START_TEST(test_DEC_D)
{
    cpu.mem[0] = 0x15;
    REG_D(cpu) = 0x12;
    
    execute_opcode(&cpu);
    
    ck_assert_uint_eq(0x11, REG_D(cpu));
    ck_assert_uint_eq(4, cpu.tstates);
}
END_TEST

START_TEST(test_DEC_E)
{
    cpu.mem[0] = 0x1D;
    REG_E(cpu) = 0x12;
    
    execute_opcode(&cpu);
    
    ck_assert_uint_eq(0x11, REG_E(cpu));
    ck_assert_uint_eq(4, cpu.tstates);
}
END_TEST

START_TEST(test_DEC_H)
{
    cpu.mem[0] = 0x25;
    REG_H(cpu) = 0x12;
    
    execute_opcode(&cpu);
    
    ck_assert_uint_eq(0x11, REG_H(cpu));
    ck_assert_uint_eq(4, cpu.tstates);
}
END_TEST

START_TEST(test_DEC_L)
{
    cpu.mem[0] = 0x2D;
    REG_L(cpu) = 0x12;
    
    execute_opcode(&cpu);
    
    ck_assert_uint_eq(0x11, REG_L(cpu));
    ck_assert_uint_eq(4, cpu.tstates);
}
END_TEST

START_TEST(test_DEC_iHL)
{
    cpu.mem[0] = 0x35;
    REG_HL(cpu) = 0x8000;
    cpu.mem[0x8000] = 0x12;
    
    execute_opcode(&cpu);
    
    ck_assert_uint_eq(0x11, cpu.mem[0x8000]);
    ck_assert_uint_eq(11, cpu.tstates);
}
END_TEST

START_TEST(test_DEC_A)
{
    cpu.mem[0] = 0x3D;
    REG_A(cpu) = 0x12;
    
    execute_opcode(&cpu);
    
    ck_assert_uint_eq(0x11, REG_A(cpu));
    ck_assert_uint_eq(4, cpu.tstates);
}
END_TEST

START_TEST(test_DEC_r8_sf)
{
    cpu.mem[0] = 0x05;
    byte val = 0;
    do {
        REG_B(cpu) = val;
        PC(cpu) = 0;
        execute_opcode(&cpu);
        if ((val - 1) & 0x80) {
            ck_assert_uint_ne(0, FLAG_GET(cpu, FLAG_S));
        } else {
            ck_assert_uint_eq(0, FLAG_GET(cpu, FLAG_S));
        }
        val++;
    } while (val != 0);
}
END_TEST

START_TEST(test_DEC_r8_zf)
{
    cpu.mem[0] = 0x05;
    byte val = 0;
    do {
        REG_B(cpu) = val;
        PC(cpu) = 0;
        execute_opcode(&cpu);
        if (val == 0x01) {
            ck_assert_uint_ne(0, FLAG_GET(cpu, FLAG_Z));
        } else {
            ck_assert_uint_eq(0, FLAG_GET(cpu, FLAG_Z));
        }
        val++;
    } while (val != 0);
}
END_TEST

START_TEST(test_DEC_r8_hf)
{
    cpu.mem[0] = 0x05;
    byte val = 0;
    do {
        REG_B(cpu) = val;
        PC(cpu) = 0;
        execute_opcode(&cpu);
        if (((val - 1) & 0x0F) == 0x0F) {
            ck_assert_uint_ne(0, FLAG_GET(cpu, FLAG_H));
        } else {
            ck_assert_uint_eq(0, FLAG_GET(cpu, FLAG_H));
        }
        val++;
    } while (val != 0);
}
END_TEST

START_TEST(test_DEC_r8_vf)
{
    cpu.mem[0] = 0x05;
    byte val = 0x00;
    do {
        REG_B(cpu) = val;
        PC(cpu) = 0;
        execute_opcode(&cpu);
        if (val == 0x80)
            ck_assert_uint_ne(0, FLAG_GET(cpu, FLAG_P));
        else
            ck_assert_uint_eq(0, FLAG_GET(cpu, FLAG_P));
        val++;
    } while (val != 0x00);
}
END_TEST

START_TEST(test_DEC_r8_daa)
{
    cpu.mem[0] = 0x05;
    REG_B(cpu) = 0x12;
    
    execute_opcode(&cpu);
    
    ck_assert_uint_ne(0, FLAG_GET(cpu, FLAG_N));
}
END_TEST

TCase* gen_x0_z5_tcase(void)
{
    TCase* test = tcase_create("x=0, z=5");
    tcase_add_test(test, test_DEC_B);
    tcase_add_test(test, test_DEC_C);
    tcase_add_test(test, test_DEC_D);
    tcase_add_test(test, test_DEC_E);
    tcase_add_test(test, test_DEC_H);
    tcase_add_test(test, test_DEC_L);
    tcase_add_test(test, test_DEC_iHL);
    tcase_add_test(test, test_DEC_A);
    
    tcase_add_test(test, test_DEC_r8_sf);
    tcase_add_test(test, test_DEC_r8_zf);
    tcase_add_test(test, test_DEC_r8_hf);
    tcase_add_test(test, test_DEC_r8_vf);
    tcase_add_test(test, test_DEC_r8_daa);
    
    return test;
}
