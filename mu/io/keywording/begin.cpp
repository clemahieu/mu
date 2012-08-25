#include <mu/io/keywording/begin.h>

#include <mu/io/tokens/identifier.h>
#include <mu/io/keywording/keywording.h>
#include <mu/io/keywording/extensions.h>

#include <boost/algorithm/string.hpp>

mu::io::keywording::begin::begin (mu::io::keywording::keywording & keywording_a)
    : keywording (keywording_a)
{
}

void mu::io::keywording::begin::operator () (mu::io::tokens::token * token_a, mu::io::debugging::context context_a)
{
    auto identifier (dynamic_cast <mu::io::tokens::identifier *> (token_a));
    if (identifier != nullptr)
    {
        auto keyword ((*(keywording.extensions)) (identifier->string));
        if (boost::get <0> (keyword).empty ())
        {
            keywording.target (token_a, context_a);
        }
        else
        {
            auto extension (boost::get <0> (keyword) (keywording));
            assert (boost::starts_with (identifier->string, boost::get <1> (keyword)));
            mu::string shortened (identifier->string.begin () + boost::get <1> (keyword).length (), identifier->string.end ());
            keywording.state.push (extension);
            (*extension) (new (GC) mu::io::tokens::identifier (shortened), context_a);
        }
    }
    else
    {
        keywording.target (token_a, context_a);
    }
}