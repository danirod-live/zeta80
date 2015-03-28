/*
 * This file is part of zeta80: a Z80 emulation library.
 * Copyright (C) 2015 Dani Rodríguez <danirod@outlook.com>
 */

#include <check.h>
#include "opcodes.h"
#include "types.h"

START_TEST(extract_opcode_test_x)
{
    struct opcode_t opstr;
    extract_opcode(0xC0, &opstr);
    ck_assert(opstr.x == 3);
    ck_assert(opstr.y == 0);
    ck_assert(opstr.z == 0);
    ck_assert(opstr.p == 0);
    ck_assert(opstr.q == 0);
}
END_TEST

START_TEST(extract_opcode_test_y)
{
    struct opcode_t opstr;
    extract_opcode(0x38, &opstr);
    ck_assert(opstr.x == 0);
    ck_assert(opstr.y == 7);
    ck_assert(opstr.z == 0);
    ck_assert(opstr.p == 3);
    ck_assert(opstr.q == 1);
}
END_TEST

START_TEST(extract_opcode_test_z)
{
    struct opcode_t opstr;
    extract_opcode(0x07, &opstr);
    ck_assert(opstr.x == 0);
    ck_assert(opstr.y == 0);
    ck_assert(opstr.z == 7);
    ck_assert(opstr.p == 0);
    ck_assert(opstr.q == 0);
}
END_TEST

START_TEST(extract_opcode_test_p)
{
    struct opcode_t opstr;
    extract_opcode(0x30, &opstr);
    ck_assert(opstr.x == 0);
    ck_assert(opstr.y == 6);
    ck_assert(opstr.z == 0);
    ck_assert(opstr.p == 3);
    ck_assert(opstr.q == 0);
}
END_TEST

START_TEST(extract_opcode_test_q)
{
    struct opcode_t opstr;
    extract_opcode(0x08, &opstr);
    ck_assert(opstr.x == 0);
    ck_assert(opstr.y == 1);
    ck_assert(opstr.z == 0);
    ck_assert(opstr.p == 0);
    ck_assert(opstr.q == 1);
}
END_TEST

/**
 * Generate a testsuite for opcodes.
 */
Suite*
gensuite_opcodes(void)
{
    TCase* extract_opcode_test = tcase_create("extract_opcode");
    tcase_add_test(extract_opcode_test, extract_opcode_test_x);
    tcase_add_test(extract_opcode_test, extract_opcode_test_y);
    tcase_add_test(extract_opcode_test, extract_opcode_test_z);
    tcase_add_test(extract_opcode_test, extract_opcode_test_p);
    tcase_add_test(extract_opcode_test, extract_opcode_test_q);
    
    Suite* s = suite_create("Opcodes");
    suite_add_tcase(s, extract_opcode_test);
    return s;
}


