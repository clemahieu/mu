#include <mu/core/node_list.h>

#include <mu/core/node_list_iterator.h>

mu::core::node_list::node_list ()
{
}

template <typename T>
mu::core::node_list::node_list (T const & begin, T const & end):
nodes (begin, end)
{
}

auto mu::core::node_list::begin () -> mu::core::node_list_iterator
{
    mu::core::node_list_iterator result (*this);
    return result;
}

auto mu::core::node_list::end () -> mu::core::node_list_iterator
{
    mu::core::node_list_iterator result (*this, nullptr);
    return result;
}

auto mu::core::node_list::size () -> size_t
{
    size_t result (0);
    for (auto i (begin ()), j (end ()); i != j; ++i)
    {
        auto list (dynamic_cast <mu::core::node_list *> (*i));
        if (list != nullptr)
        {
            result = result + list->size ();
        }
        else
        {
            result = result + 1;
        }
    }
    return result;
}

auto mu::core::node_list::empty () -> bool
{
    auto result (nodes.empty () || size () == 0);
    return result;
}