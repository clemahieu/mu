#include <mu/script/astring_extension.h>

#include <mu/io/tokens_identifier.h>
#include <mu/script/astring_node.h>
#include <mu/io/analyzer_analyzer.h>
#include <mu/io/tokens_value.h>

#include <assert.h>

#include <gc_cpp.h>

mu::script::astring::extension::extension (mu::io::analyzer::analyzer & analyzer_a):
analyzer (analyzer_a)
{
}

void mu::script::astring::extension::operator () (mu::io::tokens::token * token_a)
{
    assert (dynamic_cast <mu::io::tokens::identifier *> (token_a));
    auto data (static_cast <mu::io::tokens::identifier *> (token_a));
    analyzer.state.pop ();
    std::string str (data->string.begin (), data->string.end ());
    analyzer (new (GC) mu::io::tokens::value (token_a->context, new (GC) mu::script::astring::node (str)));
}