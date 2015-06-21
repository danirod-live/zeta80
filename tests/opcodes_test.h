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

#ifndef OPCODES_TEST_H_
#define OPCODES_TEST_H_

#include <check.h>

#include <cpu.h>

// Setup and teardown functions for test case fixtures.
// cpu has to be global since fixture setup/teardown can't have arguments.
struct cpu_t cpu;
void setup_cpu(void);
void teardown_cpu(void);

// Different suites
Suite* gensuite_opcodes(void);

// Different test cases.
TCase* gen_extract_opcode_tcase(void);
TCase* gen_x0_z0_tcase(void);
TCase* gen_x0_z1_tcase(void);
TCase* gen_x0_z2_tcase(void);
TCase* gen_x0_z3_tcase(void);
TCase* gen_x0_z4_tcase(void);
TCase* gen_x0_z5_tcase(void);
TCase* gen_x0_z6_tcase(void);
TCase* gen_x0_z7_tcase(void);
TCase* gen_x1_z0_tcase(void);
TCase* gen_x1_z1_tcase(void);
TCase* gen_x1_z2_tcase(void);
TCase* gen_x1_z3_tcase(void);
TCase* gen_x1_z4_tcase(void);
TCase* gen_x1_z5_tcase(void);
TCase* gen_x1_z6_tcase(void);
TCase* gen_x1_z7_tcase(void);
TCase* gen_x2_z0_tcase(void);
TCase* gen_x2_z1_tcase(void);
TCase* gen_x2_z2_tcase(void);
TCase* gen_x2_z3_tcase(void);
TCase* gen_x2_z4_tcase(void);
TCase* gen_x2_z5_tcase(void);
TCase* gen_x2_z6_tcase(void);
TCase* gen_x2_z7_tcase(void);
TCase* gen_x3_z0_tcase(void);

#endif // OPCODES_TEST_H_
