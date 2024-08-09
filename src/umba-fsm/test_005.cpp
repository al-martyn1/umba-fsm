/*! \file
    \brief Потестировал TheValue и TheFlags
 */

#include "umba/umba.h"
#include "umba/tokenizer.h"
#include "umba/assert.h"

//
#include "umba/text_position_info.h"
#include "umba/iterator.h"
#include "umba/the.h"

#include <iostream>
#include <map>
#include <deque>

using std::cout;
using std::cerr;




int main(int argc, char* argv[])
{
    using namespace umba::tokenizer;

    std::array<CharClass, 128> charClassTable;
    generation::generateCharClassTable(charClassTable, true /* addOperatorChars */ );


    {
        auto charClass = charClassTable[charToCharClassTableIndex('(')];
        bool bRes = umba::TheFlags(charClass).oneOf(CharClass::open, CharClass::close);
        cout << "Is brace '(': " << (bRes?"true":"false") << "\n";
    }
    {
        auto charClass = charClassTable[charToCharClassTableIndex('!')];
        bool bRes = umba::TheFlags(charClass).oneOf(CharClass::open, CharClass::close);
        cout << "Is brace '!': " << (bRes?"true":"false") << "\n";
    }

    {
        auto charClass = charClassTable[charToCharClassTableIndex('8')];
        bool bRes = umba::TheFlags(charClass).allOf(CharClass::identifier, CharClass::alpha);
        cout << "Is identifier && alpha '8': " << (bRes?"true":"false") << "\n";
    }
    {
        auto charClass = charClassTable[charToCharClassTableIndex('a')];
        bool bRes = umba::TheFlags(charClass).allOf(CharClass::identifier, CharClass::alpha);
        cout << "Is identifier && alpha 'a': " << (bRes?"true":"false") << "\n";
    }

    {
        char ch = 'a';
        bool bRes = umba::TheValue(ch).oneOf('a', 'b', 'c');
        cout << "Is 'a' one of 'a', 'b', 'c': " << (bRes?"true":"false") << "\n";
    }
    {
        char ch = 'a';
        bool bRes = umba::TheValue(ch).oneOf('b', 'c', 'd');
        cout << "Is 'a' one of 'b', 'c', 'd': " << (bRes?"true":"false") << "\n";
    }


    return 0;
}

