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

#include <check.h>

#include <opcodes.h>

#include "extract_opcodes.h"

/* Testcase for extract_opcode. Tests extration for X field. */
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

/* Testcase for extract_opcode. Tests extraction for Y field. */
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

/* Testcase for extract_opcode. Tests extraction for Z field. */
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

/* Testcase for extract_opcode. Tests extraction for P field. */
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

/* Testcase for extract_opcode. Tests extraction for Q field. */
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

TCase* gen_extract_opcode_tcase(void)
{
    TCase* test = tcase_create("extract_opcode");
    tcase_add_test(test, extract_opcode_test_x);
    tcase_add_test(test, extract_opcode_test_y);
    tcase_add_test(test, extract_opcode_test_z);
    tcase_add_test(test, extract_opcode_test_p);
    tcase_add_test(test, extract_opcode_test_q);
    return test;
}
