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

#include "cpu.h"
#include "cpu_test.h"

START_TEST(register_t_test_word)
{
    union register_t reg;
    reg.WORD = 0x1234;
    ck_assert(reg.WORD == 0x1234);
    ck_assert(reg.BYTES.H == 0x12);
    ck_assert(reg.BYTES.L == 0x34);
}
END_TEST

START_TEST(register_t_test_bytes)
{
    union register_t reg;
    reg.BYTES.H = 0x56;
    reg.BYTES.L = 0x78;
    ck_assert(reg.WORD == 0x5678);
    ck_assert(reg.BYTES.H == 0x56);
    ck_assert(reg.BYTES.L == 0x78);
}
END_TEST

Suite*
gensuite_cpu(void)
{
    TCase* tc_register = tcase_create("Register");
    tcase_add_test(tc_register, register_t_test_word);
    tcase_add_test(tc_register, register_t_test_bytes);

    Suite* s = suite_create("CPU");
    suite_add_tcase(s, tc_register);
    return s;
}
