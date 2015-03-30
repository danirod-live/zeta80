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

#include "types.h"

#ifndef CPU_H_
#define CPU_H_

/** Check whether a flag is set or reset. */
#define GET_FLAG(f, flag) ((f & flag) != 0)

/** Set a given flag (turn the flag to 1). */
#define SET_FLAG(f, flag) (f = (f | flag))

/** Reset a given flag (turn the flag to 0). */
#define RESET_FLAG(f, flag) (f = (f & ~flag))

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


#endif 
