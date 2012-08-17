#include <mu/core/node_list_iterator.h>

#include <mu/core/node_list.h>

#include <gc_cpp.h>

#include <assert.h>

mu::core::node_list_iterator::node_list_iterator (mu::core::node_list_iterator const && other):
list (other.list),
position (other.position),
inner_cursor (other.inner_cursor),
inner_end (other.inner_end)
{
}

mu::core::node_list_iterator::node_list_iterator (mu::core::node_list & list_a):
list (list_a),
position (-1),
inner_cursor (nullptr),
inner_end (nullptr)
{
    ++(*this);
}

mu::core::node_list_iterator::node_list_iterator (mu::core::node_list & list_a, void * nothing):
list (list_a),
position (list_a.nodes.size ()),
inner_cursor (nullptr),
inner_end (nullptr)
{
}

auto mu::core::node_list_iterator::operator == (mu::core::node_list_iterator const & other) const -> bool
{
    bool result ((&list == &other.list) && (position == other.position) && (inner_cursor == other.inner_cursor) && (inner_end == other.inner_end));
    return result;
}

auto mu::core::node_list_iterator::operator != (mu::core::node_list_iterator const & other) const -> bool
{
    bool result (!(*this == other));
    return result;
}

auto mu::core::node_list_iterator::operator ++ () -> mu::core::node_list_iterator &
{
    assert ((inner_cursor == nullptr) == (inner_end == nullptr));
    do
    {
        if (inner_cursor != nullptr)
        {
            if ((*inner_cursor) == (*inner_end))
            {
                inner_cursor = nullptr;
                inner_end = nullptr;
                advance ();
            }
            else
            {
                ++(*inner_cursor);
            }
        }
        else
        {
            advance ();
        }
    } while ((inner_cursor != nullptr) && (*inner_cursor == *inner_end));
    return *this;
}

auto mu::core::node_list_iterator::operator * () -> mu::core::node *
{
    assert ((inner_cursor == nullptr) == (inner_end == nullptr));
    mu::core::node * result;
    if (inner_cursor != nullptr)
    {
        result = *(*inner_cursor);
    }
    else
    {
        result = list.nodes [position];
    }
    return result;
}

auto mu::core::node_list_iterator::advance () -> void
{
    ++position;
    if (position != list.nodes.size ())
    {
        auto list_l (dynamic_cast <mu::core::node_list *> (list.nodes [position]));
        if (list_l != nullptr)
        {
            inner_cursor = new (GC) mu::core::node_list_iterator ((*list_l).begin ());
            inner_end = new (GC) mu::core::node_list_iterator ((*list_l).end ());
        }
    }    
}

auto mu::core::node_list_iterator::nested () const -> bool
{
    auto result (inner_cursor == nullptr);
    assert (result == (inner_end == nullptr));
    return result;
}