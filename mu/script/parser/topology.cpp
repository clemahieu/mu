#include <mu/script/parser/topology.h>

#include <mu/core/errors/error_target.h>
#include <mu/script/runtime/reference.h>
#include <mu/script/runtime/expression.h>
#include <mu/script/runtime/routine.h>

mu::script::parser::topology::topology (std::vector <mu::script::runtime::expression *, gc_allocator <mu::script::runtime::expression *>> & expressions_a, mu::script::runtime::routine * routine_a, mu::core::errors::error_target & errors_a):
expressions (expressions_a),
routine (routine_a),
errors (errors_a)
{
}

void mu::script::parser::topology::operator () ()
{
    recurse (expressions [0]);
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
            auto expression (dynamic_cast <mu::script::runtime::expression *>(current));
            auto reference (dynamic_cast <mu::script::runtime::reference *>(current));
            if (expression != nullptr)
            {
                recurse (expression);
            }
            else if (reference != nullptr)
            {
                recurse (reference->expression);
            }
		}
		routine->expressions.push_back (expression_a);
	}
	path.erase (expression_a);
}