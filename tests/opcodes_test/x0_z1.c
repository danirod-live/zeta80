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

/* Testcase for LD BC, NN instruction. */
START_TEST(ld_bc_nn_test)
{
    struct cpu_t* cpu = setup_cpu();
    cpu->mem[0] = 0x01; // LD BC
    cpu->mem[1] = 0x34; // 0x..34
    cpu->mem[2] = 0x12; // 0x12..

    execute_opcode(cpu);
    ck_assert(cpu->main.bc.WORD == 0x1234);
    ck_assert(cpu->tstates == 10);
    teardown_cpu(cpu);
}
END_TEST

/* Testcase for LD DE, NN instruction. */
START_TEST(ld_de_nn_test)
{
    struct cpu_t* cpu = setup_cpu();
    cpu->mem[0] = 0x11; // LD DE
    cpu->mem[1] = 0x34; // 0x..34
    cpu->mem[2] = 0x12; // 0x12..

    execute_opcode(cpu);
    ck_assert(cpu->main.de.WORD == 0x1234);
    ck_assert(cpu->tstates == 10);
    teardown_cpu(cpu);
}
END_TEST

/* Testcase for LD HL, NN instruction. */
START_TEST(ld_hl_nn_test)
{
    struct cpu_t* cpu = setup_cpu();
    cpu->mem[0] = 0x21; // LD HL
    cpu->mem[1] = 0x34; // 0x..34
    cpu->mem[2] = 0x12; // 0x12..

    execute_opcode(cpu);
    ck_assert(cpu->main.hl.WORD == 0x1234);
    ck_assert(cpu->tstates == 10);
    teardown_cpu(cpu);
}
END_TEST

/* Testcase for LD SP, NN instruction. */
START_TEST(ld_sp_nn_test)
{
    struct cpu_t* cpu = setup_cpu();
    cpu->mem[0] = 0x31; // LD SP
    cpu->mem[1] = 0x34; // 0x..34
    cpu->mem[2] = 0x12; // 0x12..

    execute_opcode(cpu);
    ck_assert(cpu->sp.WORD == 0x1234);
    ck_assert(cpu->tstates == 10);
    teardown_cpu(cpu);
}
END_TEST

/* Testcase for ADD HL, BC instruction. */
START_TEST(add_hl_bc_test)
{
    struct cpu_t* cpu = setup_cpu();
    cpu->mem[0] = 0x09; // ADD HL, BC

    cpu->pc.WORD = 0;
    cpu->tstates = 0;
    cpu->main.hl.WORD = 0x4242;
    cpu->main.bc.WORD = 0x1111;
    execute_opcode(cpu);
    ck_assert(cpu->main.hl.WORD == 0x5353);
    ck_assert(GET_FLAG(cpu->main.af.BYTES.L, FLAG_C) == 0);
    ck_assert(GET_FLAG(cpu->main.af.BYTES.L, FLAG_H) == 0);
    ck_assert(GET_FLAG(cpu->main.af.BYTES.L, FLAG_N) == 0);
    ck_assert(cpu->tstates == 11);

    cpu->pc.WORD = 0;
    cpu->tstates = 0;
    cpu->main.hl.WORD = 0x0800;
    cpu->main.bc.WORD = 0x0800;
    execute_opcode(cpu);
    ck_assert(cpu->main.hl.WORD == 0x1000);
    ck_assert(GET_FLAG(cpu->main.af.BYTES.L, FLAG_C) == 0);
    ck_assert(GET_FLAG(cpu->main.af.BYTES.L, FLAG_H) == 1);
    ck_assert(GET_FLAG(cpu->main.af.BYTES.L, FLAG_N) == 0);
    ck_assert(cpu->tstates == 11);

    cpu->pc.WORD = 0;
    cpu->tstates = 0;
    cpu->main.hl.WORD = 0x8000;
    cpu->main.bc.WORD = 0x8000;
    execute_opcode(cpu);
    ck_assert(cpu->main.hl.WORD == 0x0000);
    ck_assert(GET_FLAG(cpu->main.af.BYTES.L, FLAG_C) == 1);
    ck_assert(GET_FLAG(cpu->main.af.BYTES.L, FLAG_H) == 0);
    ck_assert(GET_FLAG(cpu->main.af.BYTES.L, FLAG_N) == 0);
    ck_assert(cpu->tstates == 11);

    cpu->pc.WORD = 0;
    cpu->tstates = 0;
    cpu->main.hl.WORD = 0x8800;
    cpu->main.bc.WORD = 0x8800;
    execute_opcode(cpu);
    ck_assert(cpu->main.hl.WORD == 0x1000);
    ck_assert(GET_FLAG(cpu->main.af.BYTES.L, FLAG_C) == 1);
    ck_assert(GET_FLAG(cpu->main.af.BYTES.L, FLAG_H) == 1);
    ck_assert(GET_FLAG(cpu->main.af.BYTES.L, FLAG_N) == 0);
    ck_assert(cpu->tstates == 11);

    teardown_cpu(cpu);
}
END_TEST

/* Testcase for ADD HL, DE instruction. */
START_TEST(add_hl_de_test)
{
    struct cpu_t* cpu = setup_cpu();
    cpu->mem[0] = 0x19; // ADD HL, DE

    cpu->pc.WORD = 0;
    cpu->tstates = 0;
    cpu->main.hl.WORD = 0x4242;
    cpu->main.de.WORD = 0x1111;
    execute_opcode(cpu);
    ck_assert(cpu->main.hl.WORD == 0x5353);
    ck_assert(GET_FLAG(cpu->main.af.BYTES.L, FLAG_C) == 0);
    ck_assert(GET_FLAG(cpu->main.af.BYTES.L, FLAG_H) == 0);
    ck_assert(GET_FLAG(cpu->main.af.BYTES.L, FLAG_N) == 0);
    ck_assert(cpu->tstates == 11);

    cpu->pc.WORD = 0;
    cpu->tstates = 0;
    cpu->main.hl.WORD = 0x0800;
    cpu->main.de.WORD = 0x0800;
    execute_opcode(cpu);
    ck_assert(cpu->main.hl.WORD == 0x1000);
    ck_assert(GET_FLAG(cpu->main.af.BYTES.L, FLAG_C) == 0);
    ck_assert(GET_FLAG(cpu->main.af.BYTES.L, FLAG_H) == 1);
    ck_assert(GET_FLAG(cpu->main.af.BYTES.L, FLAG_N) == 0);
    ck_assert(cpu->tstates == 11);

    cpu->pc.WORD = 0;
    cpu->tstates = 0;
    cpu->main.hl.WORD = 0x8000;
    cpu->main.de.WORD = 0x8000;
    execute_opcode(cpu);
    ck_assert(cpu->main.hl.WORD == 0x0000);
    ck_assert(GET_FLAG(cpu->main.af.BYTES.L, FLAG_C) == 1);
    ck_assert(GET_FLAG(cpu->main.af.BYTES.L, FLAG_H) == 0);
    ck_assert(GET_FLAG(cpu->main.af.BYTES.L, FLAG_N) == 0);
    ck_assert(cpu->tstates == 11);

    cpu->pc.WORD = 0;
    cpu->tstates = 0;
    cpu->main.hl.WORD = 0x8800;
    cpu->main.de.WORD = 0x8800;
    execute_opcode(cpu);
    ck_assert(cpu->main.hl.WORD == 0x1000);
    ck_assert(GET_FLAG(cpu->main.af.BYTES.L, FLAG_C) == 1);
    ck_assert(GET_FLAG(cpu->main.af.BYTES.L, FLAG_H) == 1);
    ck_assert(GET_FLAG(cpu->main.af.BYTES.L, FLAG_N) == 0);
    ck_assert(cpu->tstates == 11);

    teardown_cpu(cpu);
}
END_TEST

/* Testcase for ADD HL, HL instruction. */
START_TEST(add_hl_hl_test)
{
    struct cpu_t* cpu = setup_cpu();
    cpu->mem[0] = 0x29; // ADD HL, HL

    cpu->pc.WORD = 0;
    cpu->tstates = 0;
    cpu->main.hl.WORD = 0x4242;
    execute_opcode(cpu);
    ck_assert(cpu->main.hl.WORD == 0x8484);
    ck_assert(GET_FLAG(cpu->main.af.BYTES.L, FLAG_C) == 0);
    ck_assert(GET_FLAG(cpu->main.af.BYTES.L, FLAG_H) == 0);
    ck_assert(GET_FLAG(cpu->main.af.BYTES.L, FLAG_N) == 0);
    ck_assert(cpu->tstates == 11);

    cpu->pc.WORD = 0;
    cpu->tstates = 0;
    cpu->main.hl.WORD = 0x0800;
    execute_opcode(cpu);
    ck_assert(cpu->main.hl.WORD == 0x1000);
    ck_assert(GET_FLAG(cpu->main.af.BYTES.L, FLAG_C) == 0);
    ck_assert(GET_FLAG(cpu->main.af.BYTES.L, FLAG_H) == 1);
    ck_assert(GET_FLAG(cpu->main.af.BYTES.L, FLAG_N) == 0);
    ck_assert(cpu->tstates == 11);

    cpu->pc.WORD = 0;
    cpu->tstates = 0;
    cpu->main.hl.WORD = 0x8000;
    execute_opcode(cpu);
    ck_assert(cpu->main.hl.WORD == 0x0000);
    ck_assert(GET_FLAG(cpu->main.af.BYTES.L, FLAG_C) == 1);
    ck_assert(GET_FLAG(cpu->main.af.BYTES.L, FLAG_H) == 0);
    ck_assert(GET_FLAG(cpu->main.af.BYTES.L, FLAG_N) == 0);
    ck_assert(cpu->tstates == 11);

    cpu->pc.WORD = 0;
    cpu->tstates = 0;
    cpu->main.hl.WORD = 0x8800;
    execute_opcode(cpu);
    ck_assert(cpu->main.hl.WORD == 0x1000);
    ck_assert(GET_FLAG(cpu->main.af.BYTES.L, FLAG_C) == 1);
    ck_assert(GET_FLAG(cpu->main.af.BYTES.L, FLAG_H) == 1);
    ck_assert(GET_FLAG(cpu->main.af.BYTES.L, FLAG_N) == 0);
    ck_assert(cpu->tstates == 11);

    teardown_cpu(cpu);
}
END_TEST

/* Testcase for ADD HL, SP instruction. */
START_TEST(add_hl_sp_test)
{
    struct cpu_t* cpu = setup_cpu();
    cpu->mem[0] = 0x39; // ADD HL, SP

    cpu->pc.WORD = 0;
    cpu->tstates = 0;
    cpu->main.hl.WORD = 0x4242;
    cpu->sp.WORD = 0x1111;
    execute_opcode(cpu);
    ck_assert(cpu->main.hl.WORD == 0x5353);
    ck_assert(GET_FLAG(cpu->main.af.BYTES.L, FLAG_C) == 0);
    ck_assert(GET_FLAG(cpu->main.af.BYTES.L, FLAG_H) == 0);
    ck_assert(GET_FLAG(cpu->main.af.BYTES.L, FLAG_N) == 0);
    ck_assert(cpu->tstates == 11);

    cpu->pc.WORD = 0;
    cpu->tstates = 0;
    cpu->main.hl.WORD = 0x0800;
    cpu->sp.WORD = 0x0800;
    execute_opcode(cpu);
    ck_assert(cpu->main.hl.WORD == 0x1000);
    ck_assert(GET_FLAG(cpu->main.af.BYTES.L, FLAG_C) == 0);
    ck_assert(GET_FLAG(cpu->main.af.BYTES.L, FLAG_H) == 1);
    ck_assert(GET_FLAG(cpu->main.af.BYTES.L, FLAG_N) == 0);
    ck_assert(cpu->tstates == 11);

    cpu->pc.WORD = 0;
    cpu->tstates = 0;
    cpu->main.hl.WORD = 0x8000;
    cpu->sp.WORD = 0x8000;
    execute_opcode(cpu);
    ck_assert(cpu->main.hl.WORD == 0x0000);
    ck_assert(GET_FLAG(cpu->main.af.BYTES.L, FLAG_C) == 1);
    ck_assert(GET_FLAG(cpu->main.af.BYTES.L, FLAG_H) == 0);
    ck_assert(GET_FLAG(cpu->main.af.BYTES.L, FLAG_N) == 0);
    ck_assert(cpu->tstates == 11);

    cpu->pc.WORD = 0;
    cpu->tstates = 0;
    cpu->main.hl.WORD = 0x8800;
    cpu->sp.WORD = 0x8800;
    execute_opcode(cpu);
    ck_assert(cpu->main.hl.WORD == 0x1000);
    ck_assert(GET_FLAG(cpu->main.af.BYTES.L, FLAG_C) == 1);
    ck_assert(GET_FLAG(cpu->main.af.BYTES.L, FLAG_H) == 1);
    ck_assert(GET_FLAG(cpu->main.af.BYTES.L, FLAG_N) == 0);
    ck_assert(cpu->tstates == 11);

    teardown_cpu(cpu);
}
END_TEST

TCase* gen_x0_z1_tcase(void)
{
    TCase* test = tcase_create("x=0 z=1 table");
    tcase_add_test(test, ld_bc_nn_test);
    tcase_add_test(test, ld_de_nn_test);
    tcase_add_test(test, ld_hl_nn_test);
    tcase_add_test(test, ld_sp_nn_test);
    tcase_add_test(test, add_hl_bc_test);
    tcase_add_test(test, add_hl_de_test);
    tcase_add_test(test, add_hl_hl_test);
    tcase_add_test(test, add_hl_sp_test);
    return test;
}
