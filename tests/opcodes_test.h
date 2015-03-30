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

// Setup and teardown functions for test cases.
struct cpu_t* setup_cpu(void);
void teardown_cpu(struct cpu_t* cpu);

// Different suites
Suite* gensuite_opcodes(void);

// Different test cases.
TCase* gen_extract_opcode_tcase(void);
TCase* gen_x0_z0_tcase(void);
TCase* gen_x0_z1_tcase(void);

#endif // OPCODES_TEST_H_
