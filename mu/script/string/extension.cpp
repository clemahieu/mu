#include <mu/script/string/extension.h>

#include <mu/core/errors/error_target.h>
#include <mu/script/string/node.h>
#include <mu/core/errors/string_error.h>
#include <mu/io/tokens/identifier.h>
#include <mu/io/tokens/value.h>
#include <mu/io/keywording/keywording.h>
#include <mu/io/keywording/error.h>

#include <sstream>

#include <gc_cpp.h>

mu::script::string::extension::extension (mu::io::keywording::keywording & keywording_a):
keywording (keywording_a)
{
}

void mu::script::string::extension::operator () (mu::io::tokens::token * token_a, mu::io::context context_a)
{
    assert (dynamic_cast <mu::io::tokens::identifier *> (token_a) != nullptr);
    auto data (static_cast <mu::io::tokens::identifier *> (token_a));
    keywording.state.pop ();
    keywording (new (GC) mu::io::tokens::value (new (GC) mu::script::string::node (data->string)), context_a);
}