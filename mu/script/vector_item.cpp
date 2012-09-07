#include <mu/script/vector_item.h>

#include <mu/script/context.h>
#include <mu/core/check.h>
#include <mu/script/vector_node.h>
#include <mu/script/integer_node.h>

bool mu::script::vector::item::operator () (mu::script::context & context_a)
{
    auto result (mu::core::check <mu::script::vector::node, mu::script::integer::node> (context_a));
    if (result)
    {
        auto vector (static_cast <mu::script::vector::node *> (context_a.parameters (0)));
        auto index (static_cast <mu::script::integer::node *> (context_a.parameters (1)));
        result = vector->vector.size () > index->value;
        if (result)
        {
            context_a.push (vector->vector [index->value]);
        }
    }
    return result;
}