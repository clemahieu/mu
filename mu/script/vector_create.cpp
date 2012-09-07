#include <mu/script/vector_create.h>

#include <mu/script/vector_node.h>
#include <mu/script/context.h>

#include <gc_cpp.h>

bool mu::script::vector::create::operator () (mu::script::context & context_a)
{
    auto result (new (GC) mu::script::vector::node);
    for (auto i (context_a.parameters_begin ()), j (context_a.parameters_end ()); i != j; ++i)
    {
        result->vector.push_back (*i);
    }
    context_a.push (result);
    return true;
}