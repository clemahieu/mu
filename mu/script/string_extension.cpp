#include <mu/script/string_extension.h>

#include <mu/core/errors/error_target.h>
#include <mu/script/string_node.h>
#include <mu/core/errors/string_error.h>
#include <mu/io/tokens_identifier.h>
#include <mu/io/tokens_value.h>
#include <mu/io/analyzer_analyzer.h>
#include <mu/io/analyzer_error.h>

#include <sstream>

#include <gc_cpp.h>

mu::script::string::extension::extension (mu::io::analyzer::analyzer & analyzer_a):
analyzer (analyzer_a)
{
}

void mu::script::string::extension::operator () (mu::io::tokens::token * token_a)
{
    assert (dynamic_cast <mu::io::tokens::identifier *> (token_a) != nullptr);
    auto data (static_cast <mu::io::tokens::identifier *> (token_a));
    analyzer.state.pop ();
    analyzer (new (GC) mu::io::tokens::value (token_a->context, new (GC) mu::script::string::node (data->string)));
}