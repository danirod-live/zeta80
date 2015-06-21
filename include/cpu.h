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

#ifndef CPU_H_
#define CPU_H_

#include "types.h"

/** Check whether a flag is set or reset. Deprecated. */
#define GET_FLAG(f, flag) ((f & flag) != 0)

/** Set a given flag (turn the flag to 1). Deprecated. */
#define SET_FLAG(f, flag) (f = (f | flag))

/** Reset a given flag (turn the flag to 0). Deprecated. */
#define RESET_FLAG(f, flag) (f = (f & ~flag))

/** Set a flag if a condition is true. */
#define SET_IF(f, flag, cond) (f = cond ? (f | flag) : (f & ~flag))

/** Convenience flag handlers: they work with CPU instead of register. */
#define FLAG_SET(cpu, flag) ((cpu).main.af.BYTES.L |= flag)
#define FLAG_RST(cpu, flag) ((cpu).main.af.BYTES.L &= ~(flag))
#define FLAG_GET(cpu, flag) (((cpu).main.af.BYTES.L & flag) != 0)
#define FLAG_SIF(cpu, flag, cond) ((cpu).main.af.BYTES.L = cond ? \
            (cpu).main.af.BYTES.L | flag : \
            (cpu).main.af.BYTES.L & ~(flag))

/**
 * CPU flags. These flags are located in F register.
 */
enum flag_t
{
    FLAG_S = 0x80, //< Sign flag
    FLAG_Z = 0x40, //< Zero flag
    FLAG_5 = 0x20, //< 5-flag (reserved)
    FLAG_H = 0x10, //< Half carry flag
    FLAG_3 = 0x08, //< 3-flag (reserved)
    FLAG_P = 0x04, //< Parity/Overflow flag
    FLAG_N = 0x02, //< DAA flag
    FLAG_C = 0x01  //< Carry flag
};

/**
 * Register struct. This is a 16 bit structure that emulates a virtual
 * 16 bit register. It allow access to the 16 bit virtual word or to each
 * one of the two 8-bit registers that this struct is composed of.
 */
union register_t
{
    word WORD;
    struct { byte L, H; } BYTES;
};

/**
 * Register bank. Z80 has two register banks, each one is composed of eight
 * 8-bit registers, A, F, B, C, D, E, H and L, organized into pairs that
 * at the same time create four 16-bit virtual registers AF, BC, DE and HL.
 */
struct bank_t
{
    union register_t af; //< AF register pair.
    union register_t bc; //< BC register pair.
    union register_t de; //< DE register pair
    union register_t hl; //< HL register pair
};

/**
 * CPU structure.
 */
struct cpu_t
{
    byte mem[0x10000];          //< Memory

    struct bank_t main;         //< Main Register Bank
    struct bank_t alternate;    //< Alternate Register Bank

    union register_t pc;        //< Program Counter
    union register_t sp;        //< Stack Pointer
    union register_t ix;        //< Index X
    union register_t iy;        //< Index Y
    byte i;                     //< Interruptor Vector
    byte r;                     //< Memory Refresh

    int tstates;                //< T-State counter
};

/*
 * These macros expand to the full path to the field of a given register in
 * the CPU structure. They are useful defined as macros because they work
 * exceptionally well with any operator.
 *
 * This makes these macros suitable for any kind of operation:
 * Assignments, such as REG_A(cpu) = 0x55
 * Comparations, such as REG_BC(cpu) == 0x0000
 * Pre/post increments or decrements, such as REG_B(cpu)--.
 * Many other C operations.
 */

#define REG_A(cpu) ((cpu).main.af.BYTES.H) // Expands to A
#define REG_F(cpu) ((cpu).main.af.BYTES.L) // Expands to F
#define REG_B(cpu) ((cpu).main.bc.BYTES.H) // Expands to B
#define REG_C(cpu) ((cpu).main.bc.BYTES.L) // Expands to C
#define REG_D(cpu) ((cpu).main.de.BYTES.H) // Expands to D
#define REG_E(cpu) ((cpu).main.de.BYTES.L) // Expands to E
#define REG_H(cpu) ((cpu).main.hl.BYTES.H) // Expands to H
#define REG_L(cpu) ((cpu).main.hl.BYTES.L) // Expands to L

#define REG_AF(cpu) ((cpu).main.af.WORD) // Expands to AF
#define REG_BC(cpu) ((cpu).main.bc.WORD) // Expands to BC
#define REG_DE(cpu) ((cpu).main.de.WORD) // Expands to DE
#define REG_HL(cpu) ((cpu).main.hl.WORD) // Expands to HL

#define ALT_A(cpu) ((cpu).alternate.af.BYTES.H) // Expands to A'
#define ALT_F(cpu) ((cpu).alternate.af.BYTES.L) // Expands to F'
#define ALT_B(cpu) ((cpu).alternate.bc.BYTES.H) // Expands to B'
#define ALT_C(cpu) ((cpu).alternate.bc.BYTES.L) // Expands to C'
#define ALT_D(cpu) ((cpu).alternate.de.BYTES.H) // Expands to D'
#define ALT_E(cpu) ((cpu).alternate.de.BYTES.L) // Expands to E'
#define ALT_H(cpu) ((cpu).alternate.hl.BYTES.H) // Expands to H'
#define ALT_L(cpu) ((cpu).alternate.hl.BYTES.L) // Expands to L'

#define ALT_AF(cpu) ((cpu).alternate.af.WORD) // Expands to AF'
#define ALT_BC(cpu) ((cpu).alternate.bc.WORD) // Expands to BC'
#define ALT_DE(cpu) ((cpu).alternate.de.WORD) // Expands to DE'
#define ALT_HL(cpu) ((cpu).alternate.hl.WORD) // Expands to HL'

#define PC(cpu) ((cpu).pc.WORD) // Expands to PC
#define SP(cpu) ((cpu).sp.WORD) // Expands to SP
#define IX(cpu) ((cpu).ix.WORD) // Expands to IX
#define IY(cpu) ((cpu).iy.WORD) // Expands to IY

#define IXH(cpu) ((cpu).ix.BYTES.H) // Expands to IXh
#define IXL(cpu) ((cpu).ix.BYTES.L) // Expands to IHl
#define IYH(cpu) ((cpu).iy.BYTES.H) // Expands to IYh
#define IYL(cpu) ((cpu).iy.BYTES.L) // Expands to IYl

#endif
