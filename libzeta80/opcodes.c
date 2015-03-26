#include "opcodes.h"
#include "cpu.h"
#include <stdio.h>

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

static void
execute_table0(struct cpu_t* cpu, struct opcode_t* opstruct)
{
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
    // Extraer opcode.
    struct opcode_t opdata;
    byte opcode = cpu->mem[cpu->pc.WORD++];
    extract_opcode(opcode, &opdata);

    // Procesar opcode.
    table_function table = tables[(int) opdata.z];
    table(cpu, &opdata);

    // Otras operaciones.
}
