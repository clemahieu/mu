#include <mu/io/analyzer_begin.h>

#include <mu/io/tokens_identifier.h>
#include <mu/io/analyzer_analyzer.h>
#include <mu/io/analyzer_extensions.h>

#include <boost/algorithm/string.hpp>

mu::io::analyzer::begin::begin (mu::io::analyzer::analyzer & analyzer_a)
    : analyzer (analyzer_a)
{
}

void mu::io::analyzer::begin::operator () (mu::io::tokens::token * token_a)
{
    auto identifier (dynamic_cast <mu::io::tokens::identifier *> (token_a));
    if (identifier != nullptr)
    {
        auto keyword ((*(analyzer.extensions)) (identifier->string));
        if (boost::get <0> (keyword).empty ())
        {
            analyzer.target (token_a);
        }
        else
        {
            auto extension (boost::get <0> (keyword) (analyzer));
            assert (boost::starts_with (identifier->string, boost::get <1> (keyword)));
            mu::string shortened (identifier->string.begin () + boost::get <1> (keyword).length (), identifier->string.end ());
            analyzer.state.push (extension);
            (*extension) (new (GC) mu::io::tokens::identifier (token_a->context, shortened));
        }
    }
    else
    {
        analyzer.target (token_a);
    }
}