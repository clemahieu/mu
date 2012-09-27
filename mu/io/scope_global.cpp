#include <mu/io/scope_global.h>

#include <mu/core/node_list.h>
#include <mu/io/analyzer_extensions.h>
#include <mu/core/errors/error_target.h>
#include <mu/core/errors/string_error.h>

#include <gc_cpp.h>

#include <assert.h>

mu::io::scope::global::global (mu::io::analyzer::extensions & extensions_a):
extensions (extensions_a)
{
}

bool mu::io::scope::global::declare (mu::core::errors::error_target & errors_a, mu::string const & name_a, mu::core::node * const node_a, mu::io::context const & context_a)
{
    auto reserved (reserve (errors_a, name_a));
    if (!reserved)
    {
        auto& mapping_l (mapping [name_a]);
        assert (mapping_l == nullptr);
        mapping_l = node_a;
        auto first (unresolved.find (name_a));
        auto i (first);
        while (i != unresolved.end () && i->first == name_a)
        {
            i->second->nodes.push_back (node_a);
            ++i;
        }
        unresolved.erase (first, i);
    }
    return reserved;
}

bool mu::io::scope::global::fill (mu::string const & name_a, mu::core::node_list & target_a)
{
    auto existing (mapping.find (name_a));
    auto result (existing == mapping.end ());
    if (!result)
    {
        target_a.nodes.push_back (existing->second);
    }
    return result;
}

bool mu::io::scope::global::reserve (mu::core::errors::error_target & errors_a, mu::string const & name_a)
{
    auto result (mapping.find (name_a) != mapping.end ());
    auto existing (extensions (name_a));
    result = result || !boost::get <0> (existing).empty ();
    if (!result)
    {
        mapping [name_a] = nullptr;
    }
    return result;
}

void mu::io::scope::global::pass (mu::multimap <mu::string, mu::core::node_list *> const & unresolved_a)
{
    unresolved.insert (unresolved_a.begin (), unresolved_a.end ());
}

bool mu::io::scope::global::end (mu::core::errors::error_target & errors_a)
{
    bool result (!unresolved.empty ());
    for (auto i (unresolved.begin ()), j (unresolved.end ()); i != j; ++i)
    {
        mu::stringstream message;
        message << U"Unresolved identifier: ";
        message << i->first;
        errors_a (new (GC) mu::core::errors::string_error (message.str ()));
    }
    return result;
}