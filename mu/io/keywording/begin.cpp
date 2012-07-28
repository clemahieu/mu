#include <mu/io/keywording/begin.h>

#include <mu/io/tokens/identifier.h>
#include <mu/io/keywording/keywording.h>
#include <mu/io/keywording/extensions.h>

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
        if (keyword.empty ())
        {
            keywording.target (token_a, context_a);
        }
        else
        {
            auto extension (keyword (keywording));
            keywording.state.push (extension);
            (*extension) (token_a, context_a);
        }
    }
}