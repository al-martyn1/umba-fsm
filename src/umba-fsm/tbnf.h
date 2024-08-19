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
#include <unordered_map>
#include <unordered_set>


//----------------------------------------------------------------------------



//----------------------------------------------------------------------------
namespace umba{

namespace tbnf {

//----------------------------------------------------------------------------

// template<typename TValue> using TheValue = umba::TheValue<TValue>;
// template<typename TFlags> using TheFlags = umba::TheFlags<TFlags>;

#include "umba/the_.h"



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

    BuiltinNonTerminalInfoBase(BuiltinTokenType tt) : tokenType(tt) {}

}; // struct BuiltinNonTerminalInfoBase

//----------------------------------------------------------------------------



//----------------------------------------------------------------------------
struct BuiltinCommentInfo : public BuiltinNonTerminalInfoBase
{
    std::string               prefix;
    std::string               suffix;
    BuiltinTokenTypeParam     position = BuiltinTokenTypeParam::invalid; // allowed values: beginOnly/any

    UMBA_RULE_OF_FIVE(BuiltinCommentInfo, default, default, default, default, default);

    BuiltinCommentInfo(const BuiltinNonTerminalInfoBase &b) : BuiltinNonTerminalInfoBase(b)  {}
    BuiltinCommentInfo(BuiltinTokenType tt)                 : BuiltinNonTerminalInfoBase(tt) {}

}; // struct BuiltinCommentInfo

//----------------------------------------------------------------------------



//----------------------------------------------------------------------------
struct BuiltinNumberLiteralInfo : public BuiltinNonTerminalInfoBase
{
    unsigned     numberBase = 10;
    std::string  prefix;

    UMBA_RULE_OF_FIVE(BuiltinNumberLiteralInfo, default, default, default, default, default);

    BuiltinNumberLiteralInfo(const BuiltinNonTerminalInfoBase &b) : BuiltinNonTerminalInfoBase(b)  {}
    BuiltinNumberLiteralInfo(BuiltinTokenType tt)                 : BuiltinNonTerminalInfoBase(tt) {}

}; // struct BuiltinNumberLiteralInfo

//----------------------------------------------------------------------------



//----------------------------------------------------------------------------
struct BuiltinStringLiteralInfo : public BuiltinNonTerminalInfoBase
{
    std::string  prefix;
    std::string  kind  ;
    bool         caseIndependent = false;

    UMBA_RULE_OF_FIVE(BuiltinStringLiteralInfo, default, default, default, default, default);

    BuiltinStringLiteralInfo(const BuiltinNonTerminalInfoBase &b) : BuiltinNonTerminalInfoBase(b)  {}
    BuiltinStringLiteralInfo(BuiltinTokenType tt)                 : BuiltinNonTerminalInfoBase(tt) {}

}; // struct BuiltinStringLiteralInfo

//----------------------------------------------------------------------------



//----------------------------------------------------------------------------
struct BuiltinOperatorInfo : public BuiltinNonTerminalInfoBase
{
    std::string  operatorSequence;

    UMBA_RULE_OF_FIVE(BuiltinOperatorInfo, default, default, default, default, default);

    BuiltinOperatorInfo(const BuiltinNonTerminalInfoBase &b) : BuiltinNonTerminalInfoBase(b)  {}
    BuiltinOperatorInfo(BuiltinTokenType tt)                 : BuiltinNonTerminalInfoBase(tt) {}

}; // struct BuiltinOperatorInfo

//----------------------------------------------------------------------------



//----------------------------------------------------------------------------
struct BuiltinIdentigierInfo : public BuiltinNonTerminalInfoBase
{
    std::string  value;

    UMBA_RULE_OF_FIVE(BuiltinIdentigierInfo, default, default, default, default, default);

    BuiltinIdentigierInfo(const BuiltinNonTerminalInfoBase &b) : BuiltinNonTerminalInfoBase(b)  {}
    BuiltinIdentigierInfo(BuiltinTokenType tt)                 : BuiltinNonTerminalInfoBase(tt) {}

}; // struct BuiltinIdentigierInfo

//----------------------------------------------------------------------------



//----------------------------------------------------------------------------
struct BuiltinBracketInfo : public BuiltinNonTerminalInfoBase
{
    std::string               value; // exact one char from set of (){}[]<>
    BuiltinTokenTypeParam     kind = BuiltinTokenTypeParam::invalid; // allowed values: open/close

    UMBA_RULE_OF_FIVE(BuiltinBracketInfo, default, default, default, default, default);

    BuiltinBracketInfo(const BuiltinNonTerminalInfoBase &b) : BuiltinNonTerminalInfoBase(b)  {}
    BuiltinBracketInfo(BuiltinTokenType tt)                 : BuiltinNonTerminalInfoBase(tt) {}

}; // struct BuiltinBracketInfo

//----------------------------------------------------------------------------



//----------------------------------------------------------------------------
// struct BuiltinEmptyInfo
// struct BuiltinNonTerminalInfoBase
// struct BuiltinCommentInfo : public BuiltinNonTerminalInfoBase
// struct BuiltinNumberLiteralInfo : public BuiltinNonTerminalInfoBase
// struct BuiltinStringLiteralInfo : public BuiltinNonTerminalInfoBase
// struct BuiltinOperatorInfo : public BuiltinNonTerminalInfoBase
// struct BuiltinIdentigierInfo : public BuiltinNonTerminalInfoBase
// struct BuiltinBracketInfo : public BuiltinNonTerminalInfoBase
using BuiltinNonTerminalInfo = std::variant<BuiltinEmptyInfo, BuiltinCommentInfo, BuiltinNumberLiteralInfo, BuiltinStringLiteralInfo, BuiltinOperatorInfo, BuiltinIdentigierInfo, BuiltinBracketInfo>;

//----------------------------------------------------------------------------



//----------------------------------------------------------------------------
class GrammaParser
{

    enum State
    {
        stInitial           ,
        stWaitAssignment    ,
        stReadRule          ,
        stWaitBultinRuleType,
        stReadUserRule      ,
        stReadBuiltinRule
    };

    State                   st = stInitial;
    std::string             currentRuleName;
    BuiltinNonTerminalInfo  builtinRuleInfo;
    BuiltinTokenType        curBuiltinTokenType;
    BuiltinTokenTypeParam   curBuiltinTokenTypeParam;



    void resetImpl()
    {
         // Тут неплохо бы сохранить состояние до ресета, для дальнейшего исследования того, как мы докатились до такой жизни

         st = stInitial;
    }

    bool reset(bool res)
    {
        resetImpl();
        return res;
    }

    template<typename MsgStringType>
    bool reset(bool res, MsgStringType &msgSetTo, const MsgStringType &msg)
    {
        resetImpl();

        if (!res)
        {
            msgSetTo = msg;
        }

        return res;
    }

    bool isCommentToken(payload_type tokenType)
    {
        if (tokenType>=UMBA_TOKENIZER_TOKEN_OPERATOR_SINGLE_LINE_COMMENT_FIRST && tokenType<=UMBA_TOKENIZER_TOKEN_OPERATOR_SINGLE_LINE_COMMENT_LAST)
            return true;

        if (tokenType==UMBA_TOKENIZER_TOKEN_OPERATOR_MULTI_LINE_COMMENT_START || tokenType==UMBA_TOKENIZER_TOKEN_OPERATOR_MULTI_LINE_COMMENT_END)
            return true;

        return false;
    }

    static
    std::unordered_map<BuiltinTokenType, std::unordered_set<BuiltinTokenTypeParam> >  makeBuiltinRulesAllowedParams()
    {
        return std::unordered_map<BuiltinTokenType, std::unordered_set<BuiltinTokenTypeParam> >
        { { BuiltinTokenType::integralNumber   , { BuiltinTokenTypeParam::tokenId, BuiltinTokenTypeParam::name, BuiltinTokenTypeParam::base, BuiltinTokenTypeParam::prefix } }
        , { BuiltinTokenType::floatNumber      , { BuiltinTokenTypeParam::tokenId, BuiltinTokenTypeParam::name, BuiltinTokenTypeParam::base, BuiltinTokenTypeParam::prefix } }
        , { BuiltinTokenType::operatorSequence , { BuiltinTokenTypeParam::tokenId, BuiltinTokenTypeParam::name, BuiltinTokenTypeParam::value } }
        , { BuiltinTokenType::stringLiteral    , { BuiltinTokenTypeParam::tokenId, BuiltinTokenTypeParam::name, BuiltinTokenTypeParam::prefix, BuiltinTokenTypeParam::kind  } }
        , { BuiltinTokenType::identifier       , { BuiltinTokenTypeParam::tokenId, BuiltinTokenTypeParam::name, BuiltinTokenTypeParam::value } }
        , { BuiltinTokenType::bracket          , { BuiltinTokenTypeParam::tokenId, BuiltinTokenTypeParam::name, BuiltinTokenTypeParam::open  , BuiltinTokenTypeParam::close } }
        , { BuiltinTokenType::sComment         , { BuiltinTokenTypeParam::tokenId, BuiltinTokenTypeParam::name, BuiltinTokenTypeParam::prefix, BuiltinTokenTypeParam::position } }
        , { BuiltinTokenType::mComment         , { BuiltinTokenTypeParam::tokenId, BuiltinTokenTypeParam::name, BuiltinTokenTypeParam::prefix, BuiltinTokenTypeParam::suffix } }
        };
    }

    static
    const std::unordered_map<BuiltinTokenType, std::unordered_set<BuiltinTokenTypeParam> >& getBuiltinRulesAllowedParams()
    {
        static auto m = makeBuiltinRulesAllowedParams();
        return m;
    }

    static
    std::unordered_map<BuiltinTokenTypeParam, std::unordered_set<payload_type> > makeBuiltinRulesAllowedParamValueTypes()
    {
        return std::unordered_map<BuiltinTokenTypeParam, std::unordered_set<payload_type> >
        { { BuiltinTokenTypeParam::base      , { UMBA_TOKENIZER_TOKEN_INTEGRAL_NUMBER } } // только десятичный числовой литерал
        , { BuiltinTokenTypeParam::prefix    , { UMBA_TOKENIZER_TOKEN_STRING_LITERAL } }
        , { BuiltinTokenTypeParam::suffix    , { UMBA_TOKENIZER_TOKEN_STRING_LITERAL } }
        , { BuiltinTokenTypeParam::tokenId   , { UMBA_TOKENIZER_TOKEN_IDENTIFIER, UMBA_TOKENIZER_TOKEN_INTEGRAL_NUMBER, UMBA_TOKENIZER_TOKEN_INTEGRAL_NUMBER_DEC, UMBA_TOKENIZER_TOKEN_INTEGRAL_NUMBER_BIN, UMBA_TOKENIZER_TOKEN_INTEGRAL_NUMBER_OCT, UMBA_TOKENIZER_TOKEN_INTEGRAL_NUMBER_HEX  } }
        , { BuiltinTokenTypeParam::name      , { UMBA_TOKENIZER_TOKEN_IDENTIFIER, UMBA_TOKENIZER_TOKEN_STRING_LITERAL } }
        , { BuiltinTokenTypeParam::kind      , { UMBA_TOKENIZER_TOKEN_IDENTIFIER, UMBA_TOKENIZER_TOKEN_STRING_LITERAL } }
        , { BuiltinTokenTypeParam::value     , { UMBA_TOKENIZER_TOKEN_STRING_LITERAL } }
        , { BuiltinTokenTypeParam::open      , { UMBA_TOKENIZER_TOKEN_STRING_LITERAL } }
        , { BuiltinTokenTypeParam::close     , { UMBA_TOKENIZER_TOKEN_STRING_LITERAL } }
        , { BuiltinTokenTypeParam::position  , { UMBA_TOKENIZER_TOKEN_IDENTIFIER } }
        //, { BuiltinTokenTypeParam::startOnly , {} } // Это значение параметра, а не сам параметр
        //, { BuiltinTokenTypeParam::any       , {} }
        };
    }

    // template <typename StringType>
    // using make_string = umba::string_plus::make_string<StringType>;

    

    static
    const std::unordered_map<BuiltinTokenTypeParam, std::unordered_set<payload_type> >& getBuiltinRulesAllowedParamValueTypes()
    {
        static auto m = makeBuiltinRulesAllowedParamValueTypes();
        return m;
    }


    template<typename ContainerType, typename StringType, typename ValueConverter>
    static
    void makeSetValuesStringCommaList(const ContainerType &c, StringType &resStr, ValueConverter valueConverter, bool quoted=true)
    {
        using umba::string_plus::make_string;

        resStr.clear();
        for(auto v : c)
        {
            if (!resStr.empty())
                resStr.append(make_string<StringType>(", "));

            if (quoted)
                resStr.append(make_string<StringType>("'"));

            resStr.append(make_string<StringType>(valueConverter(v)));

            if (quoted)
                resStr.append(make_string<StringType>("'"));
        }
    }
    
    template<typename StringType>
    StringType makeBuiltinTokenTypeStringCommaList(bool quoted=true) const
    {
        const auto &c = getBuiltinRulesAllowedParams();
        StringType resStr;
        makeSetValuesStringCommaList( c, resStr
                                    , [&](auto p)
                                      {
                                          return enum_serialize(p.first);
                                      }
                                    , quoted
                                    );
        return resStr;
    }

    template<typename StringType>
    StringType makeBuiltinTokenTypeParamStringCommaList(BuiltinTokenType btk, bool quoted=true) const
    {
        const auto &c = getBuiltinRulesAllowedParams();
        auto it = c.find(btk);
        if (it==c.end())
            return StringType();

        StringType resStr;
        makeSetValuesStringCommaList( it->second, resStr
                                    , [&](auto v)
                                      {
                                          return enum_serialize(v);
                                      }
                                    , quoted
                                    );
        return resStr;
    }

    template<typename StringType>
    StringType makeBuiltinTokenTypeParamAllowedValuesStringCommaList(const std::unordered_set<payload_type> &s, bool quoted=true) const
    {
        StringType resStr;
        makeSetValuesStringCommaList( s, resStr
                                    , [&](auto v)
                                      {
                                          return umba::tokenizer::getTokenizerTokenStr<StringType>(v);
                                      }
                                    , quoted
                                    );
        return resStr;
    }


    // template<typename TokenizerType, typename SrcMessageType>
    // typename TokenizerType::messages_string_type
    // msg(SrcMessageType m)
    // {
    //     return typename TokenizerType::messages_string_type(m);
    // }


public:

    template<typename TokenizerType>
    bool handleToken( TokenizerType &tokenizer
                    , bool bLineStart, payload_type tokenType
                    , typename TokenizerType::iterator_type b, typename TokenizerType::iterator_type e
                    , const typename TokenizerType::token_parsed_data &parsedData // std::basic_string_view<tokenizer_char_type> parsedData
                    , typename TokenizerType::messages_string_type &errMsg
                    )
    {
        using msgt = typename TokenizerType::messages_string_type;

        using umba::string_plus::make_string;


        if (tokenType==UMBA_TOKENIZER_TOKEN_CTRL_FIN)
        {
            // Пока просто ресетим, но потом тут могут быть ошибки, в зависимости от текущего состояния
            return reset(true);
        }

        if (isCommentToken(tokenType))
        {
            return true;
        }


        switch(st)
        {
            case stInitial:
            {
                if (TheValue(tokenType).oneOf(UMBA_TOKENIZER_TOKEN_SPACE, UMBA_TOKENIZER_TOKEN_TAB, UMBA_TOKENIZER_TOKEN_LINEFEED /* , UMBA_TOKENIZER_TOKEN_LINE_CONTINUATION */ )) // На пустом месте континуация?
                    return true; // Ничего не делаем

                if (tokenType==UMBA_TOKENIZER_TOKEN_IDENTIFIER)
                {
                    auto identifierData = std::get<typename TokenizerType::IdentifierData>(parsedData);
                    currentRuleName = identifierData.data; // из string_view в строку
                    st = stWaitAssignment;
                    return true;
                }

                return reset(false, errMsg, make_string<msgt>("Unexpected ") + umba::tokenizer::getTokenizerTokenStr<msgt>(tokenType));
            }

            case stWaitAssignment:
            {
                if (TheValue(tokenType).oneOf(UMBA_TOKENIZER_TOKEN_SPACE, UMBA_TOKENIZER_TOKEN_TAB, UMBA_TOKENIZER_TOKEN_LINE_CONTINUATION))
                    return true; // Ничего не делаем

                //if (TheValue(tokenType).oneOf(UMBA_TOKENIZER_TOKEN_OPERATOR_ASSIGNMENT))
                if (tokenType==UMBA_TOKENIZER_TOKEN_OPERATOR_ASSIGNMENT)
                {
                    st = stReadRule;
                    return true;
                }

                return reset(false, errMsg, make_string<msgt>("Unexpected ") + umba::tokenizer::getTokenizerTokenStr<msgt>(tokenType));
            }

            case stReadRule:
            {
                if (TheValue(tokenType).oneOf(UMBA_TOKENIZER_TOKEN_SPACE, UMBA_TOKENIZER_TOKEN_TAB, UMBA_TOKENIZER_TOKEN_LINE_CONTINUATION))
                    return true; // Ничего не делаем

                if (tokenType==UMBA_TOKENIZER_TOKEN_OPERATOR_AT)
                {
                    st = stWaitBultinRuleType;
                    return true;
                }

                return reset(false, errMsg, make_string<msgt>("User rules not currently implemented") );
            }

            case stWaitBultinRuleType:
            {
                if (TheValue(tokenType).oneOf(UMBA_TOKENIZER_TOKEN_SPACE, UMBA_TOKENIZER_TOKEN_TAB, UMBA_TOKENIZER_TOKEN_LINE_CONTINUATION))
                    return true; // Ничего не делаем

                if (TheValue(tokenType).oneOf(UMBA_TOKENIZER_TOKEN_IDENTIFIER))
                {
                    auto identifierData       = std::get<typename TokenizerType::IdentifierData>(parsedData);
                    typename TokenizerType::string_type ruleTypeStr = typename TokenizerType::string_type(identifierData.data); // из string_view в строку
                    BuiltinTokenType ruleType = enum_deserialize(make_string<std::string>(ruleTypeStr), BuiltinTokenType::invalid);

                    if (ruleType==BuiltinTokenType::invalid)
                    {
                        return reset(false, errMsg, make_string<msgt>("Expected ") + makeBuiltinTokenTypeStringCommaList<msgt>() + make_string<msgt>(" keyword, but got ")
                                                  + make_string<msgt>("'") + make_string<msgt>(ruleTypeStr) + make_string<msgt>("'")
                                    );
                    }

                    switch(ruleType)
                    {
                        case BuiltinTokenType::integralNumber   : builtinRuleInfo = BuiltinNumberLiteralInfo(BuiltinTokenType::integralNumber); break;
                        case BuiltinTokenType::floatNumber      : builtinRuleInfo = BuiltinNumberLiteralInfo(BuiltinTokenType::floatNumber   ); break;
                        case BuiltinTokenType::operatorSequence : builtinRuleInfo = BuiltinOperatorInfo(BuiltinTokenType::operatorSequence); break;
                        case BuiltinTokenType::stringLiteral    : builtinRuleInfo = BuiltinStringLiteralInfo(BuiltinTokenType::stringLiteral); break;
                        case BuiltinTokenType::identifier       : builtinRuleInfo = BuiltinIdentigierInfo(BuiltinTokenType::identifier); break;
                        case BuiltinTokenType::bracket          : builtinRuleInfo = BuiltinBracketInfo(BuiltinTokenType::bracket); break;
                        case BuiltinTokenType::sComment         : builtinRuleInfo = BuiltinCommentInfo(BuiltinTokenType::sComment); break;
                        case BuiltinTokenType::mComment         : builtinRuleInfo = BuiltinCommentInfo(BuiltinTokenType::mComment); break;
                        default:

                             return reset(false, errMsg, make_string<msgt>("Unknown builtin rule type: ") + make_string<msgt>(ruleTypeStr));
                    }

                    st = stReadBuiltinRule;
                    curBuiltinTokenType      = ruleType;
                    curBuiltinTokenTypeParam = BuiltinTokenTypeParam::invalid;

                    return true;
                }

                return reset(false, errMsg, make_string<msgt>("Unexpected ") + umba::tokenizer::getTokenizerTokenStr<msgt>(tokenType));

            }

            case stReadBuiltinRule:
            {
                if (TheValue(tokenType).oneOf(UMBA_TOKENIZER_TOKEN_SPACE, UMBA_TOKENIZER_TOKEN_TAB, UMBA_TOKENIZER_TOKEN_LINE_CONTINUATION))
                    return true; // Ничего не делаем

                if (TheValue(tokenType).oneOf(UMBA_TOKENIZER_TOKEN_LINEFEED))
                {
                    if (curBuiltinTokenTypeParam!=BuiltinTokenTypeParam::invalid)
                    {
                        // ожидаем имя параметра
                        return reset(false, errMsg, make_string<msgt>("Unexpected rule end"));
                    }
                    else
                    {
                        // Тут надо бы финализировать разбор правила


                        st = stInitial; // Возврат в исходное состояние
                        return true;
                    }
                }


                if (curBuiltinTokenTypeParam==BuiltinTokenTypeParam::invalid)
                {
                    // ожидаем имя параметра

                    if (!TheValue(tokenType).oneOf(UMBA_TOKENIZER_TOKEN_IDENTIFIER))
                    {
                        return reset(false, errMsg, make_string<msgt>(enum_serialize(curBuiltinTokenType)) + make_string<msgt>(": ")
                                                  + make_string<msgt>("Expected ") + umba::tokenizer::getTokenizerTokenStr<msgt>(UMBA_TOKENIZER_TOKEN_IDENTIFIER) 
                                                  + make_string<msgt>(", but got ") + umba::tokenizer::getTokenizerTokenStr<msgt>(tokenType) 
                                    );
                    }

                    auto identifierData       = std::get<typename TokenizerType::IdentifierData>(parsedData);
                    typename TokenizerType::string_type paramTypeStr = typename TokenizerType::string_type(identifierData.data); // из string_view в строку

                    // Пытаемся десериализовать тип параметра
                    BuiltinTokenTypeParam paramType = enum_deserialize(make_string<std::string>(paramTypeStr), BuiltinTokenTypeParam::invalid);
                    if (paramType==BuiltinTokenTypeParam::invalid)
                    {
                        return reset(false, errMsg, make_string<msgt>(enum_serialize(curBuiltinTokenType)) + make_string<msgt>(": ")
                                                  + make_string<msgt>("Expected ") + makeBuiltinTokenTypeParamStringCommaList<msgt>(curBuiltinTokenType) + make_string<msgt>(" keyword, but got ")
                                                  + make_string<msgt>("'") + make_string<msgt>(paramTypeStr) + make_string<msgt>("'")
                                    );
                    }

                    // Проверяем, валидный ли параметр для 
                    const auto &c = getBuiltinRulesAllowedParams();
                    auto it = c.find(curBuiltinTokenType);
                    if (it==c.end())
                    {
                        return reset(false, errMsg, make_string<msgt>("Internal error (1)"));
                    }

                    const auto &allowedVals = it->second;
                    if (allowedVals.find(paramType)==allowedVals.end())
                    {
                        return reset(false, errMsg, make_string<msgt>(enum_serialize(curBuiltinTokenType)) + make_string<msgt>(": Unexpected parameter. ")
                                                  + make_string<msgt>("Expected ") + makeBuiltinTokenTypeParamStringCommaList<msgt>(curBuiltinTokenType) + make_string<msgt>(" parameter, but got ")
                                                  + make_string<msgt>("'") + make_string<msgt>(paramTypeStr) + make_string<msgt>("'")
                                    );
                    }

                    curBuiltinTokenTypeParam = paramType;

                }
                else
                {
                    // читаем значение параметра

                    const auto &apvMap = getBuiltinRulesAllowedParamValueTypes();
                    auto avpIt = apvMap.find(curBuiltinTokenTypeParam);
                    if (avpIt==apvMap.end())
                    {
                        return reset(false, errMsg, make_string<msgt>("Internal error (2)"));
                    }

                    const auto &apvSet = avpIt->second;

                    if (apvSet.find(tokenType)==apvSet.end())
                    {
                        return reset(false, errMsg, make_string<msgt>(enum_serialize(curBuiltinTokenType)) + make_string<msgt>(": Unexpected parameter value. ")
                                                  + make_string<msgt>("Expected ") + makeBuiltinTokenTypeParamAllowedValuesStringCommaList<msgt>(apvSet, false) + make_string<msgt>(" value, but got ")
                                                  + make_string<msgt>("") + umba::tokenizer::getTokenizerTokenStr<msgt>(tokenType) /* make_string<msgt>(paramTypeStr) */  + make_string<msgt>("")
                                    );
                    }

                    // Тут уже параметр только поддерживаемого типа


                    curBuiltinTokenTypeParam = BuiltinTokenTypeParam::invalid; // Прочитали, разобрали, сбрасываем тип параметра для чтения следующего
                }

                break;
            }



        // stWaitBultinRuleType
        // stReadUserRule,
        // stReadBuiltinRule,

    // StringType makeBuiltinTokenTypeStringCommaList()
    // StringType makeBuiltinTokenTypeParamStringCommaList(BuiltinTokenType btk)

        
            default:
            {
                return reset(false, errMsg, msgt("Parser state not currently handled") );
            }

        } // switch(st)

        // getBuiltinRulesAllowedParams()
        // getBuiltinRulesAllowedParamValueTypes()

        // UMBA_TOKENIZER_TOKEN_OPERATOR_ASSIGNMENT
    

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



