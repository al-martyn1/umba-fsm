#pragma once

#include "marty_cpp/marty_enum.h"

#include <exception>
#include <map>
#include <stdexcept>
#include <string>
#include <unordered_map>



namespace umba{
namespace tbnf{

enum class BuiltinTokenType : std::uint32_t
{
    invalid             = (std::uint32_t)(-1),
    unknown             = (std::uint32_t)(-1),
    none                = 0x0000,
    integralNumber      = 0x0001,
    integral            = 0x0001,
    floatNumber         = 0x0002,
    _float              = 0x0002,
    _operator           = 0x0003,
    operatorSeq         = 0x0003,
    operatorSequence    = 0x0003,
    stringLiteral       = 0x0004,
    literal             = 0x0004,
    keyword             = 0x0005,
    bracket             = 0x0006,
    sComment            = 0x0007,
    comment             = 0x0007,
    singleLineComment   = 0x0007,
    mComment            = 0x0008,
    multilineComment    = 0x0008

}; // enum class BuiltinTokenType : std::uint32_t

MARTY_CPP_MAKE_ENUM_IS_FLAGS_FOR_NON_FLAGS_ENUM(BuiltinTokenType)

MARTY_CPP_ENUM_CLASS_SERIALIZE_BEGIN( BuiltinTokenType, std::map, 1 )
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( BuiltinTokenType::floatNumber      , "FloatNumber"    );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( BuiltinTokenType::integralNumber   , "IntegralNumber" );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( BuiltinTokenType::invalid          , "Invalid"        );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( BuiltinTokenType::bracket          , "Bracket"        );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( BuiltinTokenType::none             , "None"           );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( BuiltinTokenType::_operator        , "Operator"       );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( BuiltinTokenType::stringLiteral    , "StringLiteral"  );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( BuiltinTokenType::keyword          , "Keyword"        );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( BuiltinTokenType::sComment         , "SComment"       );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( BuiltinTokenType::mComment         , "MComment"       );
MARTY_CPP_ENUM_CLASS_SERIALIZE_END( BuiltinTokenType, std::map, 1 )

MARTY_CPP_ENUM_CLASS_DESERIALIZE_BEGIN( BuiltinTokenType, std::map, 1 )
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( BuiltinTokenType::floatNumber      , "float-number"        );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( BuiltinTokenType::floatNumber      , "float_number"        );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( BuiltinTokenType::floatNumber      , "floatnumber"         );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( BuiltinTokenType::floatNumber      , "float"               );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( BuiltinTokenType::integralNumber   , "integral-number"     );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( BuiltinTokenType::integralNumber   , "integral_number"     );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( BuiltinTokenType::integralNumber   , "integralnumber"      );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( BuiltinTokenType::integralNumber   , "integral"            );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( BuiltinTokenType::invalid          , "invalid"             );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( BuiltinTokenType::invalid          , "unknown"             );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( BuiltinTokenType::bracket          , "bracket"             );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( BuiltinTokenType::none             , "none"                );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( BuiltinTokenType::_operator        , "operator-sequence"   );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( BuiltinTokenType::_operator        , "operator_seq"        );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( BuiltinTokenType::_operator        , "operator"            );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( BuiltinTokenType::_operator        , "operator_sequence"   );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( BuiltinTokenType::_operator        , "operator-seq"        );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( BuiltinTokenType::_operator        , "operatorseq"         );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( BuiltinTokenType::_operator        , "operatorsequence"    );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( BuiltinTokenType::stringLiteral    , "string-literal"      );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( BuiltinTokenType::stringLiteral    , "literal"             );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( BuiltinTokenType::stringLiteral    , "string_literal"      );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( BuiltinTokenType::stringLiteral    , "stringliteral"       );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( BuiltinTokenType::keyword          , "keyword"             );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( BuiltinTokenType::sComment         , "single_line_comment" );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( BuiltinTokenType::sComment         , "comment"             );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( BuiltinTokenType::sComment         , "s-comment"           );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( BuiltinTokenType::sComment         , "s_comment"           );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( BuiltinTokenType::sComment         , "scomment"            );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( BuiltinTokenType::sComment         , "single-line-comment" );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( BuiltinTokenType::sComment         , "singlelinecomment"   );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( BuiltinTokenType::mComment         , "multiline-comment"   );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( BuiltinTokenType::mComment         , "m-comment"           );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( BuiltinTokenType::mComment         , "multiline_comment"   );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( BuiltinTokenType::mComment         , "m_comment"           );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( BuiltinTokenType::mComment         , "multilinecomment"    );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( BuiltinTokenType::mComment         , "mcomment"            );
MARTY_CPP_ENUM_CLASS_DESERIALIZE_END( BuiltinTokenType, std::map, 1 )


enum class BuiltinTokenTypeParam : std::uint32_t
{
    invalid            = (std::uint32_t)(-1),
    unknown            = (std::uint32_t)(-1),
    none               = 0x0000,
    base               = 0x0001,
    prefix             = 0x0002,
    suffix             = 0x0003,
    tokenId            = 0x0004,
    name               = 0x0005,
    kind               = 0x0006,
    value              = 0x0007 /*!< keyword */,
    sequence           = 0x0008,
    operatorSequence   = 0x0008,
    opSequence         = 0x0008,
    open               = 0x0009,
    close              = 0x000A,
    position           = 0x000B,
    beginOnly          = 0x000C,
    beginning          = 0x000C,
    startOnly          = 0x000C,
    any                = 0x000D

}; // enum class BuiltinTokenTypeParam : std::uint32_t

MARTY_CPP_MAKE_ENUM_IS_FLAGS_FOR_NON_FLAGS_ENUM(BuiltinTokenTypeParam)

MARTY_CPP_ENUM_CLASS_SERIALIZE_BEGIN( BuiltinTokenTypeParam, std::map, 1 )
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( BuiltinTokenTypeParam::base        , "Base"         );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( BuiltinTokenTypeParam::invalid     , "Invalid"      );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( BuiltinTokenTypeParam::close       , "Close"        );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( BuiltinTokenTypeParam::kind        , "Kind"         );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( BuiltinTokenTypeParam::none        , "None"         );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( BuiltinTokenTypeParam::open        , "Open"         );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( BuiltinTokenTypeParam::prefix      , "Prefix"       );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( BuiltinTokenTypeParam::suffix      , "Suffix"       );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( BuiltinTokenTypeParam::tokenId     , "TokenId"      );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( BuiltinTokenTypeParam::name        , "Name"         );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( BuiltinTokenTypeParam::value       , "Value"        );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( BuiltinTokenTypeParam::beginOnly   , "Begin___Only" );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( BuiltinTokenTypeParam::sequence    , "Sequence"     );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( BuiltinTokenTypeParam::position    , "Position"     );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( BuiltinTokenTypeParam::any         , "Any"          );
MARTY_CPP_ENUM_CLASS_SERIALIZE_END( BuiltinTokenTypeParam, std::map, 1 )

MARTY_CPP_ENUM_CLASS_DESERIALIZE_BEGIN( BuiltinTokenTypeParam, std::map, 1 )
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( BuiltinTokenTypeParam::base        , "base"              );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( BuiltinTokenTypeParam::invalid     , "invalid"           );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( BuiltinTokenTypeParam::invalid     , "unknown"           );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( BuiltinTokenTypeParam::close       , "close"             );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( BuiltinTokenTypeParam::kind        , "kind"              );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( BuiltinTokenTypeParam::none        , "none"              );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( BuiltinTokenTypeParam::open        , "open"              );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( BuiltinTokenTypeParam::prefix      , "prefix"            );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( BuiltinTokenTypeParam::suffix      , "suffix"            );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( BuiltinTokenTypeParam::tokenId     , "token-id"          );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( BuiltinTokenTypeParam::tokenId     , "token_id"          );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( BuiltinTokenTypeParam::tokenId     , "tokenid"           );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( BuiltinTokenTypeParam::name        , "name"              );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( BuiltinTokenTypeParam::value       , "value"             );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( BuiltinTokenTypeParam::beginOnly   , "start____only"     );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( BuiltinTokenTypeParam::beginOnly   , "begin---only"      );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( BuiltinTokenTypeParam::beginOnly   , "begin____only"     );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( BuiltinTokenTypeParam::beginOnly   , "begin___only"      );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( BuiltinTokenTypeParam::beginOnly   , "start___only"      );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( BuiltinTokenTypeParam::beginOnly   , "beginning"         );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( BuiltinTokenTypeParam::beginOnly   , "start---only"      );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( BuiltinTokenTypeParam::sequence    , "op-sequence"       );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( BuiltinTokenTypeParam::sequence    , "operatorsequence"  );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( BuiltinTokenTypeParam::sequence    , "sequence"          );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( BuiltinTokenTypeParam::sequence    , "operator-sequence" );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( BuiltinTokenTypeParam::sequence    , "operator_sequence" );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( BuiltinTokenTypeParam::sequence    , "op_sequence"       );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( BuiltinTokenTypeParam::sequence    , "opsequence"        );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( BuiltinTokenTypeParam::position    , "position"          );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( BuiltinTokenTypeParam::any         , "any"               );
MARTY_CPP_ENUM_CLASS_DESERIALIZE_END( BuiltinTokenTypeParam, std::map, 1 )

} // namespace tbnf
} // namespace umba

