#include <mu/llvmc/partial_ast.hpp>

#include <mu/llvmc/parser.hpp>
#include <mu/io/stream_token.hpp>
#include <mu/io/tokens.hpp>

#include <gc_cpp.h>

mu::llvmc::partial_ast_result::partial_ast_result (mu::io::token * token_a, mu::llvmc::ast::node * ast_a):
token (token_a),
ast (ast_a)
{
    assert ((token != nullptr) xor (ast != nullptr));
}

mu::llvmc::partial_ast_result::partial_ast_result (mu::llvmc::partial_ast_result const & other_a):
token (other_a.token),
ast (other_a.ast)
{
    assert ((token != nullptr) xor (ast != nullptr));
}

mu::llvmc::partial_ast_result & mu::llvmc::partial_ast_result::operator = (mu::llvmc::partial_ast_result const & other_a)
{
    token = other_a.token;
    ast = other_a.ast;
    assert ((token != nullptr) xor (ast != nullptr));
    return *this;
}

mu::llvmc::partial_ast::partial_ast (mu::io::stream_token & tokens_a, mu::llvmc::parser & parser_a):
item (new (GC) mu::io::end, nullptr),
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
                    item = {nullptr, ast.node};
                }
                else
                {
                    item = {new (GC) mu::io::end, nullptr};
                }
            }
            else
            {
                item = {token, nullptr};
            }
        }
            break;
        default:
            item = {token, nullptr};
            break;
    }
}