/*
 * libzeta80: A Z80 emulation library.
 * Copyright (C) 2015 Dani Rodríguez <danirod@outlook.com>
 * Insert BSD license here.
 */

#include "types.h"

#ifndef CPU_H_
#define CPU_H_

/**
 * Flags del procesador.
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

/**
 * Banco de registros. El Z80 tiene varios bancos de registros y para cada
 * banco tiene ocho registros de 8 bits que virtualmente pueden agruparse
 * en 4 registros virtuales de 16 bits.
 */
struct bank_t {
    union register_t bc, de, hl, af;
};

struct cpu_t
{
    word mem[0x10000];          //< Memory

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
