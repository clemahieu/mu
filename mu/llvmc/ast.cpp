#include <mu/llvmc/ast.hpp>

#include <gc_cpp.h>

mu::llvmc::ast::result * mu::llvmc::ast::function::as_result (mu::llvmc::ast::node * node_a)
{
    assert (dynamic_cast <mu::llvmc::ast::result *> (node_a) != nullptr);
    auto result (static_cast <mu::llvmc::ast::result *> (node_a));
    return result;
}

mu::llvmc::ast::value * mu::llvmc::ast::function::as_value (mu::llvmc::ast::node * node_a)
{
    assert (dynamic_cast <mu::llvmc::ast::value *> (node_a) != nullptr);
    auto result (static_cast <mu::llvmc::ast::value *> (node_a));
    return result;
}

mu::llvmc::ast::node::~node ()
{
}

mu::llvmc::ast::value::value (mu::llvmc::skeleton::node * node_a):
node_m (node_a)
{
}

mu::llvmc::ast::element::element (mu::llvmc::ast::node * node_a, size_t index_a, size_t total_a):
node (node_a),
index (index_a),
total (total_a)
{
}

mu::llvmc::ast::parameter::parameter (mu::llvmc::ast::node * type_a):
type (type_a)
{
}

mu::llvmc::ast::result::result (mu::llvmc::ast::node * written_type_a):
written_type (written_type_a),
value (nullptr)
{
}