#include <mu/io/scope_block.h>

#include <mu/core/node_list.h>

#include <gc_cpp.h>

#include <assert.h>

mu::io::scope::block::block (mu::io::scope::scope & parent_a):
parent (parent_a)
{
}

bool mu::io::scope::block::reserve (mu::core::errors::error_target & errors_a, mu::string const & name_a)
{
    auto result (mapping.find (name_a) != mapping.end ());
    result = result || parent.reserve (errors_a, name_a);
    if (!result)
    {
        mapping [name_a] = nullptr;
    }
    return result;
}

bool mu::io::scope::block::declare (mu::core::errors::error_target & errors_a, mu::string const & name_a, mu::core::node * const node_a, mu::io::context const & context_a)
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

void mu::io::scope::block::refer (mu::string const & name_a, mu::io::context const & context_a, mu::core::node_list & target_a)
{
    auto failed (fill (name_a, target_a));
    if (failed)
    {
        auto nodes (new (GC) mu::core::node_list);
        target_a.nodes.push_back (nodes);
        unresolved.insert (decltype (unresolved)::value_type (name_a, nodes));
    }
}

bool mu::io::scope::block::fill (mu::string const & name_a, mu::core::node_list & target_a)
{
    auto existing (mapping.find (name_a));
    auto result (existing == mapping.end ());
    if (!result)
    {
        target_a.nodes.push_back (existing->second);
    }
    else
    {
        result = parent.fill (name_a, target_a);
    }
    return result;
}

void mu::io::scope::block::pass (mu::multimap <mu::string, mu::core::node_list *> const & unresolved_a)
{
    unresolved.insert (unresolved_a.begin (), unresolved_a.end ());
}

void mu::io::scope::block::end ()
{
    parent.pass (unresolved);
}