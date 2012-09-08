#include <mu/script/string_equal.h>

#include <mu/core/check.h>
#include <mu/script/context.h>
#include <mu/script/string_node.h>
#include <mu/script/bool_c_node.h>

#include <gc_cpp.h>

bool mu::script::string::equal::operator () (mu::script::context & context_a)
{
    auto valid (mu::core::check <mu::script::string::node, mu::script::string::node> (context_a));
    if (valid)
    {
        auto one (static_cast <mu::script::string::node *> (context_a.parameters (0)));
        auto two (static_cast <mu::script::string::node *> (context_a.parameters (1)));
        auto result (new (GC) mu::script::bool_c::node (one->string == two->string));
        context_a.push (result);
    }
    return valid;
}