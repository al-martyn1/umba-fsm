/*! \file
    \brief Тест TextPositionCountingIterator'а
 */

#include "umba/umba.h"
#include "umba/tokenizer.h"
#include "umba/assert.h"

//
#include "umba/text_position_info.h"
#include "umba/iterator.h"

#include <iostream>
#include <map>
#include <deque>

using std::cout;
using std::cerr;


// https://en.cppreference.com/w/cpp/language/string_literal
std::string text = R"raw(digraph {

    r_1 [label="!"]

    n_2_1 [label="+"];  n_2_2 [label="-"];  n_2_3 [label="="];  n_2_4 [label=">"]
    r_1->n_2_1;  r_1->n_2_2;  r_1->n_2_3;  r_1->n_2_4

    n_3_1 [label="+"];  n_3_2 [label="-"];  n_3_3 [label="="];  n_3_4 [label=">"]
    n_2_3->n_3_1;  n_2_3->n_3_2;  n_2_3->n_3_3;  n_2_3->n_3_4

    n_4_0 [label="!"];  n_4_1 [label="+"];  n_4_2 [label="-"];  n_4_3 [label="="];  n_4_4 [label=">"]
    n_3_3->n_4_0;  n_3_3->n_4_1;  n_3_3->n_4_2;  n_3_3->n_4_3;  n_3_3->n_4_4

}
)raw";



inline
void printPos(const umba::TextPositionInfo &pos)
{
    cout << pos.lineNumber+1 << ":" << pos.symbolOffset+1; // печатаем человеческие номера
}

inline
void printChar(char ch)
{
    if (ch>=' ')
       cout << "'" << (char)ch << "'";
    else
       cout << " " << (unsigned)(unsigned char)ch;
}

int main(int argc, char* argv[])
{
    cout << text << "\n";

    cout << "---\n";

    using PosCountingIterator = umba::iterator::TextPositionCountingIterator<char>;

    for( PosCountingIterator it=PosCountingIterator(text.data(), text.size()); it!=PosCountingIterator(); ++it)
    {
        char ch = *it;
        printChar(ch);
        cout << "  ";
        printPos(it.getPosition());

        auto nextIt = it + 1;
        if (nextIt!=PosCountingIterator())
        {
            cout << ", next char: ";
            printChar(*nextIt);
            cout << "  ";
            printPos(nextIt.getPosition());
        }

        cout << "\n";
    }

    return 0;
}

