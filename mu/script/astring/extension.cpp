#include <mu/script/astring/extension.h>

#include <mu/io/tokens/identifier.h>
#include <mu/script/astring/node.h>
#include <mu/io/keywording/keywording.h>
#include <mu/io/tokens/value.h>

#include <assert.h>

#include <gc_cpp.h>

mu::script::astring::extension::extension (mu::io::keywording::keywording & keywording_a):
keywording (keywording_a)
{
}

void mu::script::astring::extension::operator () (mu::io::tokens::token * token_a, mu::io::debugging::context context_a)
{
    assert (dynamic_cast <mu::io::tokens::identifier *> (token_a));
    auto data (static_cast <mu::io::tokens::identifier *> (token_a));
    keywording.state.pop ();
    std::string str (data->string.begin (), data->string.end ());
    keywording (new (GC) mu::io::tokens::value (new (GC) mu::script::astring::node (str)), context_a);
}