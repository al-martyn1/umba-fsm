/*! \file
    \brief Делаем для теста раскраску плюсового кода в HTML - обработка препроцессора вынесена в библиотечный класс CcPreprocessorFilter. Устаревший тест, может работать некорректно
 */

#include "umba/umba.h"
//
#include "umba/tokenizer.h"
#include "umba/assert.h"
#include "umba/filename.h"
#include "umba/filesys.h"
#include "umba/tokenizer/token_filters.h"
#include "umba/app_main.h"
//
#include "umba/debug_helpers.h"

//
#include "umba/text_position_info.h"
#include "umba/iterator.h"
#include "umba/the.h"
//
#include "utils.h"
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



#define USE_SIMPLE_NUMBER_SUFFIX_GLUING_FILTER
// #define NUMBER_PRINTING_PRINT_PARSED_VALUE
// #define PRINT_ONLY_NUMBERS
#define USE_TRY_CATCH

// #define DUPLICATE_TO_STD_OUT



using std::cout;
using std::cerr;


#include "css_style.h"




std::string inputFilename;





UMBA_MAIN()
{
    // auto t1 = getCharClassTable();
    // auto t2 = getTrieVector();
    // auto t3 = getString();
    // auto t4 = getIterator();

    using namespace umba::tokenizer;

    std::vector<std::string>  inputFiles;

    for(int argIdx=1; argIdx<argc; ++argIdx)
    {
        if (false)
        {
        }
        else
        {
            inputFiles.emplace_back(argv[argIdx]);
        }
    }

    if (umba::isDebuggerPresent() || inputFiles.empty())
    {
        std::string cwd = umba::filesys::getCurrentDirectory();
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

        inputFiles.clear();

        inputFiles.emplace_back(umba::filename::appendPath(rootPath, std::string("_libs/umba/preprocessor.h")));
        // inputFiles.emplace_back(umba::filename::appendPath(rootPath, std::string("_libs/umba/the.h")));
        // inputFiles.emplace_back(umba::filename::appendPath(rootPath, std::string("_libs/umba/stl_keil_initializer_list.h")));
        // inputFiles.emplace_back(umba::filename::appendPath(rootPath, std::string("_libs/umba/stl_keil_type_traits.h")));
        // inputFiles.emplace_back(umba::filename::appendPath(rootPath, std::string("_libs/umba/string_plus.h")));
        // inputFiles.emplace_back(umba::filename::appendPath(rootPath, std::string("_libs/umba/rgbquad.h")));

        // inputFiles.emplace_back(umba::filename::appendPath(rootPath, std::string("_libs/umba/")));

        // inputFiles.emplace_back(umba::filename::appendPath(rootPath, std::string("_libs/marty_decimal/tests/src/regression_tests.cpp")));

        //inputFiles.emplace_back(umba::filename::appendPath(rootPath, std::string("tests/tokenizer/number_ull.cpp")));

    }




    payload_type numberTokenId = UMBA_TOKENIZER_TOKEN_NUMBER_USER_LITERAL_FIRST;

    umba::tokenizer::CppEscapedSimpleQuotedStringLiteralParser<char>  cppEscapedSimpleQuotedStringLiteralParser;
    umba::tokenizer::SimpleQuotedStringLiteralParser<char>            simpleQuotedStringLiteralParser;


    auto tokenizer = TokenizerBuilder<char>().generateStandardCharClassTable()

                                             .addNumbersPrefix("0b", numberTokenId++ | UMBA_TOKENIZER_TOKEN_NUMBER_LITERAL_BASE_BIN)
                                             .addNumbersPrefix("0B", numberTokenId++ | UMBA_TOKENIZER_TOKEN_NUMBER_LITERAL_BASE_BIN)

                                             .addNumbersPrefix("0d", numberTokenId++ | UMBA_TOKENIZER_TOKEN_NUMBER_LITERAL_BASE_DEC)
                                             .addNumbersPrefix("0D", numberTokenId++ | UMBA_TOKENIZER_TOKEN_NUMBER_LITERAL_BASE_DEC)

                                             .addNumbersPrefix("4x", numberTokenId++ | UMBA_TOKENIZER_TOKEN_NUMBER_LITERAL_BASE_QUAT)
                                             .addNumbersPrefix("4X", numberTokenId++ | UMBA_TOKENIZER_TOKEN_NUMBER_LITERAL_BASE_QUAT)

                                             .addNumbersPrefix("0" , numberTokenId++ | UMBA_TOKENIZER_TOKEN_NUMBER_LITERAL_BASE_OCT | UMBA_TOKENIZER_TOKEN_NUMBER_LITERAL_FLAG_MISS_DIGIT)

                                             .addNumbersPrefix("12x", numberTokenId++ | UMBA_TOKENIZER_TOKEN_NUMBER_LITERAL_BASE_DUOD)
                                             .addNumbersPrefix("12X", numberTokenId++ | UMBA_TOKENIZER_TOKEN_NUMBER_LITERAL_BASE_DUOD)

                                             .addNumbersPrefix("0x", numberTokenId++ | UMBA_TOKENIZER_TOKEN_NUMBER_LITERAL_BASE_HEX)
                                             .addNumbersPrefix("0X", numberTokenId++ | UMBA_TOKENIZER_TOKEN_NUMBER_LITERAL_BASE_HEX)


                                             .addBrackets("{}", UMBA_TOKENIZER_TOKEN_CURLY_BRACKETS )
                                             .addBrackets("()", UMBA_TOKENIZER_TOKEN_ROUND_BRACKETS )
                                             .addBrackets("<>", UMBA_TOKENIZER_TOKEN_ANGLE_BRACKETS )
                                             .addBrackets("[]", UMBA_TOKENIZER_TOKEN_SQUARE_BRACKETS)


                                             .addSingleLineComment("//", UMBA_TOKENIZER_TOKEN_OPERATOR_SINGLE_LINE_COMMENT_FIRST)
                                             .setMultiLineComment("/*", "*/")


                                             // Операторы # и ## доступны только внутри директивы define препроцессора.
                                             // Для этого вначале работы мы сбрасываем признак umba::tokenizer::CharClass::opchar,
                                             // при получении маркера директивы define - устанавливаем его,
                                             // и при окончании блока препроцессора опять сбрасываем
                                             .addOperators(UMBA_TOKENIZER_TOKEN_OPERATOR_FIRST_GENERIC, std::vector<std::string>{".","#","##","...",".*","+","-","*","/","%","^","&","|","~","!","=","<",">","+=","-=","*=","/=","%=","^=","&=","|=","<<",">>",">>=","<<=","==","!=","<=",">=","<=>","&&","||","++","--",",","->*","->",":","::",";","?"})


                                             .addStringLiteralParser("\'", &cppEscapedSimpleQuotedStringLiteralParser)
                                             .addStringLiteralParser("\"", &cppEscapedSimpleQuotedStringLiteralParser)
                                             .addStringLiteralParser("<" , &simpleQuotedStringLiteralParser)


                                             .makeTokenizer();


    // Пока с kind не определился, и пихаем в keywords всё
    std::unordered_map<std::string, int> cppKeywords;
    std::unordered_map<std::string, int> cppPreprocessorKeywords;
    {
        // https://en.cppreference.com/w/cpp/keyword
        std::vector<std::string> allCppKeywords = { "alignas", "alignof", "and", "and_eq", "asm", "atomic_cancel", "atomic_commit", "atomic_noexcept", "auto"
                                                  , "bitand", "bitor", "bool", "break"
                                                  , "case", "catch", "char", "char8_t", "char16_t", "char32_t", "class", "compl", "concept", "const", "consteval"
                                                  , "constexpr", "constinit", "const_cast", "continue", "co_await", "co_return", "co_yield"
                                                  , "decltype", "default", "delete", "do", "double", "dynamic_cast"
                                                  , "else", "enum", "explicit", "export", "extern"
                                                  , "false", "float", "for", "friend"
                                                  , "goto"
                                                  , "if", "inline", "int"
                                                  , "long", "mutable"
                                                  , "namespace", "new", "noexcept", "not", "not_eq", "nullptr"
                                                  , "operator", "or", "or_eq", "private", "protected", "public"
                                                  , "reflexpr", "register", "reinterpret_cast", "requires", "return"
                                                  , "short", "signed", "sizeof", "static", "static_assert", "static_cast", "struct", "switch", "synchronized"
                                                  , "template", "this", "thread_local", "throw", "true", "try", "typedef", "typeid", "typename"
                                                  , "union", "unsigned", "using", "virtual", "void", "volatile"
                                                  , "wchar_t", "while", "xor", "xor_eq"
                                                  // identifiers with special meaning
                                                  , "final", "override", "transaction_safe", "transaction_safe_dynamic", "import", "module"
                                                  };
        for(const auto &kw : allCppKeywords)
        {
            cppKeywords[kw] = 0;
        }
    }

    {
        std::vector<std::string> keywords = { "if", "elif", "else", "endif", "ifdef", "ifndef", "elifdef", "elifndef", "define", "undef", "include", "line"
                                            , "error", "warning", "pragma", "defined", "__has_include", "__has_cpp_attribute", "export", "import", "module"
                                            };

        for(const auto &kw : keywords)
        {
            cppPreprocessorKeywords[kw] = 0;
        }

        cppPreprocessorKeywords["define"] = 1;

    }




    std::ostringstream oss;
    bool bOk = true;

    //using tokenizer_type        = std::decay<decltype(tokenizer)>;
    using tokenizer_type         = decltype(tokenizer);
    using InputIteratorType      = typename tokenizer_type::iterator_type;
    using tokenizer_char_type    = typename tokenizer_type::value_type;
    using messages_string_type   = typename tokenizer_type::messages_string_type;
    using token_parsed_data_type = typename tokenizer_type::token_parsed_data_type;


    // enum State
    // {
    //     stNormal,
    //     stWaitPreprocessorKeyword,
    //     stReadPreprocessor,
    //     stReadDefine
    // };

    std::vector<TokenInfo> bufferedTokens;


    auto flushBufferedTokens = [&]()
    {
        for(const auto &ti : bufferedTokens)
        {
            printTokenHtml(oss, ti);
        }

        bufferedTokens.clear();
    };

    bool inPreprocessor = false;

    tokenizer.setResetCharClassFlags('#', umba::tokenizer::CharClass::none, umba::tokenizer::CharClass::opchar); // Ничего не устанавливаем, сбрасываем opchar
    tokenizer.setResetCharClassFlags('<', umba::tokenizer::CharClass::none, umba::tokenizer::CharClass::string_literal_prefix); // По дефолту символ '<' не является маркером строкового литерала
    bool isStartAngleBracketIsOperator = (tokenizer.getCharClass('<') & umba::tokenizer::CharClass::opchar) != 0;
    bool isEndAngleBracketIsOperator   = (tokenizer.getCharClass('>') & umba::tokenizer::CharClass::opchar) != 0;

    // Как в HTML делать раскрывающиеся фрагменты
    // https://htmlacademy.ru/blog/html-tags/sup
    // <details>
    //   <summary>Заголовок</summary>
    //   Здесь располагается скрытый контент, который будет отображен после клика по заголовку.
    // </details>

    tokenizer.tokenHandler = [&]( auto &tokenizer
                                , bool bLineStart, payload_type tokenType
                                , InputIteratorType b, InputIteratorType e
                                , token_parsed_data_type parsedData // std::basic_string_view<tokenizer_char_type> parsedData
                                , messages_string_type &errMsg
                                ) -> bool
                             {
                                 UMBA_USED(parsedData);

                                 if (tokenType==UMBA_TOKENIZER_TOKEN_CTRL_RST || tokenType==UMBA_TOKENIZER_TOKEN_CTRL_FIN)
                                     return true;

                                 else if (tokenType==UMBA_TOKENIZER_TOKEN_CTRL_CC_PP_START)
                                 {
                                     oss << "<span class=\"pp\">";
#if defined(DUPLICATE_TO_STD_OUT)
                                     std::cout << "<span class=\"pp\">";
#endif

                                     inPreprocessor = true;
                                     return true;
                                 }
                                 else if (tokenType==UMBA_TOKENIZER_TOKEN_CTRL_CC_PP_END)
                                 {
                                     oss << "</span>";
#if defined(DUPLICATE_TO_STD_OUT)
                                     std::cout << "</span>";
#endif

                                     tokenizer.setResetCharClassFlags('#', umba::tokenizer::CharClass::none, umba::tokenizer::CharClass::opchar); // Ничего не устанавливаем, сбрасываем opchar

                                     if (isStartAngleBracketIsOperator)
                                     {
                                         tokenizer.setResetCharClassFlags('<', umba::tokenizer::CharClass::opchar, umba::tokenizer::CharClass::none); // Устанавливаем признак оператора обратно
                                     }
                                     if (isEndAngleBracketIsOperator)
                                     {
                                         tokenizer.setResetCharClassFlags('>', umba::tokenizer::CharClass::opchar, umba::tokenizer::CharClass::none); // Устанавливаем признак оператора обратно
                                     }

                                     tokenizer.setResetCharClassFlags('<', umba::tokenizer::CharClass::none, umba::tokenizer::CharClass::string_literal_prefix); // Ничего не устанавливаем, сбрасываем string_literal_prefix
                                     tokenizer.setResetCharClassFlags('>', umba::tokenizer::CharClass::none, umba::tokenizer::CharClass::string_literal_prefix); // Ничего не устанавливаем, сбрасываем string_literal_prefix

                                     inPreprocessor = false;
                                     return true;
                                 }
                                 else if (tokenType==UMBA_TOKENIZER_TOKEN_CTRL_CC_PP_DEFINE)
                                 {
                                     tokenizer.setResetCharClassFlags('#', umba::tokenizer::CharClass::opchar, umba::tokenizer::CharClass::none); // устанавливаем opchar, ничего не сбрасываем
                                     // inDefine = false;
                                     return true;
                                 }
                                 else if (tokenType==UMBA_TOKENIZER_TOKEN_CTRL_CC_PP_INCLUDE)
                                 {
                                     tokenizer.setResetCharClassFlags('<', umba::tokenizer::CharClass::string_literal_prefix, umba::tokenizer::CharClass::opchar); // устанавливаем string_literal_prefix, сбрасываем opchar
                                     // inDefine = false;
                                     return true;
                                 }


                                 if (tokenType==UMBA_TOKENIZER_TOKEN_IDENTIFIER)
                                 {
                                     auto identStr = umba::iterator::makeString(b, e);

                                     if (!inPreprocessor)
                                     {
                                         if (cppKeywords.find(identStr)!=cppKeywords.end())
                                             tokenType = UMBA_TOKENIZER_TOKEN_KEYWORD_SET1_FIRST;
                                         else if (cppPreprocessorKeywords.find(identStr)!=cppPreprocessorKeywords.end())
                                             tokenType = UMBA_TOKENIZER_TOKEN_KEYWORD_SET2_FIRST;
                                     }
                                     else // preprocessor
                                     {
                                         if (cppPreprocessorKeywords.find(identStr)!=cppPreprocessorKeywords.end())
                                             tokenType = UMBA_TOKENIZER_TOKEN_KEYWORD_SET2_FIRST;
                                         else if (cppKeywords.find(identStr)!=cppKeywords.end())
                                             tokenType = UMBA_TOKENIZER_TOKEN_KEYWORD_SET1_FIRST;
                                     }
                                 }

                                 printTokenHtml(oss, tokenType, b, e);

                                 if (tokenType>=UMBA_TOKENIZER_TOKEN_NUMBER_LITERAL_FIRST && tokenType<=UMBA_TOKENIZER_TOKEN_NUMBER_LITERAL_LAST)
                                 {
                                     oss.flush();

                                     // https://en.cppreference.com/w/cpp/utility/variant/get_if
                                     // https://en.cppreference.com/w/cpp/utility/variant/get
                                     if (tokenType&UMBA_TOKENIZER_TOKEN_FLOAT_FLAG)
                                     {
                                         auto numericLiteralData = std::get<typename tokenizer_type::FloatNumericLiteralData>(parsedData);
                                         #if defined(NUMBER_PRINTING_PRINT_PARSED_VALUE)
                                         oss << " " << numericLiteralData.data << " ";
                                         if (numericLiteralData.fIntegerOverflow)
                                             oss << "integer part overflow ";
                                         if (numericLiteralData.fFractionalOverflow)
                                             oss << "floating part overflow ";
                                         #endif
                                     }
                                     else
                                     {
                                         auto numericLiteralData = std::get<typename tokenizer_type::IntegerNumericLiteralData>(parsedData);
                                         #if defined(NUMBER_PRINTING_PRINT_PARSED_VALUE)
                                         oss << " " << numericLiteralData.data << " ";
                                         if (numericLiteralData.fOverflow)
                                             oss << "overflow ";
                                         #endif
                                     }
                                 }

                                 return true;
                             };

    tokenizer.unexpectedHandler = [&](auto &tokenizer, InputIteratorType it, InputIteratorType itEnd, const char* srcFile, int srcLine) -> bool
                             {
                                 printError(std::cout, inputFilename, UMBA_TOKENIZER_TOKEN_UNEXPECTED, it, itEnd, srcFile, srcLine);
                                 return false;
                             };

    tokenizer.reportUnknownOperatorHandler = [&](auto &tokenizer, InputIteratorType b, InputIteratorType e)
                             {
                                 //cout << "Possible unknown operator: '" << umba::iterator::makeString(b, e) << "'\n";
                                 UMBA_USED(b); UMBA_USED(e);
                             };

    tokenizer.reportStringLiteralMessageHandler = [&](auto &tokenizer, bool bErr, InputIteratorType it, const messages_string_type &msg)
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

    //
    // auto reportPossibleUnknownOperatorLambda = [&](const PosCountingIterator b, const PosCountingIterator &e)
    // {
    //     cout << "Possible unknown operator: '" << makeString(b, e) << "'\n";
    // };
    //
    // auto reportStringLiteralMessageLambda = [&](bool bErr, const PosCountingIterator it, const std::string msg)
    // {
    //     auto errPos = it.getPosition(true); // с поиском конца строки (а вообще не надо пока, но пусть)
    //     std::string erroneousLineText = umba::iterator::makeString(it.getLineStartIterator(), it.getLineEndIterator());
    //     cout << (bErr ? "Error: " : "Warning: ") << msg << " at " << inputFilename << ":" << umba::makeSimpleTextPositionInfoString<std::string>(errPos) << "\n";
    //     cout << "Line:" << erroneousLineText << "\n";
    //     auto errMarkerStr = std::string(erroneousLineText.size(), ' ');
    //     if (errPos.symbolOffset>=errMarkerStr.size())
    //         errMarkerStr.append(1,'^');
    //     else
    //         errMarkerStr[errPos.symbolOffset] = '^';
    //     cout << "    |" << errMarkerStr << "|\n";
    // };


    // Фильтры, установленные позже, отрабатывают раньше

    #if defined(USE_SIMPLE_NUMBER_SUFFIX_GLUING_FILTER)
    tokenizer.installTokenFilter<umba::tokenizer::filters::SimpleSuffixGluingFilter<tokenizer_type> >();
    #endif

    tokenizer.installTokenFilter<umba::tokenizer::filters::CcPreprocessorFilter<tokenizer_type> >();



    if (inputFiles.empty())
    {
        std::cout << "No input files taken\n";
        return 1;
    }

    #if defined(WIN32) || defined(_WIN32)
        marty_cpp::ELinefeedType outputLinefeed = marty_cpp::ELinefeedType::crlf;
    #else
        marty_cpp::ELinefeedType outputLinefeed = marty_cpp::ELinefeedType::lf;
    #endif


    for(const auto fn: inputFiles)
    {
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

        oss<<"<!DOCTYPE html>\n<html>\n<head>\n<meta charset=\"utf-8\"/>\n<style>\n" << cssStyle << "\n</style>\n</head>\n<body>\n<pre>\n";

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
                oss<<"</pre>\n</body>\n</html>\n";

                if (inputFilename.empty())
                {
                    std::cout << oss.str() << "\n";
                }
                else
                {
                    auto resultText = marty_cpp::converLfToOutputFormat(oss.str(), outputLinefeed);
                    auto outputFilename = umba::filename::replaceExtention(inputFilename, std::string("html"));
                    std::cout << "Writting output to '" << outputFilename << "' - ";
                    if (!umba::filesys::writeFile(outputFilename, resultText, true /* overwrite */ ))
                        std::cout << "Failed";
                    else
                        std::cout << "Success";
                    std::cout << "\n";
                }

            }

#if defined(USE_TRY_CATCH)
        }
        catch(const std::exception &e)
        {

            std::cout << oss.str() << "\n";

            auto resultText = marty_cpp::converLfToOutputFormat("!!!"  + oss.str(), outputLinefeed);
            auto outputFilename = umba::filename::replaceExtention(inputFilename, std::string("html"));
            //std::cout << "Writting output to '" << outputFilename << "' - ";
            umba::filesys::writeFile(outputFilename, resultText, true /* overwrite */ );
            // if (!umba::filesys::writeFile(outputFilename, resultText, true /* overwrite */ ))
            //     std::cout << "Failed";
            // else
            //     std::cout << "Success";
            // std::cout << "\n";

            std::cout << "!!!\n";
        }
#endif

    }


    // cout << "Input file: " << inputFilename << "\n";
    // std::cout << "---\n";



    //tikenizeInit()


    return bOk ? 0 : 1;

}


