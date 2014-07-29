/* Copyright 2014 Samsung Electronics Co., Ltd.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "globals.h"
#include "interpreter.h"
#include "mem-allocator.h"
#include "opcodes.h"
#include "serializer.h"

/**
 * Unit test's main function.
 */
int
main( int __unused argc,
      char __unused **argv)
{
  const OPCODE test_program[] = {
    /*  0: */ getop_reg_var_decl( 255, 255),
    /*  1: */ getop_var_decl( 0),
    /*  2: */ getop_var_decl( 1),
    /*  3: */ getop_assignment( 0, OPCODE_ARG_TYPE_STRING, 1),
    /*  4: */ getop_assignment( 1, OPCODE_ARG_TYPE_VARIABLE, 0),
    /*  5: */ getop_is_true_jmp( 1, 7),
    /*  6: */ getop_jmp_down( 5),
    /*  7: */ getop_assignment( 0, OPCODE_ARG_TYPE_SMALLINT, 253),
    /*  8: */ getop_assignment( 1, OPCODE_ARG_TYPE_NUMBER, 2),
    /*  9: */ getop_is_false_jmp( 1, 11),
    /* 10: */ getop_exitval( 0),
    /* 11: */ getop_exitval( 1)
  };

  mem_init();

  const char *strings[] = { "a",
                            "b" };
  int nums [] = { 2 };
  uint16_t offset = serializer_dump_strings( strings, 2);
  serializer_dump_nums( nums, 1, offset, 2);

  init_int( test_program);

  return run_int() ? 0
                   : 1;
} /* main */
