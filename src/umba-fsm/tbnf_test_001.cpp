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
#include "utils.h"
//
#include "tbnf.h"
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



std::string inputFilename;





int main(int argc, char* argv[])
{

    using namespace umba::tokenizer;

    if (argc>1)
    {
        inputFilename = argv[1];
    }

    if (umba::isDebuggerPresent())
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


        inputFilename = rootPath + "tests/tbnf_test_001.tbnf";
    }

    if (inputFilename.empty())
    {
        std::cerr << "Not input file taken\n";
        return 1;
    }


    // payload_type numberTokenId = UMBA_TOKENIZER_TOKEN_NUMBER_USER_LITERAL_FIRST;

    // umba::tokenizer::CppEscapedSimpleQuotedStringLiteralParser<char>  cppEscapedSimpleQuotedStringLiteralParser;
    // umba::tokenizer::SimpleQuotedStringLiteralParser<char>            simpleQuotedStringLiteralParser;


    // Литерал парсеры надо как-то добавлять, чтобы они хранились и в билдере, и в токенизере, и удалялись вместе с ними
    // Но это потом
    auto tokenizerBuilder = umba::tbnf::makeTokenizerBuilder();
    // auto tokenizer = tokenizerBuilder.addStringLiteralParser("\'", &cppEscapedSimpleQuotedStringLiteralParser, UMBA_TOKENIZER_TOKEN_CHAR_LITERAL)
    //                                  .addStringLiteralParser("\"", &cppEscapedSimpleQuotedStringLiteralParser, UMBA_TOKENIZER_TOKEN_STRING_LITERAL)
    //                                  .makeTokenizer();
    auto tokenizer = tokenizerBuilder.makeTokenizer();

    // std::ostringstream oss;
    bool bOk = true;

    umba::tbnf::GrammaParser grammaParser;

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


    tokenizer.tokenHandler = [&]( auto &tokenizer
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
        // printToken(std::cout, tokenType, b, e);
   
        return grammaParser.handleToken(tokenizer, bLineStart, tokenType, b, e, parsedData, errMsg);
    };

    tokenizer.unexpectedHandler = [&](auto &tokenizer, InputIteratorType it, InputIteratorType itEnd, const char* srcFile, int srcLine) -> bool
    {
        printError(std::cout, inputFilename, UMBA_TOKENIZER_TOKEN_UNEXPECTED, it, itEnd, srcFile, srcLine, messages_string_type());
        return false;
    };

    tokenizer.reportUnknownOperatorHandler = [&](auto &tokenizer, InputIteratorType b, InputIteratorType e)
    {
        //cout << "Possible unknown operator: '" << umba::iterator::makeString(b, e) << "'\n";
        UMBA_USED(b); UMBA_USED(e);
    };

    tokenizer.reportStringLiteralMessageHandler = [&](auto &tokenizer, bool bErr, InputIteratorType it, const messages_string_type &msg)
    {
        //void printError(StreamType &ss, const std::string &inputFilename, umba::tokenizer::payload_type tokenType, umba::iterator::TextPositionCountingIterator<char> it, umba::iterator::TextPositionCountingIterator<char> itEnd, MsgType msg=MsgType())
        #if 1
        auto errPos = it.getPosition(true); // с поиском конца строки (а вообще не надо пока, но пусть)
        std::string erroneousLineText = umba::iterator::makeString(it.getLineStartIterator(), it.getLineEndIterator());
        std::cout << (bErr ? "Error: " : "Warning: ") << msg << " at " << inputFilename << ":" << errPos.toString<std::string>() << "\n";
        std::cout << "Line:" << erroneousLineText << "\n";
        auto errMarkerStr = std::string(erroneousLineText.size(), ' ');
        if (errPos.symbolOffset>=errMarkerStr.size())
            errMarkerStr.append(1,'^');
        else
            errMarkerStr[errPos.symbolOffset] = '^';
        std::cout << "    |" << errMarkerStr << "|\n";
        #endif
        UMBA_USED(bErr); UMBA_USED(it); UMBA_USED(msg);
    };

    tokenizer.reportHandleTokenErrorHandler = [&](auto &tokenizer, payload_type tokenType, InputIteratorType b, InputIteratorType e, const messages_string_type &msg)
    {
        printError(std::cout, inputFilename, tokenType, b, e, msg);
    };
    //using report_handle_token_error = std::function<bool(TBase &tokenizer, payload_type, InputIteratorType, InputIteratorType, const MessagesStringType &)>;




    // Фильтры, установленные позже, отрабатывают раньше

    tokenizer.installTokenFilter<umba::tokenizer::filters::SimpleSuffixGluingFilter<tokenizer_type> >();


    #if defined(WIN32) || defined(_WIN32)
        marty_cpp::ELinefeedType outputLinefeed = marty_cpp::ELinefeedType::crlf;
    #else
        marty_cpp::ELinefeedType outputLinefeed = marty_cpp::ELinefeedType::lf;
    #endif


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
        // continue;
        return 2;
    }
#endif
    if (text.empty())
    {
        std::cout << "Input file '" << inputFilename << "' empty\n";
        // continue;
        return 3;
    }

    if (text.back()!='\n' && text.back()!='\r')
    {
        std::cout << "Warning: file '" << inputFilename << "': no linefeed at end of file\n";
    }

    // oss = std::ostringstream();
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

    if (bOk)
        return 0;
    else
        return 100;

}


