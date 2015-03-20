/*
 * libzeta80: A Z80 emulation library.
 * Copyright (C) 2015 Dani Rodríguez <danirod@outlook.com>
 * Insert BSD license here.
 */

#include "types.h"

#ifndef CPU_H_
#define CPU_H_

struct bank_t
{
    byte a, f;
    byte b, c;
    byte d, e;
    byte h, l;
};

struct cpu_t
{
    word mem[0x10000];      //< Memory

    struct bank_t main;         //< Main Register Bank
    struct bank_t alternate;    //< Alternate Register Bank

    word pc;                //< Program Counter
    word sp;                //< Stack Pointer
    word ix;                //< Index X
    word iy;                //< Index Y
    byte i;                  //< Interruptor Vector
    byte r;                  //< Memory Refresh
};

#endif 
