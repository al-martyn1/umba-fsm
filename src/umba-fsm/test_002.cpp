/*! \file
    \brief Генерируем CharClass таблицу
 */

#include "umba/umba.h"
#include "umba/tokenizer.h"



int main(int argc, char* argv[])
{

    umba::tokenizer::CharClass charClasses[128] = { umba::tokenizer::CharClass::none };
    umba::tokenizer::generation::generateCharClassTable(charClasses);

    umba::tokenizer::generation::CommentType  commentType  = umba::tokenizer::generation::CommentType ::cppLike;
    umba::tokenizer::generation::ArrayType    arrayType    = umba::tokenizer::generation::ArrayType   ::stdArray;
    umba::tokenizer::generation::TypeNameType typeNameType = umba::tokenizer::generation::TypeNameType::cppLike;

    if (argc>1)
    {
        commentType  = umba::tokenizer::generation::CommentType ::cLike;
        arrayType    = umba::tokenizer::generation::ArrayType   ::cLike;
        typeNameType = umba::tokenizer::generation::TypeNameType::cLike;
    }

    umba::tokenizer::generation::printCharClassArray( charClasses, commentType, arrayType, typeNameType /* , const std::string &varName="charClassesTable" */ );

    return 0;
}

