/*! \file
    \brief Делаем для теста раскраску плюсового кода в HTML - обработка препроцессора вынесена в библиотечный класс CcPreprocessorFilter
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
#include "umba/tokenizer/lang/cpp.h"
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



#define USE_SIMPLE_NUMBER_SUFFIX_GLUING_FILTER
// #define NUMBER_PRINTING_PRINT_PARSED_VALUE
// #define PRINT_ONLY_NUMBERS
// #define USE_TRY_CATCH

//#define DUPLICATE_TO_STD_OUT


#include "utils.h"
//






using std::cout;
using std::cerr;




/*
  color:blue
}

VSCode statements AF00DB
       keywords   0000FF
       known types 267F99
       brackets    319331
       comment     008000
       highlighted str 008000
       str         A31515

.m .com {
  color:green
}
.m .str {
  color:#8b0000
}
.m .lineQuote {
  color:#c1e5b9
}
.m .lineQuote.level1 {
  color:#137900
}
.m .lineQuote.level2 {
  color:#74b967
}
.m .lineQuote.level3 {
  color:#9fd095
}
.m .tagline {
  color:#d3acac;
  text-indent:5mm;
  padding-top:5mm
}
.m TABLE.formatter {
  margin:5px
}
.m TH.formatter {
  font-family:Verdana,Geneva,sans-serif;
  background-color:#d4d4d4;
  font-size:x-small
}

*/

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

        // inputFiles.emplace_back(umba::filename::appendPath(rootPath, std::string("_libs/umba/preprocessor.h")));
        // inputFiles.emplace_back(umba::filename::appendPath(rootPath, std::string("_libs/umba/the.h")));
        // inputFiles.emplace_back(umba::filename::appendPath(rootPath, std::string("_libs/umba/stl_keil_initializer_list.h")));
        // inputFiles.emplace_back(umba::filename::appendPath(rootPath, std::string("_libs/umba/stl_keil_type_traits.h")));
        // inputFiles.emplace_back(umba::filename::appendPath(rootPath, std::string("_libs/umba/string_plus.h")));
        // inputFiles.emplace_back(umba::filename::appendPath(rootPath, std::string("_libs/umba/rgbquad.h")));

        // inputFiles.emplace_back(umba::filename::appendPath(rootPath, std::string("_libs/umba/")));

        // inputFiles.emplace_back(umba::filename::appendPath(rootPath, std::string("_libs/marty_decimal/tests/src/regression_tests.cpp")));

        // inputFiles.emplace_back(umba::filename::appendPath(rootPath, std::string("tests/tokenizer/number_ull.cpp")));

        inputFiles.emplace_back(umba::filename::appendPath(rootPath, std::string("tests/suffix_gluing_sample.h")));
    }


    // Пока с kind не определился, и пихаем в keywords всё
    std::unordered_map<std::string, int> cppKeywords;
    // std::unordered_map<std::string, int> cppPreprocessorKeywords;
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


    auto tokenizerBuilder = umba::tokenizer::makeTokenizerBuilderCpp<char>();
    using TokenizerBuilderType = decltype(tokenizerBuilder);

    //using tokenizer_type        = std::decay<decltype(tokenizer)>;
    using tokenizer_type         = typename TokenizerBuilderType::tokenizer_type;
    using InputIteratorType      = typename tokenizer_type::iterator_type;
    using tokenizer_char_type    = typename tokenizer_type::value_type;
    using messages_string_type   = typename tokenizer_type::messages_string_type;
    using token_parsed_data_type = typename tokenizer_type::token_parsed_data_type;



    std::ostringstream oss;
    bool bOk = true;
    bool inPreprocessor = false;


    auto tokenHandler =     [&]( auto &tokenizer
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

                                    inPreprocessor = false;
                                    return true;
                                }
                                else if (tokenType==UMBA_TOKENIZER_TOKEN_CTRL_CC_PP_DEFINE)
                                {
                                    return true;
                                }
                                else if (tokenType==UMBA_TOKENIZER_TOKEN_CTRL_CC_PP_INCLUDE)
                                {
                                    return true;
                                }

                                if (tokenType&UMBA_TOKENIZER_TOKEN_CTRL_FLAG)
                                {
                                    return true; // Управляющий токен, не надо выводить, никакой нагрузки при нём нет
                                }


                                if (tokenType==UMBA_TOKENIZER_TOKEN_IDENTIFIER)
                                {
                                    auto identStr = umba::iterator::makeString(b, e);

                                    if (!inPreprocessor)
                                    {
                                        if (cppKeywords.find(identStr)!=cppKeywords.end())
                                            tokenType = UMBA_TOKENIZER_TOKEN_KEYWORD_SET1_FIRST;
                                    }
                                    else // preprocessor
                                    {
                                        if (cppKeywords.find(identStr)!=cppKeywords.end())
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


    auto tokenizer = umba::tokenizer::makeTokenizerCpp( tokenizerBuilder
                                                      , tokenHandler
                                                      );


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
                                 UMBA_USED(bErr); UMBA_USED(it); UMBA_USED(msg);
                             };



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

        std::cout << "\nProcessing: '" << inputFilename << "'\n";

        if (!umba::filesys::readFile(inputFilename, text))
        {
            std::cout << "Failed to read input file\n";
            continue;
        }

        if (text.empty())
        {
            std::cout << "Input file is empty\n";
            continue;
        }

        if (text.back()!='\n' && text.back()!='\r')
        {
            std::cout << "Warning: no linefeed at end of file\n";
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
            InputIteratorType it = itBegin;
            for(; it!=itEnd && bOk; ++it)
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

            //if (bOk)
            {
                oss<<"</pre>\n</body>\n</html>\n";

                if (inputFilename.empty())
                {
                    std::cout << oss.str() << "\n";
                }
                else
                {
#if defined(DUPLICATE_TO_STD_OUT)
                    std::cout << oss.str() << "\n";
#endif
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
#if defined(DUPLICATE_TO_STD_OUT)
                    std::cout << oss.str() << "\n";
#endif

            // !!! Inform about exception
            auto resultText = marty_cpp::converLfToOutputFormat("!!!"  + oss.str(), outputLinefeed);
            auto outputFilename = umba::filename::replaceExtention(inputFilename, std::string("html"));
            umba::filesys::writeFile(outputFilename, resultText, true /* overwrite */ );

            std::cout << "!!!\n";
        }
#endif

    }

    return bOk ? 0 : 1;

}


