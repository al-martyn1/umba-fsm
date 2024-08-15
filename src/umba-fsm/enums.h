#pragma once

#include "marty_cpp/marty_enum.h"

#include <exception>
#include <map>
#include <stdexcept>
#include <string>
#include <unordered_map>



namespace umba{
namespace fsm{

enum class BuiltinTokenType : std::uint32_t
{
    invalid             = (std::uint32_t)(-1),
    unknown             = (std::uint32_t)(-1),
    none                = 0x0000,
    integral            = 0x0001,
    integralNumber      = 0x0001,
    _float              = 0x0002,
    floatNumber         = 0x0002,
    _operator           = 0x0003,
    operatorSeq         = 0x0003,
    operatorSequence    = 0x0003,
    literal             = 0x0004,
    stringLiteral       = 0x0004,
    identifier          = 0x0005,
    brackets            = 0x0006,
    comment             = 0x0007,
    sComment            = 0x0007,
    singleLineComment   = 0x0007,
    mComment            = 0x0008,
    multilineComment    = 0x0008

}; // enum class BuiltinTokenType : std::uint32_t

MARTY_CPP_MAKE_ENUM_IS_FLAGS_FOR_NON_FLAGS_ENUM(BuiltinTokenType)

MARTY_CPP_ENUM_CLASS_SERIALIZE_BEGIN( BuiltinTokenType, std::map, 1 )
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( BuiltinTokenType::brackets     , "Brackets"   );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( BuiltinTokenType::invalid      , "Invalid"    );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( BuiltinTokenType::none         , "None"       );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( BuiltinTokenType::integral     , "Integral"   );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( BuiltinTokenType::_float       , "Float"      );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( BuiltinTokenType::literal      , "Literal"    );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( BuiltinTokenType::identifier   , "Identifier" );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( BuiltinTokenType::comment      , "Comment"    );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( BuiltinTokenType::_operator    , "Operator"   );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( BuiltinTokenType::mComment     , "MComment"   );
MARTY_CPP_ENUM_CLASS_SERIALIZE_END( BuiltinTokenType, std::map, 1 )

MARTY_CPP_ENUM_CLASS_DESERIALIZE_BEGIN( BuiltinTokenType, std::map, 1 )
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( BuiltinTokenType::brackets     , "brackets"            );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( BuiltinTokenType::invalid      , "invalid"             );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( BuiltinTokenType::invalid      , "unknown"             );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( BuiltinTokenType::none         , "none"                );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( BuiltinTokenType::integral     , "integral"            );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( BuiltinTokenType::integral     , "integral-number"     );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( BuiltinTokenType::integral     , "integral_number"     );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( BuiltinTokenType::integral     , "integralnumber"      );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( BuiltinTokenType::_float       , "float"               );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( BuiltinTokenType::_float       , "float-number"        );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( BuiltinTokenType::_float       , "float_number"        );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( BuiltinTokenType::_float       , "floatnumber"         );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( BuiltinTokenType::literal      , "string_literal"      );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( BuiltinTokenType::literal      , "literal"             );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( BuiltinTokenType::literal      , "string-literal"      );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( BuiltinTokenType::literal      , "stringliteral"       );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( BuiltinTokenType::identifier   , "identifier"          );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( BuiltinTokenType::comment      , "single_line_comment" );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( BuiltinTokenType::comment      , "s-comment"           );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( BuiltinTokenType::comment      , "comment"             );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( BuiltinTokenType::comment      , "s_comment"           );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( BuiltinTokenType::comment      , "scomment"            );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( BuiltinTokenType::comment      , "single-line-comment" );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( BuiltinTokenType::comment      , "singlelinecomment"   );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( BuiltinTokenType::_operator    , "operator-sequence"   );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( BuiltinTokenType::_operator    , "operator_seq"        );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( BuiltinTokenType::_operator    , "operator"            );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( BuiltinTokenType::_operator    , "operator_sequence"   );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( BuiltinTokenType::_operator    , "operator-seq"        );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( BuiltinTokenType::_operator    , "operatorseq"         );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( BuiltinTokenType::_operator    , "operatorsequence"    );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( BuiltinTokenType::mComment     , "multiline-comment"   );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( BuiltinTokenType::mComment     , "m-comment"           );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( BuiltinTokenType::mComment     , "multiline_comment"   );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( BuiltinTokenType::mComment     , "m_comment"           );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( BuiltinTokenType::mComment     , "multilinecomment"    );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( BuiltinTokenType::mComment     , "mcomment"            );
MARTY_CPP_ENUM_CLASS_DESERIALIZE_END( BuiltinTokenType, std::map, 1 )


enum class BuiltinTokenTypeParams : std::uint32_t
{
    invalid     = (std::uint32_t)(-1),
    unknown     = (std::uint32_t)(-1),
    none        = 0x0000,
    base        = 0x0001,
    prefix      = 0x0002,
    suffix      = 0x0003,
    tokenId     = 0x0004,
    name        = 0x0005,
    kind        = 0x0006,
    value       = 0x0007,
    open        = 0x0008,
    close       = 0x0009,
    position    = 0x000A,
    beginning   = 0x000B,
    any         = 0x000C

}; // enum class BuiltinTokenTypeParams : std::uint32_t

MARTY_CPP_MAKE_ENUM_IS_FLAGS_FOR_NON_FLAGS_ENUM(BuiltinTokenTypeParams)

MARTY_CPP_ENUM_CLASS_SERIALIZE_BEGIN( BuiltinTokenTypeParams, std::map, 1 )
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( BuiltinTokenTypeParams::beginning   , "Beginning" );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( BuiltinTokenTypeParams::base        , "Base"      );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( BuiltinTokenTypeParams::invalid     , "Invalid"   );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( BuiltinTokenTypeParams::close       , "Close"     );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( BuiltinTokenTypeParams::kind        , "Kind"      );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( BuiltinTokenTypeParams::none        , "None"      );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( BuiltinTokenTypeParams::open        , "Open"      );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( BuiltinTokenTypeParams::prefix      , "Prefix"    );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( BuiltinTokenTypeParams::suffix      , "Suffix"    );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( BuiltinTokenTypeParams::tokenId     , "TokenId"   );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( BuiltinTokenTypeParams::name        , "Name"      );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( BuiltinTokenTypeParams::value       , "Value"     );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( BuiltinTokenTypeParams::position    , "Position"  );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( BuiltinTokenTypeParams::any         , "Any"       );
MARTY_CPP_ENUM_CLASS_SERIALIZE_END( BuiltinTokenTypeParams, std::map, 1 )

MARTY_CPP_ENUM_CLASS_DESERIALIZE_BEGIN( BuiltinTokenTypeParams, std::map, 1 )
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( BuiltinTokenTypeParams::beginning   , "beginning" );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( BuiltinTokenTypeParams::base        , "base"      );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( BuiltinTokenTypeParams::invalid     , "invalid"   );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( BuiltinTokenTypeParams::invalid     , "unknown"   );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( BuiltinTokenTypeParams::close       , "close"     );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( BuiltinTokenTypeParams::kind        , "kind"      );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( BuiltinTokenTypeParams::none        , "none"      );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( BuiltinTokenTypeParams::open        , "open"      );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( BuiltinTokenTypeParams::prefix      , "prefix"    );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( BuiltinTokenTypeParams::suffix      , "suffix"    );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( BuiltinTokenTypeParams::tokenId     , "token-id"  );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( BuiltinTokenTypeParams::tokenId     , "token_id"  );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( BuiltinTokenTypeParams::tokenId     , "tokenid"   );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( BuiltinTokenTypeParams::name        , "name"      );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( BuiltinTokenTypeParams::value       , "value"     );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( BuiltinTokenTypeParams::position    , "position"  );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( BuiltinTokenTypeParams::any         , "any"       );
MARTY_CPP_ENUM_CLASS_DESERIALIZE_END( BuiltinTokenTypeParams, std::map, 1 )

} // namespace fsm
} // namespace umba

