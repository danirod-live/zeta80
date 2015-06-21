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

START_TEST(test_RET_NZ_jump)
{
    cpu.mem[0] = 0xC0;
    PC(cpu) = 0x1234;
    cpu.mem[SP(cpu)--] = 0x56;
    cpu.mem[SP(cpu)--] = 0x34;
    FLAG_RST(cpu, FLAG_Z);
    execute_opcode(&cpu);
    ck_assert_uint_eq(0x3456, PC(cpu));
    ck_assert_uint_eq(11, cpu.tstates);
}
END_TEST

START_TEST(test_RET_NZ_nojump)
{
    cpu.mem[0] = 0xC0;
    PC(cpu) = 0x1234;
    cpu.mem[SP(cpu)--] = 0x56;
    cpu.mem[SP(cpu)--] = 0x34;
    FLAG_SET(cpu, FLAG_Z);
    execute_opcode(&cpu);
    ck_assert_uint_eq(0x1235, PC(cpu));
    ck_assert_uint_eq(5, cpu.tstates);
}
END_TEST

START_TEST(test_RET_Z_jump)
{
    cpu.mem[0] = 0xC8;
    PC(cpu) = 0x1234;
    cpu.mem[SP(cpu)--] = 0x56;
    cpu.mem[SP(cpu)--] = 0x34;
    FLAG_SET(cpu, FLAG_Z);
    execute_opcode(&cpu);
    ck_assert_uint_eq(0x3456, PC(cpu));
    ck_assert_uint_eq(11, cpu.tstates);
}
END_TEST

START_TEST(test_RET_Z_nojump)
{
    cpu.mem[0] = 0xC8;
    PC(cpu) = 0x1234;
    cpu.mem[SP(cpu)--] = 0x56;
    cpu.mem[SP(cpu)--] = 0x34;
    FLAG_RST(cpu, FLAG_Z);
    execute_opcode(&cpu);
    ck_assert_uint_eq(0x1235, PC(cpu));
    ck_assert_uint_eq(5, cpu.tstates);
}
END_TEST

START_TEST(test_RET_NC_jump)
{
    cpu.mem[0] = 0xD0;
    PC(cpu) = 0x1234;
    cpu.mem[SP(cpu)--] = 0x56;
    cpu.mem[SP(cpu)--] = 0x34;
    FLAG_RST(cpu, FLAG_C);
    execute_opcode(&cpu);
    ck_assert_uint_eq(0x3456, PC(cpu));
    ck_assert_uint_eq(11, cpu.tstates);
}
END_TEST

START_TEST(test_RET_NC_nojump)
{
    cpu.mem[0] = 0xD0;
    PC(cpu) = 0x1234;
    cpu.mem[SP(cpu)--] = 0x56;
    cpu.mem[SP(cpu)--] = 0x34;
    FLAG_SET(cpu, FLAG_C);
    execute_opcode(&cpu);
    ck_assert_uint_eq(0x1235, PC(cpu));
    ck_assert_uint_eq(5, cpu.tstates);
}
END_TEST

START_TEST(test_RET_C_jump)
{
    cpu.mem[0] = 0xC8;
    PC(cpu) = 0x1234;
    cpu.mem[SP(cpu)--] = 0x56;
    cpu.mem[SP(cpu)--] = 0x34;
    FLAG_SET(cpu, FLAG_C);
    execute_opcode(&cpu);
    ck_assert_uint_eq(0x3456, PC(cpu));
    ck_assert_uint_eq(11, cpu.tstates);
}
END_TEST

START_TEST(test_RET_C_nojump)
{
    cpu.mem[0] = 0xC8;
    PC(cpu) = 0x1234;
    cpu.mem[SP(cpu)--] = 0x56;
    cpu.mem[SP(cpu)--] = 0x34;
    FLAG_RST(cpu, FLAG_C);
    execute_opcode(&cpu);
    ck_assert_uint_eq(0x1235, PC(cpu));
    ck_assert_uint_eq(5, cpu.tstates);
}
END_TEST

TCase* gen_x3_z0_tcase()
{
    TCase* test = tcase_create("x=3, z=0");
    tcase_add_checked_fixture(test, setup_cpu, teardown_cpu);
    tcase_add_test(test, test_RET_NZ_jump);
    tcase_add_test(test, test_RET_NZ_nojump);
    tcase_add_test(test, test_RET_Z_jump);
    tcase_add_test(test, test_RET_Z_nojump);
    tcase_add_test(test, test_RET_NC_jump);
    tcase_add_test(test, test_RET_NC_nojump);
    tcase_add_test(test, test_RET_C_jump);
    tcase_add_test(test, test_RET_C_nojump);
    return test;
}
