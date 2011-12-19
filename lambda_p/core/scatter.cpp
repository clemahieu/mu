#include "scatter.h"

lambda_p::core::scatter::scatter ()
	: required (~0)
{
}

void lambda_p::core::scatter::operator () (std::vector <boost::shared_ptr <lambda_p::core::expression>> arguments)
{
	if (required != ~0)
	{
		assert (arguments.size () == required);
		assert (targets.size () <= required);
	}
	auto argument_current (arguments.begin ());
	auto argument_end (arguments.end ());
	for (auto target_current (targets.begin ()), target_end (targets.end ()); target_current != target_end; ++target_current, ++argument_current)
	{
		auto current (*target_current);
		for (auto i (current.begin ()), j (current.end ()); i != j; ++i)
		{
			std::vector <boost::shared_ptr <lambda_p::core::expression>> arguments;
			arguments.push_back (*argument_current);
			(*(*i)) (arguments);
		}
	}
}
			
std::vector <boost::shared_ptr <lambda_p::core::target>> & lambda_p::core::scatter::operator [] (size_t index)
{
	if (targets.size () <= index)
	{
		targets.resize (index + 1);
	}
	return targets [index];
}

void lambda_p::core::scatter::set_required (size_t required_a)
{
	required = required_a;
}
