/*
 * libzeta80: A Z80 emulation library.
 * Copyright (C) 2015 Dani Rodríguez <danirod@outlook.com>
 * Insert BSD license here.
 */

#include "types.h"

#ifndef CPU_H_
#define CPU_H_

/**
 * Estructura registro. Por medio de esta estructura de 16 bits puedo acceder
 * a un registro virtual de 16 bits o a los dos registros de los que se 
 * compone de forma simultánea.
 *
 * Por ejemplo, creando un union register_t para BC, puedo acceder a BC con
 * bc.WORD, a B con bc.BYTES.H, y a C con bc.bytes.L.
 */
union register_t
{
    word WORD;
    struct { byte L, H; } BYTES;
};

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
