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
#include <stdlib.h>         // malloc, free
#include <string.h>         // memset

#include <cpu.h>
#include <opcodes.h>

#include "opcodes_test.h"

void
setup_cpu(void)
{
    // See section 2.4 from The Undocumented Z80 Documented.
    memset(&cpu, 0xFF, sizeof(struct cpu_t));
    PC(cpu) = 0;
    cpu.tstates = 0;
}

void
teardown_cpu(void)
{
    // No actually teardown.
}

/**
 * Generate a testsuite for opcodes.
 */
Suite*
gensuite_opcodes(void)
{
    Suite* s = suite_create("Opcodes");
    suite_add_tcase(s, gen_extract_opcode_tcase());
    suite_add_tcase(s, gen_x0_z0_tcase());
    suite_add_tcase(s, gen_x0_z1_tcase());
    suite_add_tcase(s, gen_x0_z2_tcase());
    suite_add_tcase(s, gen_x0_z3_tcase());
    suite_add_tcase(s, gen_x0_z4_tcase());
    suite_add_tcase(s, gen_x0_z5_tcase());
    suite_add_tcase(s, gen_x0_z6_tcase());
    suite_add_tcase(s, gen_x0_z7_tcase());
    suite_add_tcase(s, gen_x1_z0_tcase());
    suite_add_tcase(s, gen_x1_z1_tcase());
    suite_add_tcase(s, gen_x1_z2_tcase());
    suite_add_tcase(s, gen_x1_z3_tcase());
    suite_add_tcase(s, gen_x1_z4_tcase());
    suite_add_tcase(s, gen_x1_z5_tcase());
    suite_add_tcase(s, gen_x1_z6_tcase());
    suite_add_tcase(s, gen_x1_z7_tcase());
    return s;
}
