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

START_TEST(test_NOP)
{
    cpu.mem[0] = 0x00; // NOP
    
    execute_opcode(&cpu);
    
    ck_assert_uint_eq(cpu.tstates, 4);
}
END_TEST

START_TEST(test_EX_AF_AF)
{
    REG_AF(cpu) = 0x1234;
    ALT_AF(cpu) = 0x5678;
    cpu.mem[0] = 0x08; // Opcode for EX AF, AF'
    
    execute_opcode(&cpu);
    
    ck_assert_uint_eq(cpu.tstates, 4);
    ck_assert_uint_eq(0x5678, REG_AF(cpu));
    ck_assert_uint_eq(0x1234, ALT_AF(cpu));
}
END_TEST

START_TEST(test_DJNZ_D_jump)
{
    cpu.mem[0] = 0x10; // DJNZ opcode
    cpu.mem[1] = 0x05; // 05h -> jump 5 bytes.
    REG_B(cpu) = 2; // Set B <= 2 -> The CPU MUST jump.
    
    execute_opcode(&cpu);
    
    ck_assert_uint_eq(0x01, REG_B(cpu));
    ck_assert_uint_eq(7, PC(cpu));
    ck_assert_uint_eq(13, cpu.tstates);
}
END_TEST

START_TEST(test_DJNZ_D_nojump)
{
    cpu.mem[0] = 0x10; // DJNZ opcode
    cpu.mem[1] = 0x05; // 05h -> jump 5 bytes
    REG_B(cpu) = 1; // Set B <= 1 -> The CPU must NOT jump

    execute_opcode(&cpu);
    
    ck_assert_uint_eq(0x00, REG_B(cpu));
    ck_assert_uint_eq(2, PC(cpu));
    ck_assert_uint_eq(8, cpu.tstates);
}
END_TEST

START_TEST(test_JR_D)
{
    cpu.mem[0] = 0x18; // JR opcode
    cpu.mem[1] = 0x05; // 05h -> jump 5 bytes

    execute_opcode(&cpu);
    
    ck_assert_uint_eq(7, PC(cpu)); // 5 + 2
    ck_assert_uint_eq(12, cpu.tstates);
}
END_TEST

START_TEST(test_JR_NZ_D_jump)
{
    cpu.mem[0] = 0x20; // JR NZ opcode
    cpu.mem[1] = 0x05; // 05h -> jump 5 bytes
    FLAG_RST(cpu, FLAG_Z); // Reset zero flag: CPU MUST jump.
    
    execute_opcode(&cpu);
    
    ck_assert_uint_eq(7, PC(cpu));
    ck_assert_uint_eq(12, cpu.tstates);
}
END_TEST

START_TEST(test_JR_NZ_D_nojump)
{
    cpu.mem[0] = 0x20; // JR NZ
    cpu.mem[1] = 0x05; // 05h -> jump 5 bytes
    FLAG_SET(cpu, FLAG_Z); // Set zero flag: CPU must NOT jump.
    
    execute_opcode(&cpu);
    
    ck_assert_uint_eq(2, PC(cpu));
    ck_assert_uint_eq(7, cpu.tstates);
}
END_TEST

START_TEST(test_JR_Z_D_jump)
{
    cpu.mem[0] = 0x28; // JR Z opcode
    cpu.mem[1] = 0x05; // 05h -> jump 5 bytes
    FLAG_RST(cpu, FLAG_Z); // Reset zero flag: CPU must NOT jump
    
    execute_opcode(&cpu);
    
    ck_assert_uint_eq(2, PC(cpu));
    ck_assert_uint_eq(7, cpu.tstates);
}
END_TEST

START_TEST(test_JR_Z_D_nojump)
{
    cpu.mem[0] = 0x28; // JR Z opcode
    cpu.mem[1] = 0x05; // 05h -> jump 5 bytes
    FLAG_SET(cpu, FLAG_Z); // Reset zero flag: CPU must NOT jump
    
    execute_opcode(&cpu);
    
    ck_assert_uint_eq(7, PC(cpu));
    ck_assert_uint_eq(12, cpu.tstates);
}
END_TEST

START_TEST(test_JR_NC_D_jump)
{
    cpu.mem[0] = 0x30; // Opcode for JR NC
    cpu.mem[1] = 0x05; // 05h -> jump 5 bytes
    FLAG_RST(cpu, FLAG_C); // Reset carry flag: CPU MUST jump.
    
    execute_opcode(&cpu);
    
    ck_assert_uint_eq(7, PC(cpu));
    ck_assert_uint_eq(12, cpu.tstates);
}
END_TEST

START_TEST(test_JR_NC_D_nojump)
{
    cpu.mem[0] = 0x30; // Opcode for JR NC
    cpu.mem[1] = 0x05; // 05h -> jump 5 bytes
    FLAG_SET(cpu, FLAG_C); // Set carry flag: CPU must NOT jump.
    
    execute_opcode(&cpu);
    
    ck_assert_uint_eq(2, PC(cpu));
    ck_assert_uint_eq(7, cpu.tstates);
}
END_TEST

START_TEST(test_JR_C_D_nojump)
{
    cpu.mem[0] = 0x38; // Opcode for JR C
    cpu.mem[1] = 0x05; // 05h -> jump 5 bytes
    FLAG_RST(cpu, FLAG_C); // Reset carry flag: CPU must NOT jump
    
    execute_opcode(&cpu);
    
    ck_assert_uint_eq(2, PC(cpu));
    ck_assert_uint_eq(7, cpu.tstates);
}
END_TEST

START_TEST(test_JR_C_D_jump)
{
    cpu.mem[0] = 0x38; // Opcode for JR C
    cpu.mem[1] = 0x05; // 05h -> jump 5 bytes
    FLAG_SET(cpu, FLAG_C); // Set carry flag: CPU MUST jump
    
    execute_opcode(&cpu);
    
    ck_assert_uint_eq(7, PC(cpu));
    ck_assert_uint_eq(12, cpu.tstates);
}
END_TEST

TCase* gen_x0_z0_tcase(void)
{
    TCase* tcase = tcase_create("x=0, z=0");
    tcase_add_checked_fixture(tcase, setup_cpu, teardown_cpu);
    tcase_add_test(tcase, test_NOP);
    tcase_add_test(tcase, test_EX_AF_AF);
    tcase_add_test(tcase, test_DJNZ_D_jump);
    tcase_add_test(tcase, test_DJNZ_D_nojump);
    tcase_add_test(tcase, test_JR_D);
    tcase_add_test(tcase, test_JR_NZ_D_jump);
    tcase_add_test(tcase, test_JR_NZ_D_nojump);
    tcase_add_test(tcase, test_JR_Z_D_jump);
    tcase_add_test(tcase, test_JR_Z_D_nojump);
    tcase_add_test(tcase, test_JR_NC_D_jump);
    tcase_add_test(tcase, test_JR_NC_D_nojump);
    tcase_add_test(tcase, test_JR_C_D_jump);
    tcase_add_test(tcase, test_JR_C_D_nojump);
    return tcase;
}
