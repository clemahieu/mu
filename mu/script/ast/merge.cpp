#include <mu/script/ast/merge.h>

#include <mu/io/ast/cluster.h>
#include <mu/script/check.h>

#include <boost/make_shared.hpp>

bool mu::script::ast::merge::operator () (mu::script_runtime::context & context_a)
{
	bool complete (true);
	auto result (boost::make_shared <mu::io::ast::cluster> ());
	size_t position (0);
	for (auto i (context_a.parameters_begin ()), j (context_a.parameters_end ()); i != j; ++i, ++position)
	{
		auto cluster (boost::dynamic_pointer_cast <mu::io::ast::cluster> (*i));
		if (cluster.get () != nullptr)
		{
			result->expressions.insert (result->expressions.end (), cluster->expressions.begin (), cluster->expressions.end ());
		}
		else
		{
			mu::script::invalid_type (context_a, typeid (**i), typeid (mu::io::ast::cluster), position);
			complete = false;
		}
	}
	return complete;
}