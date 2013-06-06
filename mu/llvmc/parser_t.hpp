#include <mu/llvmc/parser.hpp>

#include <mu/io/tokens.hpp>
#include <mu/core/error.hpp>

#include <gc_cpp.h>

template <typename T>
mu::core::error * mu::llvmc::parser::parse_ast_or_refer (T op)
{
    mu::core::error * result (nullptr);
    auto item (peek ());
    if (item.ast != nullptr)
    {
        consume ();
        op (item.ast);
    }
    else if (item.token != nullptr)
    {
        auto id (item.token->id ());
        switch (id)
        {
            case mu::io::token_id::identifier:
            {
                consume ();
                current_mapping->refer (static_cast <mu::io::identifier *> (item.token)->string, op);
                break;
            }
            default:
            {
                result = new (GC) mu::core::error_string (U"Expecting ast or reference", mu::core::error_type::expecting_ast_or_reference, item.token->region);
                break;
            }
        }
    }
    else
    {
        result = item.error;
    }
    return result;
}

template <typename T>
mu::core::error * mu::llvmc::parser::parse_identifier (T identifier_op)
{
    mu::core::error * result (nullptr);
    auto item (peek ());
    if (item.token != nullptr)
    {
        auto id (item.token->id ());
        switch (id)
        {
            case mu::io::token_id::identifier:
                identifier_op (static_cast <mu::io::identifier *> (item.token));
                break;
            default:
                result = new (GC) mu::core::error_string (U"Expecting identifier", mu::core::error_type::expecting_identifier);
                break;
        }
    }
    else
    {
        result = new (GC) mu::core::error_string (U"Expecting identifier", mu::core::error_type::expecting_identifier);
    }
    return result;
}