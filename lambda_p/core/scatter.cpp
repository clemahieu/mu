#include "scatter.h"

#include <lambda_p/core/target.h>

void lambda_p::core::scatter::operator () (std::vector <boost::shared_ptr <lambda_p::core::expression>> arguments)
{
	auto argument_current (arguments.begin ());
	auto argument_end (arguments.end ());
	for (auto target_current (targets.begin ()), target_end (targets.end ()); target_current != target_end; ++target_current, ++argument_current)
	{
		auto current (*target_current);
		for (auto i (current.begin ()), j (current.end ()); i != j; ++i)
		{
			(*(*i)) (*argument_current);
		}
	}
}
