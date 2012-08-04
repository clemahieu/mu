#include <mu/script/parser/body.h>

#include <mu/io/tokens/token.h>
#include <mu/script/parser/routine.h>
#include <mu/script/parser/parser.h>
#include <mu/io/tokens/divider.h>
#include <mu/script/parser/cluster.h>
#include <mu/io/tokens/identifier.h>
#include <mu/script/runtime/expression.h>
#include <mu/script/runtime/fixed.h>
#include <mu/io/tokens/stream_end.h>
#include <mu/io/tokens/parameters.h>
#include <mu/io/tokens/value.h>
#include <mu/script/parser/expression.h>

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
    unexpected_token (routine.cluster.parser, token, context);
}

void mu::script::parser::body::operator () (mu::io::tokens::identifier * token)
{
    auto expression_l (expression);
    auto position (expression_l->dependencies.size ());
    expression_l->dependencies.resize (position + 1);
    routine.cluster.map.fill_reference (token->string, context,
        [expression_l, position]
        (mu::core::node * node_a)
        {
            assert (dynamic_cast <mu::script::operation *> (node_a) != nullptr);
            expression_l->dependencies [position] = static_cast <mu::script::operation *> (node_a);
        }
    );
}

void mu::script::parser::body::operator () (mu::io::tokens::left_square * token)
{
    auto state_l (new (GC) mu::script::parser::expression (routine));
    expression->dependencies.push_back(state_l->expression_m);
    routine.cluster.parser.state.push (state_l);
}

void mu::script::parser::body::operator () (mu::io::tokens::right_square * token)
{
    routine.cluster.parser.state.pop ();
}

void mu::script::parser::body::operator () (mu::io::tokens::stream_end * token)
{
    unexpected_token (routine.cluster.parser, token, context);
}

void mu::script::parser::body::operator () (mu::io::tokens::parameters * token)
{
    unexpected_token (routine.cluster.parser, token, context);
}

void mu::script::parser::body::operator () (mu::io::tokens::value * token)
{
    expression->dependencies.push_back (new (GC) mu::script::runtime::fixed (token->node));
}