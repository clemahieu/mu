#include <mu/script/parser_scope_merge.h>

#include <mu/core/errors/error_target.h>
#include <mu/script/parser_scope_node.h>
#include <mu/script/string_node.h>
#include <mu/core/check.h>
#include <mu/script/context.h>
#include <mu/io/analyzer_extensions.h>

#include <assert.h>

bool mu::script::parser_scope::merge::operator () (mu::script::context & context_a)
{
	bool result (mu::core::check <mu::script::parser_scope::node, mu::script::string::node, mu::script::parser_scope::node> (context_a));
	if (result)
	{
		auto one (static_cast <mu::script::parser_scope::node *> (context_a.parameters (0)));
		auto two (static_cast <mu::script::string::node *> (context_a.parameters (1)));
		auto three (static_cast <mu::script::parser_scope::node *> (context_a.parameters (2)));
        result = core (context_a.errors, one, two->string, three);
	}
	return result;
}

auto mu::script::parser_scope::merge::core (mu::core::errors::error_target & errors_a, mu::script::parser_scope::node * target, mu::string const & prefix, mu::script::parser_scope::node * source) -> bool
{
    bool result (true);
    for (auto i (source->extensions->extensions_m.begin ()), j (source->extensions->extensions_m.end ()); i != j; ++i)
    {
        mu::string name (prefix);
        name.append (i->first);
        auto error ((*target->extensions) (name, boost::get <0> (i->second), boost::get <1> (i->second)));
        if (error)
        {
            mu::stringstream message;
            message << U"Scope already contains extension named: ";
            message << i->first;
            errors_a (message.str ());
            result = false;
        }
    }
    for (auto i (source->injected.begin ()), j (source->injected.end ()); i != j; ++i)
    {
        mu::string name (prefix);
        name.append (i->first);
        auto existing (target->injected.find (name));
        if (existing == target->injected.end ())
        {
            target->injected [name] = i->second;
        }
        else
        {
            mu::stringstream message;
            message << U"Scope already contains node named: ";
            message << i->first;
            errors_a (message.str ());
            result = false;
        }
    }
    return result;
}