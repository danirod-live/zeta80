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
    REG_AF(*cpu) = 0x1234;
    ALT_AF(*cpu) = 0x5678;
    cpu->mem[0] = 0x08; // Opcode for EX AF, AF'
    execute_opcode(cpu);
    ck_assert(cpu->tstates == 4);
    ck_assert(REG_AF(*cpu) == 0x5678);
    ck_assert(ALT_AF(*cpu) == 0x1234);
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
    PC(*cpu) = 0;
    REG_B(*cpu) = 2;
    execute_opcode(cpu);
    ck_assert(REG_B(*cpu) == 1);
    ck_assert(PC(*cpu) == 7);
    ck_assert(cpu->tstates = 13);

    // Set B <= 1 -> The CPU must NOT jump
    cpu->tstates = 0;
    PC(*cpu) = 0;
    REG_B(*cpu) = 1;
    execute_opcode(cpu);
    ck_assert(REG_B(*cpu) == 0);
    ck_assert(PC(*cpu) == 2);
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
    ck_assert(PC(*cpu) == 7); // 2 + 5
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
    PC(*cpu) = 0;
    RESET_FLAG(REG_F(*cpu), FLAG_Z);
    execute_opcode(cpu);
    ck_assert(PC(*cpu) == 7);
    ck_assert(cpu->tstates == 12);

    // Set zero flag: CPU must NOT jump.
    PC(*cpu) = 0;
    cpu->tstates = 0;
    SET_FLAG(REG_F(*cpu), FLAG_Z);
    execute_opcode(cpu);
    ck_assert(PC(*cpu) == 2);
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
    PC(*cpu) = 0;
    RESET_FLAG(REG_F(*cpu), FLAG_Z);
    execute_opcode(cpu);
    ck_assert(PC(*cpu) == 2);
    ck_assert(cpu->tstates == 7);

    // Set zero flag: CPU MUST jump.
    PC(*cpu) = 0;
    cpu->tstates = 0;
    SET_FLAG(REG_F(*cpu), FLAG_Z);
    execute_opcode(cpu);
    ck_assert(PC(*cpu) == 7);
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
    PC(*cpu) = 0;
    RESET_FLAG(REG_F(*cpu), FLAG_C);
    execute_opcode(cpu);
    ck_assert(PC(*cpu) == 7);
    ck_assert(cpu->tstates == 12);

    // Set carry flag: CPU must NOT jump.
    cpu->tstates = 0;
    PC(*cpu) = 0;
    SET_FLAG(REG_F(*cpu), FLAG_C);
    execute_opcode(cpu);
    ck_assert(PC(*cpu) == 2);
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
    PC(*cpu) = 0;
    RESET_FLAG(REG_F(*cpu), FLAG_C);
    execute_opcode(cpu);
    ck_assert(PC(*cpu) == 2);
    ck_assert(cpu->tstates == 7);

    // Set carry flag: CPU MUST jump
    PC(*cpu) = 0;
    cpu->tstates = 0;
    SET_FLAG(REG_F(*cpu), FLAG_C);
    execute_opcode(cpu);
    ck_assert(PC(*cpu) == 7);
    ck_assert(cpu->tstates == 12);

    teardown_cpu(cpu);
}
END_TEST

TCase* gen_x0_z0_tcase(void)
{
    TCase* tcase = tcase_create("x=0 z=0 table");
    tcase_add_test(tcase, nop_test);
    tcase_add_test(tcase, ex_af_af_test);
    tcase_add_test(tcase, djnz_d_test);
    tcase_add_test(tcase, jr_d_test);
    tcase_add_test(tcase, jr_nz_d_test);
    tcase_add_test(tcase, jr_z_d_test);
    tcase_add_test(tcase, jr_nc_d_test);
    tcase_add_test(tcase, jr_c_d_test);
    return tcase;
}
