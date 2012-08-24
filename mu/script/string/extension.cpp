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

mu::script::string::extension::extension (mu::io::keywording::keywording & keywording_a)
    : keywording (keywording_a),
    first (true)
{
}

void mu::script::string::extension::operator () (mu::io::tokens::token * token_a, mu::io::debugging::context context_a)
{
    if (first)
    {
        first = false;
    }
    else
    {
        auto data (dynamic_cast <mu::io::tokens::identifier *> (token_a));
        if (data != nullptr)
        {
            keywording.state.pop ();
            keywording (new (GC) mu::io::tokens::value (new (GC) mu::script::string::node (data->string)), context_a);
        }
        else
        {
            keywording.state.push (new (GC) mu::io::keywording::error);
            keywording.errors (U"String extension requires its argument to be an identifier");
        }      
    }
}