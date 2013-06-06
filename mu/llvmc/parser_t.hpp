#include <mu/llvmc/parser.hpp>

#include <mu/io/tokens.hpp>
#include <mu/core/error.hpp>

#include <gc_cpp.h>

template <typename T>
mu::core::error * mu::llvmc::parser::ast_or_refer (T identifier_op)
{
    mu::core::error * result (nullptr);
    auto item (peek ());
    if (item.ast != nullptr)
    {
        consume ();
        identifier_op (item.ast);
    }
    else if (item.token != nullptr)
    {
        auto id (item.token->id ());
        switch (id)
        {
            case mu::io::token_id::identifier:
            {
                consume ();
                current_mapping->refer (static_cast <mu::io::identifier *> (item.token)->string, identifier_op);
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