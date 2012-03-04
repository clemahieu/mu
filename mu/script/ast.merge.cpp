#include <mu/script/ast.merge.h>

#include <mu/io/ast.cluster.h>

#include <boost/make_shared.hpp>

void mu::script::ast::merge::perform (boost::shared_ptr <mu::core::errors::error_target> errors_a, mu::core::segment <boost::shared_ptr <mu::core::node>> parameters, std::vector <boost::shared_ptr <mu::core::node>> & results)
{
	auto result (boost::make_shared <mu::io::ast::cluster> ());
	size_t position (0);
	for (auto i (parameters.begin ()), j (parameters.end ()); i != j; ++i, ++position)
	{
		auto cluster (boost::dynamic_pointer_cast <mu::io::ast::cluster> (*i));
		if (cluster.get () != nullptr)
		{
			result->expressions.insert (result->expressions.end (), cluster->expressions.begin (), cluster->expressions.end ());
		}
		else
		{
			invalid_type (errors_a, *i, position);
		}
	}
}
