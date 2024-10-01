#pragma once

#include "umba/umba.h"
//
#include "umba/tokenizer.h"
#include "umba/text_position_info.h"
#include "umba/iterator.h"
#include "umba/the.h"
//
#include "marty_cpp/src_normalization.h"


template<typename StringType>
StringType getTokenKindString(umba::tokenizer::payload_type p)
{
    switch(p)
    {
        case UMBA_TOKENIZER_TOKEN_UNEXPECTED                         : return umba::string_plus::make_string<StringType>("unxp");
        case UMBA_TOKENIZER_TOKEN_LINEFEED                           : return umba::string_plus::make_string<StringType>("");
        case UMBA_TOKENIZER_TOKEN_SPACE                              : return umba::string_plus::make_string<StringType>("");
        case UMBA_TOKENIZER_TOKEN_TAB                                : return umba::string_plus::make_string<StringType>("");
        case UMBA_TOKENIZER_TOKEN_IDENTIFIER                         : return umba::string_plus::make_string<StringType>("ident");
        case UMBA_TOKENIZER_TOKEN_SEMIALPHA                          : return umba::string_plus::make_string<StringType>("");
        // https://en.wikipedia.org/wiki/Bracket
        case UMBA_TOKENIZER_TOKEN_CURLY_BRACKET_OPEN                 : return umba::string_plus::make_string<StringType>("curly");
        case UMBA_TOKENIZER_TOKEN_CURLY_BRACKET_CLOSE                : return umba::string_plus::make_string<StringType>("curly");
        case UMBA_TOKENIZER_TOKEN_ROUND_BRACKET_OPEN                 : return umba::string_plus::make_string<StringType>("round");
        case UMBA_TOKENIZER_TOKEN_ROUND_BRACKET_CLOSE                : return umba::string_plus::make_string<StringType>("round");
        case UMBA_TOKENIZER_TOKEN_ANGLE_BRACKET_OPEN                 : return umba::string_plus::make_string<StringType>("angle");
        case UMBA_TOKENIZER_TOKEN_ANGLE_BRACKET_CLOSE                : return umba::string_plus::make_string<StringType>("angle");
        case UMBA_TOKENIZER_TOKEN_SQUARE_BRACKET_OPEN                : return umba::string_plus::make_string<StringType>("square");
        case UMBA_TOKENIZER_TOKEN_SQUARE_BRACKET_CLOSE               : return umba::string_plus::make_string<StringType>("square");
        case UMBA_TOKENIZER_TOKEN_OPERATOR_MULTI_LINE_COMMENT_START  : return umba::string_plus::make_string<StringType>("cmnt");
        case UMBA_TOKENIZER_TOKEN_OPERATOR_MULTI_LINE_COMMENT_END    : return umba::string_plus::make_string<StringType>("cmnt");
        case UMBA_TOKENIZER_TOKEN_CTRL_CC_PP_START                   : return umba::string_plus::make_string<StringType>("pp");
        case UMBA_TOKENIZER_TOKEN_CTRL_CC_PP_END                     : return umba::string_plus::make_string<StringType>("pp");

        case UMBA_TOKENIZER_TOKEN_OPERATOR_TRANSITION                : return umba::string_plus::make_string<StringType>("TRANSITION");
        case UMBA_TOKENIZER_TOKEN_OPERATOR_PLANTUML_TRANSITION_DIRECTED       : return umba::string_plus::make_string<StringType>("TRANSITION_DIRECTED");
        case UMBA_TOKENIZER_TOKEN_OPERATOR_PLANTUML_TRANSITION_DIRECTED_UP    : return umba::string_plus::make_string<StringType>("TRANSITION_DIRECTED_UP");
        case UMBA_TOKENIZER_TOKEN_OPERATOR_PLANTUML_TRANSITION_DIRECTED_DOWN  : return umba::string_plus::make_string<StringType>("TRANSITION_DIRECTED_DOWN");
        case UMBA_TOKENIZER_TOKEN_OPERATOR_PLANTUML_TRANSITION_DIRECTED_LEFT  : return umba::string_plus::make_string<StringType>("TRANSITION_DIRECTED_LEFT");
        case UMBA_TOKENIZER_TOKEN_OPERATOR_PLANTUML_TRANSITION_DIRECTED_RIGHT : return umba::string_plus::make_string<StringType>("TRANSITION_DIRECTED_RIGHT");

        case UMBA_TOKENIZER_TOKEN_PLANTUML_PSEUDO_STATE                       : return umba::string_plus::make_string<StringType>("PSEUDO_STATE");
        case UMBA_TOKENIZER_TOKEN_PLANTUML_HISTORY_STATE                      : return umba::string_plus::make_string<StringType>("HISTORY_STATE");
        case UMBA_TOKENIZER_TOKEN_PLANTUML_HISTORYPLUS_STATE                  : return umba::string_plus::make_string<StringType>("HISTORYPLUS_STATE");

        case UMBA_TOKENIZER_TOKEN_PLANTUML_STARTUML                           : return umba::string_plus::make_string<StringType>("STARTUML");
        case UMBA_TOKENIZER_TOKEN_PLANTUML_ENDUML                             : return umba::string_plus::make_string<StringType>("ENDUML");

        case UMBA_TOKENIZER_TOKEN_PLANTUML_GENERIC_TAG_START                  : return umba::string_plus::make_string<StringType>("GENERIC_TAG_START");
        case UMBA_TOKENIZER_TOKEN_PLANTUML_GENERIC_TAG_END                    : return umba::string_plus::make_string<StringType>("GENERIC_TAG_END");

        case UMBA_TOKENIZER_TOKEN_PLANTUML_GENERIC_STEREOTYPE                 : return umba::string_plus::make_string<StringType>("GENERIC_STEREOTYPE");

        case UMBA_TOKENIZER_TOKEN_PLANTUML_STEREOTYPE_FORK                    : return umba::string_plus::make_string<StringType>("STEREOTYPE_FORK");
        case UMBA_TOKENIZER_TOKEN_PLANTUML_STEREOTYPE_JOIN                    : return umba::string_plus::make_string<StringType>("STEREOTYPE_JOIN");
        case UMBA_TOKENIZER_TOKEN_PLANTUML_STEREOTYPE_CHOICE                  : return umba::string_plus::make_string<StringType>("STEREOTYPE_CHOICE");
        case UMBA_TOKENIZER_TOKEN_PLANTUML_STEREOTYPE_START                   : return umba::string_plus::make_string<StringType>("STEREOTYPE_START");
        case UMBA_TOKENIZER_TOKEN_PLANTUML_STEREOTYPE_END                     : return umba::string_plus::make_string<StringType>("STEREOTYPE_END");
        case UMBA_TOKENIZER_TOKEN_PLANTUML_STEREOTYPE_ENTRYPOINT              : return umba::string_plus::make_string<StringType>("STEREOTYPE_ENTRYPOINT");
        case UMBA_TOKENIZER_TOKEN_PLANTUML_STEREOTYPE_EXITPOINT               : return umba::string_plus::make_string<StringType>("STEREOTYPE_EXITPOINT");
        case UMBA_TOKENIZER_TOKEN_PLANTUML_STEREOTYPE_INPUTPIN                : return umba::string_plus::make_string<StringType>("STEREOTYPE_INPUTPIN");
        case UMBA_TOKENIZER_TOKEN_PLANTUML_STEREOTYPE_OUTPUTPIN               : return umba::string_plus::make_string<StringType>("STEREOTYPE_OUTPUTPIN");
        case UMBA_TOKENIZER_TOKEN_PLANTUML_STEREOTYPE_EXPANSIONINPUT          : return umba::string_plus::make_string<StringType>("STEREOTYPE_EXPANSIONINPUT");
        case UMBA_TOKENIZER_TOKEN_PLANTUML_STEREOTYPE_EXPANSIONOUTPUT         : return umba::string_plus::make_string<StringType>("STEREOTYPE_EXPANSIONOUTPUT");

        case UMBA_TOKENIZER_TOKEN_OPERATOR_PLANTUML_HSPLIT                    : return umba::string_plus::make_string<StringType>("HSPLIT");
        case UMBA_TOKENIZER_TOKEN_OPERATOR_PLANTUML_VSPLIT                    : return umba::string_plus::make_string<StringType>("VSPLIT");

        case UMBA_TOKENIZER_TOKEN_PLANTUML_STATE                              : return umba::string_plus::make_string<StringType>("STATE"      );
        case UMBA_TOKENIZER_TOKEN_PLANTUML_HIDE                               : return umba::string_plus::make_string<StringType>("HIDE"       );
        case UMBA_TOKENIZER_TOKEN_PLANTUML_EMPTY                              : return umba::string_plus::make_string<StringType>("EMPTY"      );
        case UMBA_TOKENIZER_TOKEN_PLANTUML_DESCRIPTION                        : return umba::string_plus::make_string<StringType>("DESCRIPTION");
        case UMBA_TOKENIZER_TOKEN_PLANTUML_SCALE                              : return umba::string_plus::make_string<StringType>("SCALE"      );
        case UMBA_TOKENIZER_TOKEN_PLANTUML_WIDTH                              : return umba::string_plus::make_string<StringType>("WIDTH"      );
        case UMBA_TOKENIZER_TOKEN_PLANTUML_HEIGHT                             : return umba::string_plus::make_string<StringType>("HEIGHT"     );
        case UMBA_TOKENIZER_TOKEN_PLANTUML_AS                                 : return umba::string_plus::make_string<StringType>("AS"         );
        case UMBA_TOKENIZER_TOKEN_PLANTUML_NOTE                               : return umba::string_plus::make_string<StringType>("NOTE"       );
        case UMBA_TOKENIZER_TOKEN_PLANTUML_ON                                 : return umba::string_plus::make_string<StringType>("ON"         );
        case UMBA_TOKENIZER_TOKEN_PLANTUML_END                                : return umba::string_plus::make_string<StringType>("END"        );
        case UMBA_TOKENIZER_TOKEN_PLANTUML_OF                                 : return umba::string_plus::make_string<StringType>("OF"         );
        case UMBA_TOKENIZER_TOKEN_PLANTUML_UP                                 : return umba::string_plus::make_string<StringType>("UP"         );
        case UMBA_TOKENIZER_TOKEN_PLANTUML_DOWN                               : return umba::string_plus::make_string<StringType>("DOWN"       );
        case UMBA_TOKENIZER_TOKEN_PLANTUML_LEFT                               : return umba::string_plus::make_string<StringType>("LEFT"       );
        case UMBA_TOKENIZER_TOKEN_PLANTUML_RIGHT                              : return umba::string_plus::make_string<StringType>("RIGHT"      );
        case UMBA_TOKENIZER_TOKEN_PLANTUML_DASHED                             : return umba::string_plus::make_string<StringType>("DASHED"     );
        case UMBA_TOKENIZER_TOKEN_PLANTUML_DOTTED                             : return umba::string_plus::make_string<StringType>("DOTTED"     );
        case UMBA_TOKENIZER_TOKEN_PLANTUML_BOLD                               : return umba::string_plus::make_string<StringType>("BOLD"       );
        case UMBA_TOKENIZER_TOKEN_PLANTUML_ITALIC                             : return umba::string_plus::make_string<StringType>("ITALIC"     );

        case UMBA_TOKENIZER_TOKEN_PLANTUML_STYLE_TAG_START                    : return umba::string_plus::make_string<StringType>("STYLE_TAG_START");
        case UMBA_TOKENIZER_TOKEN_PLANTUML_STYLE_TAG_END                      : return umba::string_plus::make_string<StringType>("STYLE_TAG_END  ");



        // case : return umba::string_plus::make_string<StringType>("");
        // case : return umba::string_plus::make_string<StringType>("");
        // case : return umba::string_plus::make_string<StringType>("");
        // case : return umba::string_plus::make_string<StringType>("");
        // case : return umba::string_plus::make_string<StringType>("");
        // case : return umba::string_plus::make_string<StringType>("");




        //case : return umba::string_plus::make_string<StringType>("");
        default:

            if (p>=UMBA_TOKENIZER_TOKEN_NUMBER_LITERAL_FIRST && p<=UMBA_TOKENIZER_TOKEN_NUMBER_LITERAL_LAST)
            {
                if (p&UMBA_TOKENIZER_TOKEN_FLOAT_FLAG)
                    return umba::string_plus::make_string<StringType>("num");
                else
                    return umba::string_plus::make_string<StringType>("num");
            }

            if (p>=UMBA_TOKENIZER_TOKEN_OPERATOR_SINGLE_LINE_COMMENT_FIRST && p<=UMBA_TOKENIZER_TOKEN_OPERATOR_SINGLE_LINE_COMMENT_LAST)
                return umba::string_plus::make_string<StringType>("cmnt");

            //if (p>=UMBA_TOKENIZER_TOKEN_NUMBER_USER_LITERAL_FIRST && p<=UMBA_TOKENIZER_TOKEN_NUMBER_USER_LITERAL_LAST)
            if (p>=UMBA_TOKENIZER_TOKEN_NUMBER_LITERAL_FIRST && p<=UMBA_TOKENIZER_TOKEN_NUMBER_LITERAL_LAST)
                return umba::string_plus::make_string<StringType>("num");

            if (p>=UMBA_TOKENIZER_TOKEN_OPERATOR_FIRST && p<=UMBA_TOKENIZER_TOKEN_OPERATOR_LAST)
                return umba::string_plus::make_string<StringType>("op");

            if (p>=UMBA_TOKENIZER_TOKEN_STRING_LITERAL_FIRST && p<=UMBA_TOKENIZER_TOKEN_STRING_LITERAL_LAST)
                return umba::string_plus::make_string<StringType>("str");

            if (p>=UMBA_TOKENIZER_TOKEN_KEYWORD_SET1_FIRST && p<=UMBA_TOKENIZER_TOKEN_KEYWORD_SET1_LAST)
                return umba::string_plus::make_string<StringType>("kwd1");

            if (p>=UMBA_TOKENIZER_TOKEN_KEYWORD_SET2_FIRST && p<=UMBA_TOKENIZER_TOKEN_KEYWORD_SET2_LAST)
                return umba::string_plus::make_string<StringType>("kwd2");

            if (p>=UMBA_TOKENIZER_TOKEN_KEYWORD_SET3_FIRST && p<=UMBA_TOKENIZER_TOKEN_KEYWORD_SET3_LAST)
                return umba::string_plus::make_string<StringType>("kwd3");

            if (p>=UMBA_TOKENIZER_TOKEN_KEYWORD_SET4_FIRST && p<=UMBA_TOKENIZER_TOKEN_KEYWORD_SET4_LAST)
                return umba::string_plus::make_string<StringType>("kwd4");

            return umba::string_plus::make_string<StringType>("");
    }
}


inline
auto makeTokenText(umba::tokenizer::payload_type tokenType, umba::iterator::TextPositionCountingIterator<char> b, umba::iterator::TextPositionCountingIterator<char> e)
{
    if (tokenType==UMBA_TOKENIZER_TOKEN_LINEFEED)
    {
        return std::string("\n");
    }

    if (tokenType==UMBA_TOKENIZER_TOKEN_LINE_CONTINUATION)
    {
        return std::string("\\\n");
    }

    if (tokenType==UMBA_TOKENIZER_TOKEN_OPERATOR_MULTI_LINE_COMMENT_START)
    {
        return marty_cpp::normalizeCrLfToLf(umba::iterator::makeString(b, e));
    }

    return umba::iterator::makeString(b, e);
}

template<typename StreamType, typename InputIteratorType>
StreamType& printTokenImpl(StreamType &ss, umba::tokenizer::payload_type tokenType, InputIteratorType b, InputIteratorType e)
{
    auto kindStr   = getTokenKindString<std::string>(tokenType);
    auto tokenText = makeTokenText(tokenType, b, e);

    ss << tokenText;

    if (!kindStr.empty())
    {
        ss << " - " << kindStr;
    }

    return ss;
}

template<typename StreamType, typename InputIteratorType>
StreamType& printToken(StreamType &ss, umba::tokenizer::payload_type tokenType, InputIteratorType b, InputIteratorType e)
{
    return printTokenImpl(ss, tokenType, b, e) << "\n";
}

template<typename StreamType, typename InputIteratorType>
StreamType& printToken(StreamType &ss, umba::tokenizer::payload_type tokenType, InputIteratorType b, InputIteratorType e, bool lineStart)
{
    printTokenImpl(ss, tokenType, b, e);
    if (tokenType==UMBA_TOKENIZER_TOKEN_OPERATOR_MULTI_LINE_COMMENT)
    {
        ss << " - lineStart: " << (lineStart?"true":"false");
    }

    ss << "\n";

    return ss;
}

template<typename StreamType, typename MsgType>
void printError(StreamType &ss, const std::string &inputFilename, umba::tokenizer::payload_type tokenType, umba::iterator::TextPositionCountingIterator<char> it, umba::iterator::TextPositionCountingIterator<char> itEnd, MsgType msg)
{
     UMBA_USED(tokenType);

     ss << "!!! ";

     if (it==itEnd)
     {
         ss << inputFilename << ": Unexpected end of file\n";
         ss << "TokenType: " << tokenType << "\n";
         return;
     }

     if (msg.empty())
     {
         msg = "Unexpected symbol";
     }

     auto errPos = it.getPosition(true); // с поиском конца строки (а вообще не надо пока, но пусть)
     std::string erroneousLineText = umba::iterator::makeString(it.getLineStartIterator(), it.getLineEndIterator());
     ss << inputFilename << ":" << errPos.toString<std::string>() << ": " << msg << "\n";
     ss << "Line: " << erroneousLineText << "\n";
     auto errMarkerStr = std::string(erroneousLineText.size(), ' ');
     if (errPos.symbolOffset>=errMarkerStr.size())
         errMarkerStr.append(1,'^');
     else
         errMarkerStr[errPos.symbolOffset] = '^';
     ss << "     |" << errMarkerStr << "|\n";

     if (it!=itEnd)
     {
         // char ch = *it;
         // ss << "ch: " << umba::escapeStringC(std::string(1,ch)) << "\n";
     }
}

template<typename StreamType>
void printError(StreamType &ss, const std::string &inputFilename, umba::tokenizer::payload_type tokenType, umba::iterator::TextPositionCountingIterator<char> it, umba::iterator::TextPositionCountingIterator<char> itEnd)
{
    printError(ss, inputFilename, tokenType, it, itEnd, std::string());
}

template<typename StreamType, typename MsgType>
void printError(StreamType &ss, const std::string &inputFilename, umba::tokenizer::payload_type tokenType, umba::iterator::TextPositionCountingIterator<char> it, umba::iterator::TextPositionCountingIterator<char> itEnd, const char* srcFile, int srcLine, const MsgType &msg)
{
    printError(ss, inputFilename, tokenType, it, itEnd, msg);
    ss << "At " << srcFile << ":" << srcLine << "\n";
}

template<typename StreamType>
void printError(StreamType &ss, const std::string &inputFilename, umba::tokenizer::payload_type tokenType, umba::iterator::TextPositionCountingIterator<char> it, umba::iterator::TextPositionCountingIterator<char> itEnd, const char* srcFile, int srcLine)
{
    printError(ss, inputFilename, tokenType, it, itEnd);
    ss << "At " << srcFile << ":" << srcLine << "\n";
}


