#include <mu/io/analyzer_global.h>

#include <mu/io/analyzer_analyzer.h>
#include <mu/io/tokens_value.h>

#include <gc_cpp.h>

mu::io::keywording::global::global (mu::io::keywording::keywording & keywording_a, mu::core::node * node_a):
keywording (keywording_a),
node (node_a)    
{
}

void mu::io::keywording::global::operator () (mu::io::tokens::token * token_a)
{
    keywording.state.pop ();
    keywording (new (GC) mu::io::tokens::value (token_a->context, node));
}