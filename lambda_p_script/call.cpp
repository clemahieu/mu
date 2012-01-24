#include "call.h"

#include <lambda_p_script/node.h>
#include <lambda_p_script/operation.h>
#include <lambda_p/errors/error_context.h>
#include <lambda_p_script/context.h>

#include <boost/make_shared.hpp>

lambda_p_script::call::call (size_t results_a, lambda_p::context context_a)
	: results (results_a),
	context (context_a)
{
}

void lambda_p_script::call::operator () (boost::shared_ptr <lambda_p::errors::error_target> errors_a, lambda_p_script::context & context_a)
{
	std::vector <boost::shared_ptr <lambda_p::node>> arguments_l;
	auto errors_l (boost::make_shared <lambda_p::errors::error_context> (errors_a, context));
	for (auto i (arguments.begin ()), j (arguments.end ()); i != j; ++i)
	{
		(*(*i)) (errors_a, context_a, arguments_l);
	}
	std::vector <boost::shared_ptr <lambda_p::node>> results_l;
	if (arguments_l.size () > 0)
	{
		auto operation (boost::dynamic_pointer_cast <lambda_p_script::operation> (arguments_l [0]));
		if (operation.get () != nullptr)
		{
			auto segment (lambda_p_script::segment <boost::shared_ptr <lambda_p::node>> (1, arguments_l.size () - 1, arguments_l));
			operation->perform (errors_l, segment, results_l);
			std::vector <boost::shared_ptr <lambda_p::node>> & target (context_a.nodes [results]);
			assert (target.empty () && L"Destination has already been assigned");
			target.assign (results_l.begin (), results_l.end ());
		}
		else
		{
			(*errors_a) (L"First argument to call is not an operation", context);
		}
	}
	else
	{
		(*errors_a) (L"Call has no arguments", context);
	}
}