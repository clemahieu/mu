#include <mu/llvmc/parser.hpp>

#include <mu/core/error_string.hpp>
#include <mu/io/stream.hpp>
#include <mu/io/tokens.hpp>
#include <mu/llvmc/ast.hpp>

#include <gc_cpp.h>

mu::llvmc::module_result::~module_result ()
{
    assert ((module != nullptr) xor (error != nullptr));
}

mu::llvmc::parser::parser (mu::io::stream <mu::io::token *> & stream_a):
stream (stream_a)
{
}

mu::llvmc::module_result mu::llvmc::parser::parse ()
{
    mu::llvmc::module_result result ({nullptr, nullptr});
    auto module (new (GC) mu::llvmc::ast::module);
    auto token (stream [0]);
    auto id (token->id ());
    switch (id)
    {
        case mu::io::token_id::identifier:
            break;
        case mu::io::token_id::end:
            result.module = module;
            break;
        default:
            result.error = new (GC) mu::core::error_string (U"Unexpected token");
            break;
    }
    return result;
}