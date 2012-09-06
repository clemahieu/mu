#include <mu/io/analyzer_analyzer.h>

#include <mu/io/tokens_identifier.h>
#include <mu/io/analyzer_begin.h>
#include <mu/io/analyzer_state.h>

#include <gc_cpp.h>

mu::io::analyzer::analyzer::analyzer (mu::core::errors::error_target & errors_a, boost::function <void (mu::io::tokens::token const &)> target_a, mu::io::analyzer::extensions * extensions_a):
target (target_a),
extensions (extensions_a),
errors (errors_a)
{
    state.push (new (GC) mu::io::analyzer::begin (*this));
}

void mu::io::analyzer::analyzer::operator () (mu::io::tokens::token const & token_a)
{
    auto top (state.top ());
    (*top) (token_a);
}