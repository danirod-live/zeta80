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

#include <opcodes.h>
#include <cpu.h>

/**
 * Executes NOP. This opcode does nothing. It just refreshes memory.
 *
 * @param cpu CPU instances
 */
static void
nop(struct cpu_t* cpu)
{
    cpu->tstates += 4;
}

static void
ex_af_af(struct cpu_t* cpu)
{
    word tmp = REG_A(*cpu);
    REG_A(*cpu) = ALT_A(*cpu);

    cpu->tstates += 4;
}

static void
djnz_d(struct cpu_t* cpu)
{
    char e = (char) cpu->mem[PC(*cpu)++];

    if (--REG_B(*cpu) == 0) {
        cpu->tstates += 8;
    } else {
        PC(*cpu) += e;
        cpu->tstates = 13;
    }
}

static void
jr_d(struct cpu_t* cpu)
{
    char e = (char) cpu->mem[PC(*cpu)++];
    PC(*cpu) += e;
    cpu->tstates = 12;
}

static void
jr_nz(struct cpu_t* cpu)
{
    char e = (char) cpu->mem[PC(*cpu)++];
    if (GET_FLAG(REG_F(*cpu), FLAG_Z) == 0) {
        PC(*cpu) += e;
        cpu->tstates += 12;
    } else {
        cpu->tstates += 7;
    }
}

static void
jr_z(struct cpu_t* cpu)
{
    char e = (char) cpu->mem[PC(*cpu)++];
    if (GET_FLAG(REG_F(*cpu), FLAG_Z) != 0) {
        cpu->pc.WORD += e;
        cpu->tstates += 12;
    } else {
        cpu->tstates += 7;
    }
}

static void
jr_nc(struct cpu_t* cpu)
{
    char e = (char) cpu->mem[PC(*cpu)++];
    if (GET_FLAG(REG_F(*cpu), FLAG_C) == 0) {
        cpu->pc.WORD += e;
        cpu->tstates += 12;
    } else {
        cpu->tstates += 7;
    }
}

static void
jr_c(struct cpu_t* cpu)
{
    char e = (char) cpu->mem[PC(*cpu)++];
    if(GET_FLAG(REG_F(*cpu), FLAG_C) != 0) {
        cpu->pc.WORD += e;
        cpu->tstates += 12;
    } else {
        cpu->tstates += 7;
    }
}

static void
ld_dd_nn(struct cpu_t* cpu, union register_t* reg)
{
    // Read NN in memory. Remember: Z80 is little endian.
    word nn = cpu->mem[PC(*cpu)] | (cpu->mem[PC(*cpu) + 1] << 8);
    PC(*cpu) += 2; // Increment program counter after read.
    reg->WORD = nn;
    cpu->tstates += 10;
}

static void
add_hl_ss(struct cpu_t* cpu, union register_t* reg)
{
    word op1 = REG_HL(*cpu), op2 = reg->WORD;

    RESET_FLAG(REG_F(*cpu), FLAG_N);
    SET_IF(REG_F(*cpu), FLAG_H, ((op1 & 0x7FF + op2 & 0x7FF) & 0x800) != 0);
    SET_IF(REG_F(*cpu), FLAG_C, ((op1 + op2) & 0x10000) != 0);

    REG_HL(*cpu) += reg->WORD;
    cpu->tstates += 11;
}

/**
 * Extrae los trozos de un opcode a partir del opcode tal cual que se
 * haya sacado de memoria. Aplica una serie de máscaras de bit para sacar
 * el resultado. Ver documentación.
 *
 * Sin probar.
 *
 * @param opcode opcode leído de memoria
 * @param opstruct la estructura en la que quiero volcar los datos
 */
void
extract_opcode(char opcode, struct opcode_t* opstruct)
{
    opstruct->x = (opcode & 0xC0) >> 6;
    opstruct->y = (opcode & 0x38) >> 3;
    opstruct->z = (opcode & 0x07);
    opstruct->p = opstruct->y >> 1;
    opstruct->q = opstruct->y & 1;
}

/**
 * Este es el tipo de datos para la función que va a procesar la tabla
 * de opcodes. Construiré con ellas un array de callbacks para que pueda
 * llamar rápidamente a la función apropiada.
 */
typedef void (*table_function)(struct cpu_t*, struct opcode_t*);

static union register_t* rp[4];

static void
execute_table0(struct cpu_t* cpu, struct opcode_t* opstruct)
{
    if (opstruct->z == 0)
    {
        if (opstruct->y == 0) nop(cpu);
        if (opstruct->y == 1) ex_af_af(cpu);
        if (opstruct->y == 2) djnz_d(cpu);
        if (opstruct->y == 3) jr_d(cpu);
        if (opstruct->y == 4) jr_nz(cpu);
        if (opstruct->y == 5) jr_z(cpu);
        if (opstruct->y == 6) jr_nc(cpu);
        if (opstruct->y == 7) jr_c(cpu);
    }
    else if (opstruct->z == 1)
    {
        if (opstruct->q == 0) ld_dd_nn(cpu, rp[(int) opstruct->p]);
        if (opstruct->q == 1) add_hl_ss(cpu, rp[(int) opstruct->p]);
    }
}

static void
execute_table1(struct cpu_t* cpu, struct opcode_t* opstruct)
{
}

static void
execute_table2(struct cpu_t* cpu, struct opcode_t* opstruct)
{
}

static void
execute_table3(struct cpu_t* cpu, struct opcode_t* opstruct)
{
}


/**
 * Array con las distintas tablas. La intención es que si luego tengo que
 * usar la tabla I, pueda llamar simplemente a tables[I].
 */
static table_function tables[] = {
    &execute_table0, &execute_table1, &execute_table2, &execute_table3
};

void
execute_opcode(struct cpu_t* cpu)
{
    // Fill arrays
    rp[0] = &cpu->main.bc;
    rp[1] = &cpu->main.de;
    rp[2] = &cpu->main.hl;
    rp[3] = &cpu->sp;

    // Extraer opcode.
    struct opcode_t opdata;
    byte opcode = cpu->mem[cpu->pc.WORD++];
    extract_opcode(opcode, &opdata);

    // Procesar opcode.
    table_function table = tables[(int) opdata.x];
    table(cpu, &opdata);

    // Otras operaciones.
}
