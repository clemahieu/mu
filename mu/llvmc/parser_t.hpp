#include <mu/llvmc/parser.hpp>

#include <mu/io/tokens.hpp>
#include <mu/core/error.hpp>

#include <gc_cpp.h>

template <typename T, typename U>
mu::core::error * mu::llvmc::parser::ast_or_refer (T identifier_op, U other_token_op)
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
                other_token_op (item.token, id);
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