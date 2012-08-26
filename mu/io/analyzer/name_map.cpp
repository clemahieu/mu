#include <mu/io/analyzer/name_map.h>

#include <mu/core/errors/error_target.h>
#include <mu/io/analyzer/resolver.h>
#include <mu/core/errors/string_error.h>
#include <mu/core/node_list.h>

#include <boost/array.hpp>

#include <assert.h>

#include <gc_cpp.h>

void mu::io::analyzer::name_map::insert_global (mu::core::errors::error_target & errors_a, mu::string const & name, mu::core::node * const node, mu::io::context const & context_a)
{
    auto collision (used_names.find (name) != used_names.end ());
    if (collision)
    {
        mu::stringstream message;
        message << L"Global name: ";
        message << name;
        message << L" has already been used";
        errors_a (message.str ());
    }
    else
    {
        assert (mapping.find (name) == mapping.end ());
        used_names.insert (name);
        mapping [name] = node;
        resolve (errors_a, name, node, true, context_a);
    }

}

template <typename T>
void mu::io::analyzer::name_map::insert_global (mu::core::errors::error_target & errors_a, mu::string const & name, T const & begin, T const & end, mu::io::context const & context_a)
{
    auto collision (used_names.find (name) != used_names.end ());
    if (collision)
    {
        mu::stringstream message;
        message << L"Global name: ";
        message << name;
        message << L" has already been used";
        errors_a (message.str ());
    }
    else
    {
        assert (mapping.find (name) == mapping.end ());
        used_names.insert (name);
        auto list (new (GC) mu::core::node_list (begin, end));
        mapping [name] = list;
        resolve (errors_a, name, list, true, context_a);
    }
}

void mu::io::analyzer::name_map::insert_local (mu::core::errors::error_target & errors_a, mu::string const & name, mu::core::node * const node, mu::io::context const & context_a)
{
    auto collision (mapping.find (name) != mapping.end ());
    if (collision)
    {
        mu::stringstream message;
        message << L"Local name: ";
        message << name;
        message << L" has already been used";
        errors_a (message.str ());
    }
    else
    {
        used_names.insert (name);
        mapping [name] = node;
        locals.insert (name);
        resolve (errors_a, name, node, false, context_a);
    }
}

template <typename T>
void mu::io::analyzer::name_map::insert_local (mu::core::errors::error_target & errors_a, mu::string const & name, T const & begin, T const & end, mu::io::context const & context_a)
{
    auto collision (mapping.find (name) != mapping.end ());
    if (collision)
    {
        mu::stringstream message;
        message << L"Local name: ";
        message << name;
        message << L" has already been used";
        errors_a (message.str ());
    }
    else
    {
        used_names.insert (name);
        auto list (new (GC) mu::core::node_list (begin, end));
        mapping [name] = list;
        locals.insert (name);
        resolve (errors_a, name, list, false, context_a);
    }
}

void mu::io::analyzer::name_map::free_locals ()
{
    for (auto i (local_references.begin ()), j (local_references.end ()); i != j; ++i)
    {
        *(*i) = true;
    }
    local_references.clear ();
    for (auto i (locals.begin ()), j (locals.end ()); i != j; ++i)
    {
        mapping.erase (*i);
    }
    locals.clear ();
}

void mu::io::analyzer::name_map::fill_reference (mu::string name, mu::io::context const & context_a, mu::core::node_list & target)
{
    auto existing (mapping.find (name));
    if (existing != mapping.end ())
    {
        target.nodes.push_back (existing->second);
    }
    else
    {
        auto list (new (GC) mu::core::node_list);
        target.nodes.push_back (list);
        auto resolver (mu::io::analyzer::resolver (*list, context_a));
        std::multimap <mu::string, mu::io::analyzer::resolver, std::less <mu::string>, gc_allocator <mu::io::analyzer::resolver>>::iterator const & new_item (unresolved.insert (std::pair <mu::string, mu::io::analyzer::resolver> (name, resolver)));
        local_references.push_back (&new_item->second.only_global);
    }
}

void mu::io::analyzer::name_map::resolve (mu::core::errors::error_target & errors_a, mu::string const & name, mu::core::node * const node, bool global, mu::io::context const & context_a)
{
    auto first (unresolved.find (name));
    auto i (first);
    for (; i != unresolved.end () && i->first == name; ++i)
    {
        i->second (errors_a, global, context_a, node);
    }
    unresolved.erase (first, i);
}

bool mu::io::analyzer::name_map::finalize (mu::core::errors::error_target & errors_a)
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
