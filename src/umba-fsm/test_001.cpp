/*! \file
    \brief Тестируем корректность генерации индексов для таблицы CharClass по символу
 */

#include "umba/umba.h"
#include "umba/tokenizer.h"


#include <iostream>

using std::cout;
using std::cerr;

int main(int argc, char* argv[])
{
    cout << "Character indices in CharClass table:\n";

    for(std::uint8_t i=0; i!=(std::uint8_t)-1; ++i)
    {
        cout << "  " << (unsigned)i;
        if (i>32)
           cout << " '" << (char)i << "'";
        else
           cout << "    ";

        cout << "  - " << umba::tokenizer::charToCharClassTableIndex((char)i) << "\n";
    }

    return 0;
}

