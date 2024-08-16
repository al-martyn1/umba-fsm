/*! \file
    \brief Начинаем разбор TBNF
 */

#include "umba/umba.h"
//
#include "umba/tokenizer.h"
#include "umba/assert.h"
#include "umba/filename.h"
#include "umba/filesys.h"
#include "umba/tokenizer/token_filters.h"
//
#include "umba/debug_helpers.h"

//
#include "umba/text_position_info.h"
#include "umba/iterator.h"
#include "umba/the.h"
//

#include "marty_cpp/src_normalization.h"
//

#include <iostream>
#include <map>
#include <set>
#include <unordered_set>
#include <unordered_map>
#include <deque>
#include <sstream>





using std::cout;
using std::cerr;



template<typename StringType>
StringType getTokenKindString(umba::tokenizer::payload_type p)
{
    switch(p)
    {
        case UMBA_TOKENIZER_TOKEN_UNEXPECTED                       : return umba::string_plus::make_string<StringType>("unxp");
        case UMBA_TOKENIZER_TOKEN_LINEFEED                         : return umba::string_plus::make_string<StringType>("");
        case UMBA_TOKENIZER_TOKEN_SPACE                            : return umba::string_plus::make_string<StringType>("");
        case UMBA_TOKENIZER_TOKEN_TAB                              : return umba::string_plus::make_string<StringType>("");
        case UMBA_TOKENIZER_TOKEN_IDENTIFIER                       : return umba::string_plus::make_string<StringType>("ident");
        case UMBA_TOKENIZER_TOKEN_SEMIALPHA                        : return umba::string_plus::make_string<StringType>("");
        // https://en.wikipedia.org/wiki/Bracket
        case UMBA_TOKENIZER_TOKEN_CURLY_BRACKET_OPEN               : return umba::string_plus::make_string<StringType>("curly");
        case UMBA_TOKENIZER_TOKEN_CURLY_BRACKET_CLOSE              : return umba::string_plus::make_string<StringType>("curly");
        case UMBA_TOKENIZER_TOKEN_ROUND_BRACKET_OPEN               : return umba::string_plus::make_string<StringType>("round");
        case UMBA_TOKENIZER_TOKEN_ROUND_BRACKET_CLOSE              : return umba::string_plus::make_string<StringType>("round");
        case UMBA_TOKENIZER_TOKEN_ANGLE_BRACKET_OPEN               : return umba::string_plus::make_string<StringType>("angle");
        case UMBA_TOKENIZER_TOKEN_ANGLE_BRACKET_CLOSE              : return umba::string_plus::make_string<StringType>("angle");
        case UMBA_TOKENIZER_TOKEN_SQUARE_BRACKET_OPEN              : return umba::string_plus::make_string<StringType>("square");
        case UMBA_TOKENIZER_TOKEN_SQUARE_BRACKET_CLOSE             : return umba::string_plus::make_string<StringType>("square");
        case UMBA_TOKENIZER_TOKEN_OPERATOR_MULTI_LINE_COMMENT_START: return umba::string_plus::make_string<StringType>("cmnt");
        case UMBA_TOKENIZER_TOKEN_OPERATOR_MULTI_LINE_COMMENT_END  : return umba::string_plus::make_string<StringType>("cmnt");
        case UMBA_TOKENIZER_TOKEN_PP_START                         : return umba::string_plus::make_string<StringType>("pp");
        case UMBA_TOKENIZER_TOKEN_PP_END                           : return umba::string_plus::make_string<StringType>("pp");

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


template<typename StreamType, typename InputIteratorType>
StreamType& printToken(StreamType &ss, umba::tokenizer::payload_type tokenType, InputIteratorType b, InputIteratorType e)
{
    auto kindStr   = getTokenKindString<std::string>(tokenType);
    auto tokenText = makeTokenText(tokenType, b, e);

    ss << tokenText;

    if (!kindStr.empty())
    {
        ss << " - " << kindStr << "\n";
    }

    return ss;
}


std::string inputFilename;




void printError(umba::tokenizer::payload_type tokenType, umba::iterator::TextPositionCountingIterator<char> it, umba::iterator::TextPositionCountingIterator<char> itEnd)
{
     UMBA_USED(tokenType);

     if (it==itEnd)
     {
         cout << "Unexpected end of file\n";
         return;
     }

     auto errPos = it.getPosition(true); // с поиском конца строки (а вообще не надо пока, но пусть)
     std::string erroneousLineText = umba::iterator::makeString(it.getLineStartIterator(), it.getLineEndIterator());
     cout << "Unexpected at " << inputFilename << ":" << errPos.toString<std::string>() << "\n";
     cout << "Line:" << erroneousLineText << "\n";
     auto errMarkerStr = std::string(erroneousLineText.size(), ' ');
     if (errPos.symbolOffset>=errMarkerStr.size())
         errMarkerStr.append(1,'^');
     else
         errMarkerStr[errPos.symbolOffset] = '^';
     cout << "    |" << errMarkerStr << "|\n";

     if (it!=itEnd)
     {
         char ch = *it;
         cout << "ch: " << umba::escapeStringC(std::string(1,ch)) << "\n";
     }
}

void printError(umba::tokenizer::payload_type tokenType, umba::iterator::TextPositionCountingIterator<char> it, umba::iterator::TextPositionCountingIterator<char> itEnd, const char* srcFile, int srcLine)
{
    printError(tokenType, it, itEnd);
     cout << "At " << srcFile << ":" << srcLine << "\n";
}








int main(int argc, char* argv[])
{

    using namespace umba::tokenizer;

    if (argc>1)
    {
        inputFile = argv[1];
    }

    if (umba::isDebuggerPresent() || inputFiles.empty())
    {
        std::string cwd = umba::filesys::getCurrentDirectory<std::string>();
        std::cout << "Working Dir: " << cwd << "\n";
        std::string rootPath;

        #if (defined(WIN32) || defined(_WIN32))


            if (winhelpers::isProcessHasParentOneOf({"devenv"}))
            {
                // По умолчанию студия задаёт текущим каталогом На  уровень выше от того, где лежит бинарник
                rootPath = umba::filename::makeCanonical(umba::filename::appendPath<std::string>(cwd, "..\\..\\..\\"));
                //argsParser.args.push_back("--batch-output-root=D:/temp/mdpp-test");
            }
            else if (winhelpers::isProcessHasParentOneOf({"code"}))
            {
                // По умолчанию VSCode задаёт текущим каталогом тот, где лежит бинарник
                rootPath = umba::filename::makeCanonical(umba::filename::appendPath<std::string>(cwd, "..\\..\\..\\..\\"));
                //argsParser.args.push_back("--batch-output-root=C:/work/temp/mdpp-test");

            }
            else
            {
                //rootPath = umba::filename::makeCanonical(umba::filename::appendPath<std::string>(cwd, "..\\..\\..\\"));
            }

            //#endif

            if (!rootPath.empty())
                rootPath = umba::filename::appendPathSepCopy(rootPath);

        #endif


        inputFile = "_libs/umba/preprocessor.h";
    }

    if (inputFile.empty())
    {
        std::cerr << "Not input file taken\n";
        return 1;
    }


    payload_type numberTokenId = UMBA_TOKENIZER_TOKEN_NUMBER_USER_LITERAL_FIRST;

    umba::tokenizer::CppEscapedSimpleQuotedStringLiteralParser<char>  cppEscapedSimpleQuotedStringLiteralParser;
    umba::tokenizer::SimpleQuotedStringLiteralParser<char>            simpleQuotedStringLiteralParser;


    auto tokenizer = TokenizerBuilder<char>().generateStandardCharClassTable()

                                             // Числа с плавающей точкой отличаются только флагом UMBA_TOKENIZER_TOKEN_FLOAT_FLAG
                                             .addNumbersPrefix("0b", UMBA_TOKENIZER_TOKEN_INTEGRAL_NUMBER_BIN)
                                             .addNumbersPrefix("0B", UMBA_TOKENIZER_TOKEN_INTEGRAL_NUMBER_BIN)

                                             .addNumbersPrefix("0d", UMBA_TOKENIZER_TOKEN_INTEGRAL_NUMBER_DEC)
                                             .addNumbersPrefix("0D", UMBA_TOKENIZER_TOKEN_INTEGRAL_NUMBER_DEC)

                                             .addNumbersPrefix("0" , UMBA_TOKENIZER_TOKEN_INTEGRAL_NUMBER_OCT | UMBA_TOKENIZER_TOKEN_NUMBER_LITERAL_FLAG_MISS_DIGIT)

                                             .addNumbersPrefix("0x", UMBA_TOKENIZER_TOKEN_INTEGRAL_NUMBER_HEX)
                                             .addNumbersPrefix("0X", UMBA_TOKENIZER_TOKEN_INTEGRAL_NUMBER_HEX)


                                             .addBrackets("{}", UMBA_TOKENIZER_TOKEN_CURLY_BRACKETS )
                                             .addBrackets("()", UMBA_TOKENIZER_TOKEN_ROUND_BRACKETS )
                                             //.addBrackets("<>", UMBA_TOKENIZER_TOKEN_ANGLE_BRACKETS )
                                             .addBrackets("[]", UMBA_TOKENIZER_TOKEN_SQUARE_BRACKETS)


                                             .addSingleLineComment("//", UMBA_TOKENIZER_TOKEN_OPERATOR_SINGLE_LINE_COMMENT_FIRST)
                                             .addSingleLineComment("//", UMBA_TOKENIZER_TOKEN_OPERATOR_SINGLE_LINE_COMMENT_FIRST)
                                             .setMultiLineComment("/*", "*/")


                                             .addOperator("*", UMBA_TOKENIZER_TOKEN_OPERATOR_ANY_NUM_REPETITIONS) // * - от нуля повторений до бесконечности
                                             .addOperator("+", UMBA_TOKENIZER_TOKEN_OPERATOR_ONE_MORE_REPETITION) // + - от одного повторения до бесконечности
                                             .addOperator("?", UMBA_TOKENIZER_TOKEN_OPERATOR_ZERO_OR_ONE)         // ? - ноль или одно
                                             .addOperator(":", UMBA_TOKENIZER_TOKEN_OPERATOR_COLON)
                                             .addOperator("@", UMBA_TOKENIZER_TOKEN_OPERATOR_AT)
                                             

                                             .addStringLiteralParser("\'", &cppEscapedSimpleQuotedStringLiteralParser, UMBA_TOKENIZER_TOKEN_CHAR_LITERAL)
                                             .addStringLiteralParser("\"", &cppEscapedSimpleQuotedStringLiteralParser, UMBA_TOKENIZER_TOKEN_STRING_LITERAL)


                                             .makeTokenizer();


    std::ostringstream oss;
    bool bOk = true;

    //using tokenizer_type      = std::decay<decltype(tokenizer)>;
    using tokenizer_type       = decltype(tokenizer);
    using InputIteratorType    = typename tokenizer_type::iterator_type;
    using tokenizer_char_type  = typename tokenizer_type::value_type;
    using messages_string_type = typename tokenizer_type::messages_string_type;
    using token_parsed_data    = typename tokenizer_type::token_parsed_data;


    // tokenizer.setResetCharClassFlags('#', umba::tokenizer::CharClass::none, umba::tokenizer::CharClass::opchar); // Ничего не устанавливаем, сбрасываем opchar
    // tokenizer.setResetCharClassFlags('<', umba::tokenizer::CharClass::none, umba::tokenizer::CharClass::string_literal_prefix); // По дефолту символ '<' не является маркером строкового литерала
    // bool isStartAngleBracketIsOperator = (tokenizer.getCharClass('<') & umba::tokenizer::CharClass::opchar) != 0;
    // bool isEndAngleBracketIsOperator   = (tokenizer.getCharClass('>') & umba::tokenizer::CharClass::opchar) != 0;


    tokenizer.tokenHandler = [&]( tokenizer_type &tokenizer
                                , bool bLineStart, payload_type tokenType
                                , InputIteratorType b, InputIteratorType e
                                , token_parsed_data parsedData // std::basic_string_view<tokenizer_char_type> parsedData
                                , messages_string_type &errMsg
                                ) -> bool
                             {
                                 UMBA_USED(tokenizer);
                                 UMBA_USED(bLineStart);
                                 UMBA_USED(tokenType);
                                 UMBA_USED(b);
                                 UMBA_USED(e);
                                 UMBA_USED(parsedData);
                                 UMBA_USED(errMsg);

                                 //getTokenKindString(umba::tokenizer::payload_type p)
                                 // printToken(oss, tokenType, b, e);
                                 printToken(std::cout, tokenType, b, e);

                                 return true;
                             };

    tokenizer.unexpectedHandler = [&](tokenizer_type &tokenizer, InputIteratorType it, InputIteratorType itEnd, const char* srcFile, int srcLine) -> bool
                             {
                                 printError(UMBA_TOKENIZER_TOKEN_UNEXPECTED, it, itEnd, srcFile, srcLine);
                                 return false;
                             };

    tokenizer.reportUnknownOperatorHandler = [&](tokenizer_type &tokenizer, InputIteratorType b, InputIteratorType e)
                             {
                                 //cout << "Possible unknown operator: '" << umba::iterator::makeString(b, e) << "'\n";
                                 UMBA_USED(b); UMBA_USED(e);
                             };

    tokenizer.reportStringLiteralMessageHandler = [&](tokenizer_type &tokenizer, bool bErr, InputIteratorType it, const messages_string_type &msg)
                             {
                                 #if 0
                                 auto errPos = it.getPosition(true); // с поиском конца строки (а вообще не надо пока, но пусть)
                                 std::string erroneousLineText = umba::iterator::makeString(it.getLineStartIterator(), it.getLineEndIterator());
                                 cout << (bErr ? "Error: " : "Warning: ") << msg << " at " << inputFilename << ":" << errPos.toString<std::string>() << "\n";
                                 cout << "Line:" << erroneousLineText << "\n";
                                 auto errMarkerStr = std::string(erroneousLineText.size(), ' ');
                                 if (errPos.symbolOffset>=errMarkerStr.size())
                                     errMarkerStr.append(1,'^');
                                 else
                                     errMarkerStr[errPos.symbolOffset] = '^';
                                 cout << "    |" << errMarkerStr << "|\n";
                                 #endif
                                 UMBA_USED(bErr); UMBA_USED(it); UMBA_USED(msg);
                             };


    // Фильтры, установленные позже, отрабатывают раньше

    #if defined(USE_SIMPLE_NUMBER_SUFFIX_GLUING_FILTER)
    tokenizer.installTokenFilter<umba::tokenizer::filters::SimpleSuffixGluingFilter<tokenizer_type> >();
    #endif



    #if defined(WIN32) || defined(_WIN32)
        marty_cpp::ELinefeedType outputLinefeed = marty_cpp::ELinefeedType::crlf;
    #else
        marty_cpp::ELinefeedType outputLinefeed = marty_cpp::ELinefeedType::lf;
    #endif


    inputFilename = fn;

    std::string text;

#if 0
    // text = "(1)";
    // text = "    //! Оператор сравнения на равенство\n    bool operator==( const RgbQuad rq ) const\n";
    // text = "DECIMAL_CTOR_TEST_WITH_PREC(  ((std::uint64_t)3141592654ULL), 9, \"3.141592654\" );";
    // text = "3141592654ULL), 9, \"3.141592654\" );";
    // text = "54ULL), 9, \"3.141592654\" );";
    text = "4ULL), 9, \"3.141592654\" );";
    // text = "";
    // text = "";
    // text = "";
    // text = "";
    inputFilename.clear();
#else
    if (!umba::filesys::readFile(inputFilename, text))
    {
        std::cout << "Failed to read input file '" << inputFilename << "'\n";
        continue;
    }
#endif
    if (text.empty())
    {
        std::cout << "Input file '" << inputFilename << "' empty\n";
        continue;
    }

    if (text.back()!='\n' && text.back()!='\r')
    {
        std::cout << "Warning: file '" << inputFilename << "': no linefeed at end of file\n";
    }

    oss = std::ostringstream();
    bOk = true;

#if defined(USE_TRY_CATCH)
    try
    {
#endif
        auto itBegin = InputIteratorType(text.data(), text.size());
        auto itEnd   = InputIteratorType();
        tokenizer.tokenizeInit();
        for( InputIteratorType it=itBegin; it!=itEnd && bOk; ++it)
        {
            if (!tokenizer.tokenize(it, itEnd))
            {
                bOk = false;
            }
        }

        if (bOk)
        {
            bOk = tokenizer.tokenizeFinalize(itEnd);
        }

        if (bOk)
        {
            // auto resultText = marty_cpp::converLfToOutputFormat(oss.str(), outputLinefeed);
            // auto outputFilename = umba::filename::replaceExtention(inputFilename, std::string("html"));
            // std::cout << "Writting output to '" << outputFilename << "' - ";
            // if (!umba::filesys::writeFile(outputFilename, resultText, true /* overwrite */ ))
            //     std::cout << "Failed";
            // else
            //     std::cout << "Success";
            // std::cout << "\n";
        }

#if defined(USE_TRY_CATCH)
    }
    catch(const std::exception &e)
    {

        // std::cout << oss.str() << "\n";
        //  
        // auto resultText = marty_cpp::converLfToOutputFormat("!!!"  + oss.str(), outputLinefeed);
        // auto outputFilename = umba::filename::replaceExtention(inputFilename, std::string("html"));
        // umba::filesys::writeFile(outputFilename, resultText, true /* overwrite */ );
        std::cout << "!!!\n";
    }
#endif


    return bOk ? 0 : 1;

}


