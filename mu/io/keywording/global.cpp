#include <mu/io/keywording/global.h>

#include <mu/io/keywording/keywording.h>
#include <mu/io/tokens/value.h>

#include <gc_cpp.h>

mu::io::keywording::global::global (mu::io::keywording::keywording & keywording_a, mu::core::node * node_a)
    : keywording (keywording_a),
    node (node_a)    
{
}

void mu::io::keywording::global::operator () (mu::io::tokens::token * token_a, mu::io::debugging::context context_a)
{
    keywording.state.pop ();
    keywording (new (GC) mu::io::tokens::value (node), context_a);
}