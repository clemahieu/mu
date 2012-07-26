#include <mu/io/analyzer/name_map.h>

#include <mu/core/errors/error_target.h>
#include <mu/core/expression.h>
#include <mu/io/analyzer/resolver.h>
#include <mu/core/errors/string_error.h>

#include <assert.h>

#include <gc_cpp.h>

void mu::io::analyzer::name_map::insert_global (mu::core::errors::error_target * errors_a, mu::string const & name, mu::core::node * const node)
{
    auto collision (used_names.find (name) != used_names.end ());
    if (collision)
    {
        mu::stringstream message;
        message << L"Global name: ";
        message << name;
        message << L" has already been used";
        (*errors_a) (message.str ());
    }
    else
    {
        assert (mapping.find (name) == mapping.end ());
        used_names.insert (name);
        mapping [name] = node;
        resolve (name, node);
    }
}

void mu::io::analyzer::name_map::insert_local (mu::core::errors::error_target * errors_a, mu::string const & name, mu::core::node * const node)
{
    auto collision (mapping.find (name) != mapping.end ());
    if (collision)
    {
        mu::stringstream message;
        message << L"Local name: ";
        message << name;
        message << L" has already been used";
        (*errors_a) (message.str ());
    }
    else
    {
        used_names.insert (name);
        mapping [name] = node;
        locals.insert (name);
        resolve (name, node);
    }
}

void mu::io::analyzer::name_map::free_locals (mu::core::errors::error_target * errors_a)
{
    for (auto i (locals.begin ()), j (locals.end ()); i != j; ++i)
    {
        mapping.erase (*i);
    }
    locals.clear ();
}

void mu::io::analyzer::name_map::fill_reference (mu::string name, mu::io::debugging::context const & context_a, mu::core::expression & expression)
{
    auto existing (mapping.find (name));
    if (existing != mapping.end ())
    {
        expression.dependencies.push_back (existing->second);
    }
    else
    {
        expression.dependencies.push_back (nullptr);
        auto resolver (mu::io::analyzer::resolver (expression, expression.dependencies.size () - 1, context_a));
        unresolved.insert (std::pair <mu::string, mu::io::analyzer::resolver> (name, resolver));
    }
}

void mu::io::analyzer::name_map::resolve (mu::string const & name, mu::core::node * const node)
{
    auto first (unresolved.find (name));
    auto i (first);
    for (; i != unresolved.end () && i->first == name; ++i)
    {
        i->second (node);
    }
    unresolved.erase (first, i);
}

void mu::io::analyzer::name_map::finalize (mu::core::errors::error_target * errors_a)
{
    for (auto i (unresolved.begin ()), j (unresolved.end ()); i != j; ++i)
    {
        mu::stringstream message;
        message << U"Unresolved identifier: ";
        message << i->first;
        (*errors_a) (new (GC) mu::core::errors::string_error (message.str ()));
    }
}
