//
#include "char_class.h"
//
#include "iterator.h"
#include "escape_string.h"

//
#include <map>
#include <deque>
#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <type_traits>

//
#include "assert.h"

//
#include "tokenizer/defs.h"
//
#include "tokenizer/utils.h"
//
#include "tokenizer/trie_builder.h"
//
#include "tokenizer/string_literal_parsing.h"
//
#include "tokenizer/tokenizer_base.h"
//
#include "tokenizer/tokenizer_function_handlers.h"
//
#include "tokenizer/tokenizer.h"
//
#include "tokenizer/tokenizer_builder.h"


#if !defined(_MSVC_LANG) || _MSVC_LANG < 201402
#endif

#pragma once

// #if !defined(_MSVC_LANG) || _MSVC_LANG < 201402
    // #define UMBA_DEPRECATED            __declspec(deprecated)
    // #define UMBA_DEPRECATED_MSG(msg)   __declspec(deprecated(msg))
// #else
    // #define UMBA_DEPRECATED            [[deprecated]]
    // #define UMBA_DEPRECATED_MSG(msg)   [[deprecated(msg)]]
// #endif



#ifndef TEST_H_INCLUDED
#define TEST_H_INCLUDED

#include "zz_detect_environment.h"

#if defined(UMBA_CXX_HAS_STD11)

    #include <cstddef>
    #include <cstdint>

    //! Зачем-то сделано
    #define UMBA_STD_SIZE_T    std::size_t

#else

    //! Зачем-то сделано
    #define UMBA_STD_SIZE_T    size_t

#endif


/* add this lines to your source
#ifndef TEST_H_INCLUDED
    #include "test.h"
#endif
*/

#include<iostream>

void func()
{
    auto hexFloat = 0x123.456l;
    auto quatUnsigned = 4x123l;
    auto duodUnsigned = 12x123l;
    auto str = "literal_with_suffix"_s;
    auto i   = "literal_with_suffix"i;
}

#endif /* TEST_H_INCLUDED */


#ifndef UMBA_DECLARE_WEAK_IRQ_HANDLER
    #define UMBA_DECLARE_WEAK_IRQ_HANDLER( funcName )     extern "C" UMBA_DECLARE_WEAK_FUNCTION( void funcName() )
#endif

//! Декларирует WEAK-функцию - обработчик прерывания
#ifndef UMBA_WEAK_IRQ_HANDLER
    #define UMBA_WEAK_IRQ_HANDLER( funcName )             UMBA_DECLARE_WEAK_IRQ_HANDLER(funcName)
#endif

