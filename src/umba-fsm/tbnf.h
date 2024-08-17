#pragma once


#include "umba/umba.h"
//
#include "umba/tokenizer.h"
#include "umba/text_position_info.h"
#include "umba/iterator.h"
#include "umba/the.h"
#include "umba/rule_of_five.h"

//
#include "enums.h"


//
#include <variant>


//----------------------------------------------------------------------------



//----------------------------------------------------------------------------
namespace umba{

namespace tbnf {

//----------------------------------------------------------------------------



//----------------------------------------------------------------------------
inline
auto makeTokenizerBuilder()
{
    using namespace umba::tokenizer;
    return TokenizerBuilder<char>().generateStandardCharClassTable()

                                   .setCharClassFlags('-', umba::tokenizer::CharClass::identifier) // делаем минус валидным символом для идентификатора - имена атрибутов могут иметь тире/дефис в середине имени

                                   // Числа с плавающей точкой отличаются только флагом UMBA_TOKENIZER_TOKEN_FLOAT_FLAG
                                   .addNumbersPrefix("0b", UMBA_TOKENIZER_TOKEN_INTEGRAL_NUMBER_BIN)
                                   .addNumbersPrefix("0B", UMBA_TOKENIZER_TOKEN_INTEGRAL_NUMBER_BIN, true) // allow token usage for multiple sequences

                                   .addNumbersPrefix("0d", UMBA_TOKENIZER_TOKEN_INTEGRAL_NUMBER_DEC)
                                   .addNumbersPrefix("0D", UMBA_TOKENIZER_TOKEN_INTEGRAL_NUMBER_DEC, true)

                                   .addNumbersPrefix("0" , UMBA_TOKENIZER_TOKEN_INTEGRAL_NUMBER_OCT | UMBA_TOKENIZER_TOKEN_NUMBER_LITERAL_FLAG_MISS_DIGIT)

                                   .addNumbersPrefix("0x", UMBA_TOKENIZER_TOKEN_INTEGRAL_NUMBER_HEX)
                                   .addNumbersPrefix("0X", UMBA_TOKENIZER_TOKEN_INTEGRAL_NUMBER_HEX, true)


                                   .addBrackets("{}", UMBA_TOKENIZER_TOKEN_CURLY_BRACKETS )  // {N,M} - задаётся мощность
                                   .addBrackets("()", UMBA_TOKENIZER_TOKEN_ROUND_BRACKETS )  // группирует последовательность, обычно для того, чтобы задать ей мощность
                                   //.addBrackets("<>", UMBA_TOKENIZER_TOKEN_ANGLE_BRACKETS )
                                   .addBrackets("[]", UMBA_TOKENIZER_TOKEN_SQUARE_BRACKETS)  // Краткая форма записи для ?() - опциональная часть


                                   .addSingleLineComment("//", UMBA_TOKENIZER_TOKEN_OPERATOR_SINGLE_LINE_COMMENT)
                                   .addSingleLineComment("#" , UMBA_TOKENIZER_TOKEN_OPERATOR_SINGLE_LINE_COMMENT, true) // allow token usage for multiple sequences
                                   .setMultiLineComment("/*", "*/")


                                   .addOperator("*"  , UMBA_TOKENIZER_TOKEN_OPERATOR_ANY_NUM_REPETITIONS)      // * - от нуля повторений до бесконечности
                                   .addOperator("+"  , UMBA_TOKENIZER_TOKEN_OPERATOR_ONE_MORE_REPETITION)      // + - от одного повторения до бесконечности
                                   .addOperator("?"  , UMBA_TOKENIZER_TOKEN_OPERATOR_ZERO_OR_ONE_REPETITIONS)  // ? - ноль или одно

                                   .addOperator(":"  , UMBA_TOKENIZER_TOKEN_OPERATOR_ASSIGNMENT)        // Поддерживаем три версии оператора присваивания
                                   .addOperator("="  , UMBA_TOKENIZER_TOKEN_OPERATOR_ASSIGNMENT, true)  // allow token usage for multiple sequences
                                   .addOperator("::=", UMBA_TOKENIZER_TOKEN_OPERATOR_ASSIGNMENT, true)  // allow token usage for multiple sequences
                                   
                                   .addOperator("@"  , UMBA_TOKENIZER_TOKEN_OPERATOR_AT)

                                   .addOperator("|"  , UMBA_TOKENIZER_TOKEN_OPERATOR_BNF_ALTER)
                                   .addOperator("/"  , UMBA_TOKENIZER_TOKEN_OPERATOR_BNF_ALTER, true) // allow token usage for multiple sequences

                                   // #define UMBA_TOKENIZER_TOKEN_STRING_LITERAL                                           0x3000u
                                   // #define UMBA_TOKENIZER_TOKEN_CHAR_LITERAL                                             0x3001u
                                   .addStringLiteralParser< umba::tokenizer::CppEscapedSimpleQuotedStringLiteralParser<char> >(UMBA_TOKENIZER_TOKEN_STRING_LITERAL
                                                                                                                             , { "\""    // UMBA_TOKENIZER_TOKEN_STRING_LITERAL itself
                                                                                                                               ,  "\'"   // UMBA_TOKENIZER_TOKEN_CHAR_LITERAL (UMBA_TOKENIZER_TOKEN_STRING_LITERAL+1)
                                                                                                                               }
                                                                                                                             )
                                   ;
}

//----------------------------------------------------------------------------



//----------------------------------------------------------------------------
using token_type   = umba::tokenizer::token_type;
using payload_type = umba::tokenizer::payload_type;

inline constexpr const token_type token_id_invalid         = umba::tokenizer::token_id_invalid;
inline constexpr const payload_type payload_invalid        = umba::tokenizer::payload_invalid;

using TrieNode = umba::tokenizer::TrieNode;

//----------------------------------------------------------------------------



//----------------------------------------------------------------------------
struct BuiltinEmptyInfo
{
};

//----------------------------------------------------------------------------



//----------------------------------------------------------------------------
struct BuiltinNonTerminalInfoBase
{
    BuiltinTokenType      tokenType = BuiltinTokenType::invalid;
    token_type            tokenId   = token_id_invalid;
    std::string           tokenName;

    UMBA_RULE_OF_FIVE(BuiltinNonTerminalInfoBase, default, default, default, default, default);

}; // struct BuiltinNonTerminalInfoBase

//----------------------------------------------------------------------------



//----------------------------------------------------------------------------
struct BuiltinCommentInfo : public BuiltinNonTerminalInfoBase
{
    std::string               prefix;
    std::string               suffix;
    BuiltinTokenTypeParam     position = BuiltinTokenTypeParam::invalid; // allowed values: beginOnly/any

    UMBA_RULE_OF_FIVE(BuiltinCommentInfo, default, default, default, default, default);

    BuiltinCommentInfo(const BuiltinNonTerminalInfoBase &b) : BuiltinNonTerminalInfoBase(b) {}

}; // struct BuiltinCommentInfo

//----------------------------------------------------------------------------



//----------------------------------------------------------------------------
struct BuiltinNumberLiteralInfo : public BuiltinNonTerminalInfoBase
{
    unsigned     numberBase = 10;
    std::string  prefix;

    UMBA_RULE_OF_FIVE(BuiltinNumberLiteralInfo, default, default, default, default, default);

    BuiltinNumberLiteralInfo(const BuiltinNonTerminalInfoBase &b) : BuiltinNonTerminalInfoBase(b) {}

}; // struct BuiltinNumberLiteralInfo

//----------------------------------------------------------------------------



//----------------------------------------------------------------------------
struct BuiltinStringLiteralInfo : public BuiltinNonTerminalInfoBase
{
    std::string  prefix;
    std::string  kind  ;
    bool         caseIndependent = false;

    UMBA_RULE_OF_FIVE(BuiltinStringLiteralInfo, default, default, default, default, default);

    BuiltinStringLiteralInfo(const BuiltinNonTerminalInfoBase &b) : BuiltinNonTerminalInfoBase(b) {}

}; // struct BuiltinStringLiteralInfo

//----------------------------------------------------------------------------



//----------------------------------------------------------------------------
struct BuiltinOperatorInfo : public BuiltinNonTerminalInfoBase
{
    std::string  operatorSequence;

    UMBA_RULE_OF_FIVE(BuiltinOperatorInfo, default, default, default, default, default);

    BuiltinOperatorInfo(const BuiltinNonTerminalInfoBase &b) : BuiltinNonTerminalInfoBase(b) {}

}; // struct BuiltinOperatorInfo

//----------------------------------------------------------------------------



//----------------------------------------------------------------------------
struct BuiltinIdentigierInfo : public BuiltinNonTerminalInfoBase
{
    std::string  value;

    UMBA_RULE_OF_FIVE(BuiltinIdentigierInfo, default, default, default, default, default);

    BuiltinIdentigierInfo(const BuiltinNonTerminalInfoBase &b) : BuiltinNonTerminalInfoBase(b) {}

}; // struct BuiltinIdentigierInfo

//----------------------------------------------------------------------------



//----------------------------------------------------------------------------
struct BuiltinBracketInfo : public BuiltinNonTerminalInfoBase
{
    std::string               value; // exact one char from set of (){}[]<>
    BuiltinTokenTypeParam     kind = BuiltinTokenTypeParam::invalid; // allowed values: open/close

    UMBA_RULE_OF_FIVE(BuiltinBracketInfo, default, default, default, default, default);

    BuiltinBracketInfo(const BuiltinNonTerminalInfoBase &b) : BuiltinNonTerminalInfoBase(b) {}

}; // struct BuiltinBracketInfo

//----------------------------------------------------------------------------



//----------------------------------------------------------------------------
using BuiltinNonTerminalInfo = std::variant<BuiltinEmptyInfo, BuiltinCommentInfo, BuiltinNumberLiteralInfo, BuiltinStringLiteralInfo, BuiltinOperatorInfo, BuiltinIdentigierInfo, BuiltinBracketInfo>;

//----------------------------------------------------------------------------



//----------------------------------------------------------------------------
class GrammaParser
{


public:

    template<typename TokenizerType>
    bool handleInput( TokenizerType &tokenizer
                    , bool bLineStart, payload_type tokenType
                    , typename tokenizer_type::iterator_type b, typename tokenizer_type::iterator_type e
                    , const typename tokenizer_type::token_parsed_data &parsedData // std::basic_string_view<tokenizer_char_type> parsedData
                    , typename tokenizer_type::messages_string_type &errMsg
                    )
    {
        UMBA_USED(tokenizer);
        UMBA_USED(bLineStart);
        UMBA_USED(tokenType);
        UMBA_USED(b);
        UMBA_USED(e);
        UMBA_USED(parsedData);
        UMBA_USED(errMsg);

        return true; 
    }

}; // class GrammaParser




    // using tokenizer_type       = decltype(tokenizer);
    // using InputIteratorType    = typename tokenizer_type::iterator_type;
    // using tokenizer_char_type  = typename tokenizer_type::value_type;
    // using messages_string_type = typename tokenizer_type::messages_string_type;
    // using token_parsed_data    = typename tokenizer_type::token_parsed_data;
    //  
    //  
    // // tokenizer.setResetCharClassFlags('#', umba::tokenizer::CharClass::none, umba::tokenizer::CharClass::opchar); // Ничего не устанавливаем, сбрасываем opchar
    // // tokenizer.setResetCharClassFlags('<', umba::tokenizer::CharClass::none, umba::tokenizer::CharClass::string_literal_prefix); // По дефолту символ '<' не является маркером строкового литерала
    // // bool isStartAngleBracketIsOperator = (tokenizer.getCharClass('<') & umba::tokenizer::CharClass::opchar) != 0;
    // // bool isEndAngleBracketIsOperator   = (tokenizer.getCharClass('>') & umba::tokenizer::CharClass::opchar) != 0;
    //  
    //  
    // tokenizer.tokenHandler = [&]( tokenizer_type &tokenizer
    //                             , bool bLineStart, payload_type tokenType
    //                             , InputIteratorType b, InputIteratorType e
    //                             , token_parsed_data parsedData // std::basic_string_view<tokenizer_char_type> parsedData
    //                             , messages_string_type &errMsg
    //                             ) -> bool
    //                          {




} // namespace tbnf

} // namespace umba



