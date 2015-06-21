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

#include "../opcodes_test.h"

START_TEST(test_INC_BC)
{
    cpu.mem[0] = 0x03;
    REG_BC(cpu) = 0x1234;
    
    execute_opcode(&cpu);
    
    ck_assert_uint_eq(0x1235, REG_BC(cpu));
    ck_assert_uint_eq(6, cpu.tstates);
}
END_TEST

START_TEST(test_INC_DE)
{
    cpu.mem[0] = 0x13;
    REG_DE(cpu) = 0x1234;
    
    execute_opcode(&cpu);
    
    ck_assert_uint_eq(0x1235, REG_DE(cpu));
    ck_assert_uint_eq(6, cpu.tstates);
}
END_TEST

START_TEST(test_INC_HL)
{
    cpu.mem[0] = 0x23;
    REG_HL(cpu) = 0x1234;
    
    execute_opcode(&cpu);
    
    ck_assert_uint_eq(0x1235, REG_HL(cpu));
    ck_assert_uint_eq(6, cpu.tstates);
}
END_TEST

START_TEST(test_INC_SP)
{
    cpu.mem[0] = 0x33;
    SP(cpu) = 0x1234;
    
    execute_opcode(&cpu);
    
    ck_assert_uint_eq(0x1235, SP(cpu));
    ck_assert_uint_eq(6, cpu.tstates);
}
END_TEST

START_TEST(test_DEC_BC)
{
    cpu.mem[0] = 0x0B;
    REG_BC(cpu) = 0x1234;
    
    execute_opcode(&cpu);
    
    ck_assert_uint_eq(0x1233, REG_BC(cpu));
    ck_assert_uint_eq(6, cpu.tstates);
}
END_TEST

START_TEST(test_DEC_DE)
{
    cpu.mem[0] = 0x1B;
    REG_DE(cpu) = 0x1234;
    
    execute_opcode(&cpu);
    
    ck_assert_uint_eq(0x1233, REG_DE(cpu));
    ck_assert_uint_eq(6, cpu.tstates);
}
END_TEST

START_TEST(test_DEC_HL)
{
    cpu.mem[0] = 0x2B;
    REG_HL(cpu) = 0x1234;
    
    execute_opcode(&cpu);
    
    ck_assert_uint_eq(0x1233, REG_HL(cpu));
    ck_assert_uint_eq(6, cpu.tstates);
}
END_TEST

START_TEST(test_DEC_SP)
{
    cpu.mem[0] = 0x3B;
    SP(cpu) = 0x1234;
    
    execute_opcode(&cpu);
    
    ck_assert_uint_eq(0x1233, SP(cpu));
    ck_assert_uint_eq(6, cpu.tstates);
}
END_TEST

TCase* gen_x0_z3_tcase(void)
{
    TCase* test = tcase_create("x=0, z=3");
    tcase_add_test(test, test_INC_BC);
    tcase_add_test(test, test_INC_DE);
    tcase_add_test(test, test_INC_HL);
    tcase_add_test(test, test_INC_SP);
    tcase_add_test(test, test_DEC_BC);
    tcase_add_test(test, test_DEC_DE);
    tcase_add_test(test, test_DEC_HL);
    tcase_add_test(test, test_DEC_SP);
    return test;
}
