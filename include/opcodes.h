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

#ifndef OPCODES_H_
#define OPCODES_H_

#include "cpu.h"

/**
 * Decoded opcode struct.
 */
struct opcode_t
{
            //  7 6 5 4  3 2 1 0
    char x; //< 1 1 0 0  0 0 0 0 - 0xC0
    char y; //< 0 0 1 1  1 0 0 0 - 0x38
    char z; //< 0 0 0 0  0 1 1 1 - 0x07
    char p; //< 0 0 1 1  0 0 0 0 - 0x30
    char q; //< 0 0 0 0  1 0 0 0 - 0x08
};

void extract_opcode(char opcode, struct opcode_t* opstruct);

void execute_opcode(struct cpu_t* cpu);
#endif
