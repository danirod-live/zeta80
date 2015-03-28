#ifndef OPCODES_H_
#define OPCODES_H_

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

#endif
