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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cpu.h"
#include "opcodes.h"
#include "types.h"

#include "opcodes_test/extract_opcodes.h"

struct cpu_t*
setup_cpu(void)
{
    struct cpu_t* cpu = (struct cpu_t*) malloc(sizeof(struct cpu_t));

    // See section 2.4 from The Undocumented Z80 Documented.
    memset(cpu, 0xFF, sizeof(struct cpu_t));
    cpu->pc.WORD = 0;
    cpu->tstates = 0;
    return cpu;
}

void
teardown_cpu(struct cpu_t* cpu)
{
    free(cpu);
}

/* Testcase for NOP instruction. */
START_TEST(nop_test)
{
    struct cpu_t* cpu = setup_cpu();
    cpu->mem[0] = 0x00; // NOP

    execute_opcode(cpu);
    ck_assert(cpu->tstates == 4);
    teardown_cpu(cpu);
}
END_TEST

/* Testcase for EX AF, AF' instruction. */
START_TEST(ex_af_af_test)
{
    struct cpu_t* cpu = setup_cpu();
    cpu->main.af.WORD = 0x1234;
    cpu->alternate.af.WORD = 0x5678;
    cpu->mem[0] = 0x08; // Opcode for EX AF, AF'
    execute_opcode(cpu);
    ck_assert(cpu->tstates == 4);
    ck_assert(cpu->main.af.WORD == 0x5678);
    ck_assert(cpu->alternate.af.WORD == 0x1234);
    teardown_cpu(cpu);
}
END_TEST

/* Testcase for DJNZ D instruction. */
START_TEST(djnz_d_test)
{
    struct cpu_t* cpu = setup_cpu();
    cpu->mem[0] = 0x10; // DJNZ opcode
    cpu->mem[1] = 0x05; // 05h -> jump 5 bytes.

    // Set B <= 2 -> The CPU MUST jump.
    cpu->tstates = 0;
    cpu->pc.WORD = 0;
    cpu->main.bc.BYTES.H = 2;
    execute_opcode(cpu);
    ck_assert(cpu->main.bc.BYTES.H == 1);
    ck_assert(cpu->pc.WORD == 7);
    ck_assert(cpu->tstates = 13);

    // Set B <= 1 -> The CPU must NOT jump
    cpu->tstates = 0;
    cpu->pc.WORD = 0;
    cpu->main.bc.BYTES.H = 1;
    execute_opcode(cpu);
    ck_assert(cpu->main.bc.BYTES.H == 0);
    ck_assert(cpu->pc.WORD == 2);
    ck_assert(cpu->tstates = 8);

    teardown_cpu(cpu);
}
END_TEST

/* Testcase for JR D instruction. */
START_TEST(jr_d_test)
{
    struct cpu_t* cpu = setup_cpu();
    cpu->mem[0] = 0x18; // JR opcode
    cpu->mem[1] = 0x05; // 05h -> jump 5 bytes

    execute_opcode(cpu);
    ck_assert(cpu->pc.WORD == 7); // 2 + 5
    ck_assert(cpu->tstates == 12);

    teardown_cpu(cpu);
}
END_TEST

/* Testcase for JR NZ, D instruction. */
START_TEST(jr_nz_d_test)
{
    struct cpu_t* cpu = setup_cpu();
    cpu->mem[0] = 0x20; // JR NZ opcode
    cpu->mem[1] = 0x05; // 05h -> jump 5 bytes

    // Reset zero flag: CPU MUST jump.
    cpu->tstates = 0;
    cpu->pc.WORD = 0;
    RESET_FLAG(cpu->main.af.BYTES.L, FLAG_Z);
    execute_opcode(cpu);
    ck_assert(cpu->pc.WORD == 7);
    ck_assert(cpu->tstates == 12);

    // Set zero flag: CPU must NOT jump.
    cpu->pc.WORD = 0;
    cpu->tstates = 0;
    SET_FLAG(cpu->main.af.BYTES.L, FLAG_Z);
    execute_opcode(cpu);
    ck_assert(cpu->pc.WORD == 2);
    ck_assert(cpu->tstates == 7);

    teardown_cpu(cpu);
}
END_TEST

/* Testcase for JR Z, D instruction. */
START_TEST(jr_z_d_test)
{
    struct cpu_t* cpu = setup_cpu();
    cpu->mem[0] = 0x28; // JR Z opcode
    cpu->mem[1] = 0x05; // 05h -> jump 5 bytes

    // Reset zero flag: CPU must NOT jump.
    cpu->tstates = 0;
    cpu->pc.WORD = 0;
    RESET_FLAG(cpu->main.af.BYTES.L, FLAG_Z);
    execute_opcode(cpu);
    ck_assert(cpu->pc.WORD == 2);
    ck_assert(cpu->tstates == 7);

    // Set zero flag: CPU MUST jump.
    cpu->pc.WORD = 0;
    cpu->tstates = 0;
    SET_FLAG(cpu->main.af.BYTES.L, FLAG_Z);
    execute_opcode(cpu);
    ck_assert(cpu->pc.WORD == 7);
    ck_assert(cpu->tstates == 12);

    teardown_cpu(cpu);
}
END_TEST

/* Testcase for JR NC, D instruction. */
START_TEST(jr_nc_d_test)
{
    struct cpu_t* cpu = setup_cpu();
    cpu->mem[0] = 0x30; // Opcode for JR NC
    cpu->mem[1] = 0x05; // 05h -> jump 5 bytes

    // Reset carry flag: CPU MUST jump.
    cpu->tstates = 0;
    cpu->pc.WORD = 0;
    RESET_FLAG(cpu->main.af.BYTES.L, FLAG_C);
    execute_opcode(cpu);
    ck_assert(cpu->pc.WORD == 7);
    ck_assert(cpu->tstates == 12);

    // Set carry flag: CPU must NOT jump.
    cpu->tstates = 0;
    cpu->pc.WORD = 0;
    SET_FLAG(cpu->main.af.BYTES.L, FLAG_C);
    execute_opcode(cpu);
    ck_assert(cpu->pc.WORD == 2);
    ck_assert(cpu->tstates == 7);

    teardown_cpu(cpu);
}
END_TEST

/* Testcase for JR C, D instruction. */
START_TEST(jr_c_d_test)
{
    struct cpu_t* cpu = setup_cpu();
    cpu->mem[0] = 0x38; // Opcode for JR C
    cpu->mem[1] = 0x05; // 05h -> jump 5 bytes

    // Reset carry flag: CPU must NOT jump
    cpu->tstates = 0;
    cpu->pc.WORD = 0;
    RESET_FLAG(cpu->main.af.BYTES.L, FLAG_C);
    execute_opcode(cpu);
    ck_assert(cpu->pc.WORD == 2);
    ck_assert(cpu->tstates == 7);

    // Set carry flag: CPU MUST jump
    cpu->pc.WORD = 0;
    cpu->tstates = 0;
    SET_FLAG(cpu->main.af.BYTES.L, FLAG_C);
    execute_opcode(cpu);
    ck_assert(cpu->pc.WORD == 7);
    ck_assert(cpu->tstates == 12);

    teardown_cpu(cpu);
}
END_TEST

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
    printf("%x\n", cpu->main.af.BYTES.L);
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

/* Test for LD (BC), A instruction. */
START_TEST(ld_bci_a_test)
{
    struct cpu_t* cpu = setup_cpu();
    cpu->mem[0] = 0x02; // LD (BC); A

    cpu->main.bc.WORD = 0x8000;
    cpu->main.af.BYTES.H = 0x55;
    execute_opcode(cpu);
    ck_assert(cpu->mem[0x8000] == 0x55);
    ck_assert(cpu->tstates == 7);

    teardown_cpu(cpu);
}
END_TEST

/* Test for LD (DE), A instruction. */
START_TEST(ld_dei_a_test)
{
    struct cpu_t* cpu = setup_cpu();
    cpu->mem[0] = 0x12; // LD (DE), A

    cpu->main.de.WORD = 0x8000;
    cpu->main.af.BYTES.H = 0x55;
    execute_opcode(cpu);
    ck_assert(cpu->mem[0x8000] == 0x55);
    ck_assert(cpu->tstates == 7);

    teardown_cpu(cpu);
}
END_TEST

/* Test for LD (NN), HL instruction. */
START_TEST(ld_nni_hl_test)
{
    struct cpu_t* cpu = setup_cpu();
    cpu->mem[0] = 0x22; // LD (NN), HL
    cpu->mem[1] = 0x00; // 0x..00
    cpu->mem[2] = 0x80; // 0x80..

    cpu->main.hl.WORD = 0x1234;
    execute_opcode(cpu);
    ck_assert(cpu->mem[0x8000] = 0x34);
    ck_assert(cpu->mem[0x8001] = 0x12);
    ck_assert(cpu->tstates == 16);

    teardown_cpu(cpu);
}
END_TEST

/* Test for LD (NN), A instruction. */
START_TEST(ld_nni_a_test)
{
    struct cpu_t* cpu = setup_cpu();
    cpu->mem[0] = 0x32; // LD (NN), A
    cpu->mem[1] = 0x00; // 0x..00
    cpu->mem[2] = 0x80; // 0x80..

    cpu->main.af.BYTES.H = 0x55;
    execute_opcode(cpu);
    ck_assert(cpu->mem[0x8000] = 0x55);
    ck_assert(cpu->tstates == 13);

    teardown_cpu(cpu);
}
END_TEST

/* Test for LD A, (BC) instruction. */
START_TEST(ld_a_bci_test)
{
    struct cpu_t* cpu = setup_cpu();
    cpu->mem[0] = 0x0A; // LD A, (BC)

    cpu->main.bc.WORD = 0x8000;
    cpu->mem[0x8000] = 0x55;
    execute_opcode(cpu);
    ck_assert(cpu->main.af.BYTES.H == 0x55);
    ck_assert(cpu->tstates == 7);

    teardown_cpu(cpu);
}
END_TEST

/* Test for LD A, (DE) instruction. */
START_TEST(ld_a_dei_test)
{
    struct cpu_t* cpu = setup_cpu();
    cpu->mem[0] = 0x1A; // LD A, (DE)

    cpu->main.de.WORD = 0x8000;
    cpu->mem[0x8000] = 0x55;
    execute_opcode(cpu);
    ck_assert(cpu->main.af.BYTES.H == 0x55);
    ck_assert(cpu->tstates == 7);

    teardown_cpu(cpu);
}
END_TEST

/* Test for LD HL, (NN) instruction. */
START_TEST(ld_hl_nni_test)
{
    struct cpu_t* cpu = setup_cpu();
    cpu->mem[0] = 0x2A; // LD HL, (NN)

    cpu->mem[0x8000] = 0x34; // 0x..34
    cpu->mem[0x8001] = 0x12; // 0x12..
    execute_opcode(cpu);
    ck_assert(cpu->main.hl.WORD == 0x1234);
    ck_assert(cpu->tstates == 16);

    teardown_cpu(cpu);
}
END_TEST

/* Test for LD A, (NN) instruction. */
START_TEST(ld_a_nni_test)
{
    struct cpu_t* cpu = setup_cpu();
    cpu->mem[0] = 0x3A; // LD A, (NN)

    cpu->mem[0x8000] = 0x55;
    execute_opcode(cpu);
    ck_assert(cpu->main.af.BYTES.H == 0x55);
    ck_assert(cpu->tstates == 13);

    teardown_cpu(cpu);
}
END_TEST

/**
 * Generate a testsuite for opcodes.
 */
Suite*
gensuite_opcodes(void)
{
    TCase* extract_opcodes_tcase = gen_extract_opcode_tcase();
    TCase* opcodes_test = tcase_create("opcodes");
    tcase_add_test(opcodes_test, nop_test);
    tcase_add_test(opcodes_test, ex_af_af_test);
    tcase_add_test(opcodes_test, djnz_d_test);
    tcase_add_test(opcodes_test, jr_d_test);
    tcase_add_test(opcodes_test, jr_nz_d_test);
    tcase_add_test(opcodes_test, jr_z_d_test);
    tcase_add_test(opcodes_test, jr_nc_d_test);
    tcase_add_test(opcodes_test, jr_c_d_test);
    tcase_add_test(opcodes_test, ld_bc_nn_test);
    tcase_add_test(opcodes_test, ld_de_nn_test);
    tcase_add_test(opcodes_test, ld_hl_nn_test);
    tcase_add_test(opcodes_test, ld_sp_nn_test);
    tcase_add_test(opcodes_test, add_hl_bc_test);
    tcase_add_test(opcodes_test, add_hl_de_test);
    tcase_add_test(opcodes_test, add_hl_hl_test);
    tcase_add_test(opcodes_test, add_hl_sp_test);
    tcase_add_test(opcodes_test, ld_bci_a_test);
    tcase_add_test(opcodes_test, ld_dei_a_test);
    tcase_add_test(opcodes_test, ld_a_bci_test);
    tcase_add_test(opcodes_test, ld_a_dei_test);
    tcase_add_test(opcodes_test, ld_nni_hl_test);
    tcase_add_test(opcodes_test, ld_nni_a_test);
    tcase_add_test(opcodes_test, ld_hl_nni_test);
    tcase_add_test(opcodes_test, ld_a_nni_test);

    Suite* s = suite_create("Opcodes");
    suite_add_tcase(s, extract_opcodes_tcase);
    suite_add_tcase(s, opcodes_test);
    return s;
}
