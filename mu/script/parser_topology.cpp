#include <mu/script/parser_topology.h>

#include <mu/core/errors/error_target.h>
#include <mu/script/runtime_reference.h>
#include <mu/script/runtime_expression.h>
#include <mu/script/runtime_routine.h>
#include <mu/script/runtime_selection.h>

mu::script::parser::topology::topology (mu::script::runtime::expression * root, boost::function <void (mu::script::runtime::expression *)> target_a, mu::core::errors::error_target & errors_a):
target (target_a),
errors (errors_a)
{
    assert (root != nullptr);
    recurse (root);
}

void mu::script::parser::topology::recurse (mu::script::runtime::expression * expression_a)
{
	if (path.find (expression_a) != path.end ())
	{
        errors (U"Routine has a cycle");
	}
	path.insert (expression_a);
	auto existing (already.find (expression_a));
	if (existing == already.end ())
	{
		already.insert (expression_a);
		for (auto i (expression_a->dependencies.begin ()), j (expression_a->dependencies.end ()); i != j; ++i)
		{
			auto current (*i);
            auto expression (dynamic_cast <mu::script::runtime::expression *> (current));
            auto reference (dynamic_cast <mu::script::runtime::reference *> (current));
            auto selection (dynamic_cast <mu::script::runtime::selection *> (current));
            if (expression != nullptr)
            {
                recurse (expression);
            }
            else if (reference != nullptr)
            {
                recurse (reference->expression);
            }
            else if (selection != nullptr)
            {
                recurse (selection->expression);
            }
		}
		target (expression_a);
	}
	path.erase (expression_a);
}