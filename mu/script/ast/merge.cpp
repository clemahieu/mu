#include <mu/script/ast/merge.h>

#include <mu/io/ast/cluster.h>
#include <mu/script/check.h>

#include <gc_cpp.h>

bool mu::script::ast::merge::operator () (mu::script::context & context_a)
{
	bool complete (true);
	auto result (new (GC) mu::io::ast::cluster);
	size_t position (0);
	for (auto i (context_a.parameters_begin ()), j (context_a.parameters_end ()); i != j; ++i, ++position)
	{
		auto cluster (dynamic_cast <mu::io::ast::cluster *> (*i));
		if (cluster != nullptr)
		{
			result->expressions.insert (result->expressions.end (), cluster->expressions.begin (), cluster->expressions.end ());
		}
		else
		{
			mu::script::type_fail (context_a.errors, typeid (mu::io::ast::cluster), *i, position);
			complete = false;
		}
	}
	return complete;
}