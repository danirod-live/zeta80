#include "opcodes.h"
#include "cpu.h"
#include <stdio.h>

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
    Register* af = &cpu->main.af;
    Register* af2 = &cpu->alternate.af;
    word tmp = af->WORD;
    af->WORD = af2->WORD;
    af2->WORD = tmp;

    cpu->tstates += 4;
}

static void
djnz_d(struct cpu_t* cpu)
{
    signed char e = (signed char) cpu->mem[cpu->pc.WORD++];
    if (--cpu->main.bc.BYTES.H == 0) {
        cpu->tstates += 8;
    } else {
        cpu->pc.WORD += e;
        cpu->tstates = 13;
    }
}

static void
jr_d(struct cpu_t* cpu)
{
    signed char e = (signed char) cpu->mem[cpu->pc.WORD++];
    cpu->pc.WORD += e;
    cpu->tstates = 12;
}

static void
jr_nz(struct cpu_t* cpu)
{
    signed char e = (signed char) cpu->mem[cpu->pc.WORD++];
    if ( GET_FLAG(cpu->main.af.BYTES.L, FLAG_Z) == 0) {
        cpu->pc.WORD += e;
        cpu->tstates += 12;
    } else {
        cpu->tstates += 7;
    }
}

static void
jr_z(struct cpu_t* cpu)
{
    signed char e = (signed char) cpu->mem[cpu->pc.WORD++];
    if ( GET_FLAG(cpu->main.af.BYTES.L, FLAG_Z) != 0) {
        cpu->pc.WORD += e;
        cpu->tstates += 12;
    } else {
        cpu->tstates += 7;
    }
}

static void
jr_nc(struct cpu_t* cpu)
{
    signed char e = (signed char) cpu->mem[cpu->pc.WORD++];
    if ( GET_FLAG(cpu->main.af.BYTES.L, FLAG_C) == 0) {
        cpu->pc.WORD += e;
        cpu->tstates += 12;
    } else {
        cpu->tstates += 7;
    }
}

static void
jr_c(struct cpu_t* cpu)
{
    signed char e = (signed char) cpu->mem[cpu->pc.WORD++];
    if ( GET_FLAG(cpu->main.af.BYTES.L, FLAG_C) != 0) {
        cpu->pc.WORD += e;
        cpu->tstates += 12;
    } else {
        cpu->tstates += 7;
    }
}

static void
ld_dd_nn(struct cpu_t* cpu, Register* reg)
{
    // Read NN from memory. It's a 16 bit value.
    word nn = *(((word*) cpu->mem) + cpu->pc.WORD);
    cpu->pc.WORD += 2;

    reg->WORD = nn;
    cpu->tstates += 10;
}

static void
add_hl_ss(struct cpu_t* cpu, Register* reg)
{
    word op1 = cpu->main.hl.WORD, op2 = reg->WORD;

    // Flag N must be reset anyway.
    RESET_FLAG(cpu->main.af.BYTES.L, FLAG_N);

    // Flag H must be set if carry from bit 11.
    if ((((op1 & 0x07FF) + (op2 & 0x7FF)) & 0x0800) != 0)
        SET_FLAG(cpu->main.af.BYTES.L, FLAG_H);
    else
        RESET_FLAG(cpu->main.af.BYTES.L, FLAG_H);

    // Flag C must be set if carry from bit 15.
    if (((op1 + op2) & 0x10000) != 0)
        SET_FLAG(cpu->main.af.BYTES.L, FLAG_C);
    else
        RESET_FLAG(cpu->main.af.BYTES.L, FLAG_C);

    cpu->main.hl.WORD += reg->WORD;
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

static Register* rp[4];

static void
execute_table0(struct cpu_t* cpu, struct opcode_t* opstruct)
{
    char z = opstruct->z;
    char y = opstruct->y;

    if (z == 0)
    {
        if (y == 0) nop(cpu);
        if (y == 1) ex_af_af(cpu);
        if (y == 2) djnz_d(cpu);
        if (y == 3) jr_d(cpu);
        if (y == 4) jr_nz(cpu);
        if (y == 5) jr_z(cpu);
        if (y == 6) jr_nc(cpu);
        if (y == 7) jr_c(cpu);
    }
    else if (z == 1)
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
    table_function table = tables[(int) opdata.z];
    table(cpu, &opdata);

    // Otras operaciones.
}
