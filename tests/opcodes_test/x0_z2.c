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

TCase* gen_x0_z2_tcase(void)
{
    TCase* test = tcase_create("x=0 z=2 table");
    tcase_add_test(test, ld_bci_a_test);
    tcase_add_test(test, ld_dei_a_test);
    tcase_add_test(test, ld_a_bci_test);
    tcase_add_test(test, ld_a_dei_test);
    tcase_add_test(test, ld_nni_hl_test);
    tcase_add_test(test, ld_nni_a_test);
    tcase_add_test(test, ld_hl_nni_test);
    tcase_add_test(test, ld_a_nni_test);
    return test;
}
