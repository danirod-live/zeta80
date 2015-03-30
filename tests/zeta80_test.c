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

#include "cpu_test.h"
#include "opcodes_test.h"

int
main(int argc, char** argv)
{
    SRunner* suite_runner = srunner_create(gensuite_cpu());
    srunner_add_suite(suite_runner, gensuite_opcodes());

    srunner_run_all(suite_runner, CK_NORMAL);
    int failed = srunner_ntests_failed(suite_runner);
    srunner_free(suite_runner);

    return (failed > 0);
}
