#pragma once


#ifndef TEST_H_INCLUDED
#define TEST_H_INCLUDED

/* add this lines to your source
#ifndef TEST_H_INCLUDED
    #include "test.h"
#endif
*/

void func()
{
    auto hexFloat = 0x123.456l;
    auto str = "literal_with_suffix"_s;
    auto i   = "literal_with_suffix"i;
}

#endif /* TEST_H_INCLUDED */
