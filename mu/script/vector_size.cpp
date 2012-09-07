#include <mu/script/vector_size.h>

#include <mu/core/check.h>
#include <mu/script/vector_node.h>
#include <mu/script/integer_node.h>
#include <mu/script/context.h>

#include <gc_cpp.h>

bool mu::script::vector::size::operator () (mu::script::context & context_a)
{
    auto valid (mu::core::check <mu::script::vector::node> (context_a));
    if (valid)
    {
        auto vector (static_cast <mu::script::vector::node *> (context_a.parameters (0)));
        auto result (new (GC) mu::script::integer::node (vector->vector.size ()));
        context_a.push (result);
    }
    return valid;
}