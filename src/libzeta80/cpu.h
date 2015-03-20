/*
 * libzeta80: A Z80 emulation library.
 * Copyright (C) 2015 Dani Rodríguez <danirod@outlook.com>
 * Insert BSD license here.
 */

#include <stdint.h>

struct bank_t
{
    uint8_t a, f;
    uint8_t b, c;
    uint8_t d, e;
    uint8_t h, l;
};

struct cpu_t
{
    uint16_t mem[0x10000];      //< Memory

    struct bank_t main;         //< Main Register Bank
    struct bank_t alternate;    //< Alternate Register Bank

    uint16_t pc;                //< Program Counter
    uint16_t sp;                //< Stack Pointer
    uint16_t ix;                //< Index X
    uint16_t iy;                //< Index Y
    uint8_t i;                  //< Interruptor Vector
    uint8_t r;                  //< Memory Refresh
};
