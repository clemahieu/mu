#include <mu/io/analyzer_global.h>

#include <mu/io/analyzer_analyzer.h>
#include <mu/io/tokens_value.h>

#include <gc_cpp.h>

mu::io::analyzer::global::global (mu::io::analyzer::analyzer & analyzer_a, mu::core::node * node_a):
analyzer (analyzer_a),
node (node_a)    
{
}

void mu::io::analyzer::global::operator () (mu::io::tokens::token const & token_a)
{
    analyzer.state.pop ();
    analyzer (mu::io::tokens::value (token_a.context, node));
}