#include <mu/llvmc/partial_ast.hpp>

#include <mu/llvmc/parser.hpp>
#include <mu/io/stream_token.hpp>
#include <mu/io/tokens.hpp>
#include <mu/core/error_string.hpp>

#include <gc_cpp.h>

mu::llvmc::partial_ast_result::partial_ast_result (mu::io::token * token_a, mu::llvmc::ast::node * ast_a, mu::core::error * error_a):
token (token_a),
ast (ast_a),
error (error_a)
{
    assert (valid ());
}

mu::llvmc::partial_ast_result::partial_ast_result (mu::llvmc::partial_ast_result const & other_a):
token (other_a.token),
ast (other_a.ast),
error (other_a.error)
{
    assert (valid ());
}

mu::llvmc::partial_ast_result & mu::llvmc::partial_ast_result::operator = (mu::llvmc::partial_ast_result const & other_a)
{
    token = other_a.token;
    ast = other_a.ast;
    error = other_a.error;
    assert (valid ());
    return *this;
}

bool mu::llvmc::partial_ast_result::valid ()
{
    auto result (not ((token != nullptr and ast != nullptr) or (token != nullptr and error != nullptr) or (ast != nullptr and error != nullptr)));
    return result;
}

mu::llvmc::partial_ast::partial_ast (mu::io::stream_token & tokens_a, mu::llvmc::parser & parser_a):
item (nullptr, nullptr, new (GC) mu::core::error_string (U"Unset")),
tokens (tokens_a),
parser (parser_a)
{
    refill ();
}

void mu::llvmc::partial_ast::consume ()
{
    tokens.consume (1);
    refill ();
}

mu::llvmc::partial_ast_result & mu::llvmc::partial_ast::peek ()
{
    auto & result (item);
    return result;
}
void mu::llvmc::partial_ast::refill ()
{
    auto token (tokens [0]);
    auto id (token->id ());
    switch (id)
    {
        case mu::io::token_id::identifier:
        {
            auto identifier (static_cast <mu::io::identifier *> (token));
            auto hook (parser.keywords.get_hook (identifier->string));
            if (hook.hook != nullptr)
            {
                auto ast (hook.hook->parse (hook.data, parser));
                if (ast.node != nullptr)
                {
                    item = {nullptr, ast.node, nullptr};
                }
                else
                {
                    item = {nullptr, nullptr, ast.error};
                }
            }
            else
            {
                item = {token, nullptr, nullptr};
            }
        }
            break;
        default:
            item = {token, nullptr, nullptr};
            break;
    }
}