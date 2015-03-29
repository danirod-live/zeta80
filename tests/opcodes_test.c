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

struct cpu_t*
setup_cpu(void)
{
    struct cpu_t* cpu = (struct cpu_t*) malloc(sizeof(struct cpu_t));
    memset(cpu, 0, sizeof(struct cpu_t));
    return cpu;
}

void
teardown_cpu(struct cpu_t* cpu)
{
    free(cpu);
}

START_TEST(extract_opcode_test_x)
{
    struct opcode_t opstr;
    extract_opcode(0xC0, &opstr);
    ck_assert(opstr.x == 3);
    ck_assert(opstr.y == 0);
    ck_assert(opstr.z == 0);
    ck_assert(opstr.p == 0);
    ck_assert(opstr.q == 0);
}
END_TEST

START_TEST(extract_opcode_test_y)
{
    struct opcode_t opstr;
    extract_opcode(0x38, &opstr);
    ck_assert(opstr.x == 0);
    ck_assert(opstr.y == 7);
    ck_assert(opstr.z == 0);
    ck_assert(opstr.p == 3);
    ck_assert(opstr.q == 1);
}
END_TEST

START_TEST(extract_opcode_test_z)
{
    struct opcode_t opstr;
    extract_opcode(0x07, &opstr);
    ck_assert(opstr.x == 0);
    ck_assert(opstr.y == 0);
    ck_assert(opstr.z == 7);
    ck_assert(opstr.p == 0);
    ck_assert(opstr.q == 0);
}
END_TEST

START_TEST(extract_opcode_test_p)
{
    struct opcode_t opstr;
    extract_opcode(0x30, &opstr);
    ck_assert(opstr.x == 0);
    ck_assert(opstr.y == 6);
    ck_assert(opstr.z == 0);
    ck_assert(opstr.p == 3);
    ck_assert(opstr.q == 0);
}
END_TEST

START_TEST(extract_opcode_test_q)
{
    struct opcode_t opstr;
    extract_opcode(0x08, &opstr);
    ck_assert(opstr.x == 0);
    ck_assert(opstr.y == 1);
    ck_assert(opstr.z == 0);
    ck_assert(opstr.p == 0);
    ck_assert(opstr.q == 1);
}
END_TEST

START_TEST(nop_test)
{
    struct cpu_t* cpu = setup_cpu();
    execute_opcode(cpu);
    ck_assert(cpu->tstates == 4);
    teardown_cpu(cpu);
}
END_TEST

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

START_TEST(djnz_d_test)
{
    struct cpu_t* cpu = setup_cpu();
    cpu->mem[0] = 0x10;
    cpu->mem[1] = 0x05;

    cpu->pc.WORD = 0;
    cpu->main.bc.BYTES.H = 2;
    execute_opcode(cpu);
    ck_assert(cpu->main.bc.BYTES.H == 1);
    ck_assert(cpu->pc.WORD == 7);
    ck_assert(cpu->tstates = 13);

    cpu->pc.WORD = 0;
    cpu->main.bc.BYTES.H = 1;
    execute_opcode(cpu);
    ck_assert(cpu->main.bc.BYTES.H == 0);
    ck_assert(cpu->pc.WORD == 2);
    ck_assert(cpu->tstates = 8);

    teardown_cpu(cpu);
}
END_TEST

START_TEST(jr_d_test)
{
    struct cpu_t* cpu = setup_cpu();
    
    // JR 5h
    cpu->mem[0] = 0x18;
    cpu->mem[1] = 0x05;
    execute_opcode(cpu);
    ck_assert(cpu->pc.WORD == 7); // 2 + 5
    ck_assert(cpu->tstates == 12);

    teardown_cpu(cpu);
}
END_TEST

START_TEST(jr_nz_d_test)
{
    struct cpu_t* cpu = setup_cpu();
    cpu->mem[0] = 0x20;
    cpu->mem[1] = 0x05;

    cpu->tstates = 0;
    cpu->pc.WORD = 0;
    RESET_FLAG(cpu->main.af.BYTES.L, FLAG_Z);
    execute_opcode(cpu);
    ck_assert(cpu->pc.WORD == 7);
    ck_assert(cpu->tstates == 12);

    cpu->pc.WORD = 0;
    cpu->tstates = 0;
    SET_FLAG(cpu->main.af.BYTES.L, FLAG_Z);
    execute_opcode(cpu);
    ck_assert(cpu->pc.WORD == 2);
    ck_assert(cpu->tstates == 7);

    teardown_cpu(cpu);
}
END_TEST

START_TEST(jr_z_d_test)
{
    struct cpu_t* cpu = setup_cpu();
    cpu->mem[0] = 0x28;
    cpu->mem[1] = 0x05;

    cpu->tstates = 0;
    cpu->pc.WORD = 0;
    RESET_FLAG(cpu->main.af.BYTES.L, FLAG_Z);
    execute_opcode(cpu);
    ck_assert(cpu->pc.WORD == 2);
    ck_assert(cpu->tstates == 7);

    cpu->pc.WORD = 0;
    cpu->tstates = 0;
    SET_FLAG(cpu->main.af.BYTES.L, FLAG_Z);
    execute_opcode(cpu);
    ck_assert(cpu->pc.WORD == 7);
    ck_assert(cpu->tstates == 12);

    teardown_cpu(cpu);
}
END_TEST

START_TEST(jr_nc_d_test)
{
    struct cpu_t* cpu = setup_cpu();
    cpu->mem[0] = 0x30;
    cpu->mem[1] = 0x05;

    cpu->tstates = 0;
    cpu->pc.WORD = 0;
    RESET_FLAG(cpu->main.af.BYTES.L, FLAG_C);
    execute_opcode(cpu);
    ck_assert(cpu->pc.WORD == 7);
    ck_assert(cpu->tstates == 12);

    cpu->tstates = 0;
    cpu->pc.WORD = 0;
    SET_FLAG(cpu->main.af.BYTES.L, FLAG_C);
    execute_opcode(cpu);
    ck_assert(cpu->pc.WORD == 2);
    ck_assert(cpu->tstates == 7);

    teardown_cpu(cpu);
}
END_TEST

START_TEST(jr_c_d_test)
{
    struct cpu_t* cpu = setup_cpu();
    cpu->mem[0] = 0x38;
    cpu->mem[1] = 0x05;

    cpu->tstates = 0;
    cpu->pc.WORD = 0;
    RESET_FLAG(cpu->main.af.BYTES.L, FLAG_C);
    execute_opcode(cpu);
    ck_assert(cpu->pc.WORD == 2);
    ck_assert(cpu->tstates == 7);

    cpu->pc.WORD = 0;
    cpu->tstates = 0;
    SET_FLAG(cpu->main.af.BYTES.L, FLAG_C);
    execute_opcode(cpu);
    ck_assert(cpu->pc.WORD == 7);
    ck_assert(cpu->tstates == 12);

    teardown_cpu(cpu);
}
END_TEST

START_TEST(ld_bc_nn_test)
{
    struct cpu_t* cpu = setup_cpu();
    cpu->mem[0] = 0x01;
    cpu->mem[1] = 0x34;
    cpu->mem[2] = 0x12;
    execute_opcode(cpu);
    ck_assert(cpu->main.bc.WORD == 0x1234);
    ck_assert(cpu->tstates == 10);
    teardown_cpu(cpu);
}
END_TEST

START_TEST(ld_de_nn_test)
{
    struct cpu_t* cpu = setup_cpu();
    cpu->mem[0] = 0x11;
    cpu->mem[1] = 0x34;
    cpu->mem[2] = 0x12;
    execute_opcode(cpu);
    ck_assert(cpu->main.de.WORD == 0x1234);
    ck_assert(cpu->tstates == 10);
    teardown_cpu(cpu);
}
END_TEST

START_TEST(ld_hl_nn_test)
{
    struct cpu_t* cpu = setup_cpu();
    cpu->mem[0] = 0x21;
    cpu->mem[1] = 0x34;
    cpu->mem[2] = 0x12;
    execute_opcode(cpu);
    ck_assert(cpu->main.hl.WORD == 0x1234);
    ck_assert(cpu->tstates == 10);
    teardown_cpu(cpu);
}
END_TEST

START_TEST(ld_sp_nn_test)
{
    struct cpu_t* cpu = setup_cpu();
    cpu->mem[0] = 0x31;
    cpu->mem[1] = 0x34;
    cpu->mem[2] = 0x12;
    execute_opcode(cpu);
    ck_assert(cpu->sp.WORD == 0x1234);
    ck_assert(cpu->tstates == 10);
    teardown_cpu(cpu);
}
END_TEST

START_TEST(add_hl_bc_test)
{
    struct cpu_t* cpu = setup_cpu();
    cpu->main.hl.WORD = 0x4242;
    cpu->main.bc.WORD = 0x1111;
    cpu->mem[0] = 0x09;
    execute_opcode(cpu);
    ck_assert(cpu->main.hl.WORD == 0x5353);
    // TODO: Check flags
    ck_assert( GET_FLAG(cpu->main.af.BYTES.L, FLAG_N) == 0);
    ck_assert(cpu->tstates == 11);
    teardown_cpu(cpu);
}
END_TEST

START_TEST(add_hl_de_test)
{
    struct cpu_t* cpu = setup_cpu();
    cpu->main.hl.WORD = 0x4242;
    cpu->main.de.WORD = 0x1111;
    cpu->mem[0] = 0x19;
    execute_opcode(cpu);
    ck_assert(cpu->main.hl.WORD == 0x5353);
    // TODO: Check flags
    ck_assert( GET_FLAG(cpu->main.af.BYTES.L, FLAG_N) == 0);
    ck_assert(cpu->tstates == 11);
    teardown_cpu(cpu);
}
END_TEST

START_TEST(add_hl_hl_test)
{
    struct cpu_t* cpu = setup_cpu();
    cpu->main.hl.WORD = 0x4242;
    cpu->mem[0] = 0x29;
    execute_opcode(cpu);
    ck_assert(cpu->main.hl.WORD == 0x8484);
    // TODO: Check flags
    ck_assert( GET_FLAG(cpu->main.af.BYTES.L, FLAG_N) == 0);
    ck_assert(cpu->tstates == 11);
    teardown_cpu(cpu);
}
END_TEST

START_TEST(add_hl_sp_test)
{
    struct cpu_t* cpu = setup_cpu();
    cpu->main.hl.WORD = 0x4242;
    cpu->sp.WORD = 0x1111;
    cpu->mem[0] = 0x39;
    execute_opcode(cpu);
    ck_assert(cpu->main.hl.WORD == 0x5353);
    // TODO: Check flags
    ck_assert( GET_FLAG(cpu->main.af.BYTES.L, FLAG_N) == 0);
    ck_assert(cpu->tstates == 11);
    teardown_cpu(cpu);
}
END_TEST

/**
 * Generate a testsuite for opcodes.
 */
Suite*
gensuite_opcodes(void)
{
    TCase* extract_opcode_test = tcase_create("extract_opcode");
    tcase_add_test(extract_opcode_test, extract_opcode_test_x);
    tcase_add_test(extract_opcode_test, extract_opcode_test_y);
    tcase_add_test(extract_opcode_test, extract_opcode_test_z);
    tcase_add_test(extract_opcode_test, extract_opcode_test_p);
    tcase_add_test(extract_opcode_test, extract_opcode_test_q);

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
    
    Suite* s = suite_create("Opcodes");
    suite_add_tcase(s, extract_opcode_test);
    suite_add_tcase(s, opcodes_test);
    return s;
}


