#include <mu/script/parser/body.h>

#include <mu/io/tokens/token.h>
#include <mu/script/parser/routine.h>
#include <mu/script/parser/parser.h>
#include <mu/io/tokens/divider.h>
#include <mu/script/parser/cluster.h>
#include <mu/io/tokens/identifier.h>
#include <mu/script/runtime/expression.h>

#include <gc_cpp.h>

mu::script::parser::body::body (mu::script::parser::routine & routine_a):
routine (routine_a),
expression (new (GC) mu::script::runtime::expression)
{
}

void mu::script::parser::body::operator () (mu::io::tokens::token * token_a, mu::io::debugging::context context_a)
{
    context = context_a;
    (*token_a) (this);
}

void mu::script::parser::body::operator () (mu::io::tokens::divider * token)
{
    unexpected_token (routine.cluster.parser.errors, token, context);
}

void mu::script::parser::body::operator () (mu::io::tokens::identifier * token)
{
    //routine.cluster.map.fill_reference (token->string, context, *expression);
}

void mu::script::parser::body::operator () (mu::io::tokens::left_square * token)
{
    
}

void mu::script::parser::body::operator () (mu::io::tokens::right_square * token)
{
    
}

void mu::script::parser::body::operator () (mu::io::tokens::stream_end * token)
{
    
}

void mu::script::parser::body::operator () (mu::io::tokens::parameters * token)
{
    
}

void mu::script::parser::body::operator () (mu::io::tokens::value * token)
{
    
}