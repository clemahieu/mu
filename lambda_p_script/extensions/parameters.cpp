#include "parameters.h"

#include <lambda_p_io/analyzer/expression.h>
#include <lambda_p/errors/error_target.h>
#include <lambda_p_io/analyzer/routine.h>
#include <lambda_p_io/analyzer/analyzer.h>
#include <lambda_p_io/ast/expression.h>
#include <lambda_p_script/nodes/parameters.h>

#include <sstream>

void lambda_p_script::extensions::parameters::operator () (lambda_p_io::analyzer::expression & expression_a)
{
	if (expression_a.position == 0)
	{
		if (expression_a.expression_m->values.size () == 1)
		{
			auto existing (counts.find (expression_a.result));
			if (existing == counts.end ())
			{
				count_checked (expression_a);
			}
			else
			{
				if (existing->second->count == expression_a.expression_m->individual_names.size ())
				{
					count_checked (expression_a);
				}
				else
				{
					std::wstringstream message;
					message << L"Number of parameters in current expression: ";
					message << expression_a.expression_m->individual_names.size ();
					message << L" differs from previous expression: ";
					message << existing->second;
					(*expression_a.routine.analyzer.errors) (message.str ());
				}
			}
		}
		else
		{
			(*expression_a.routine.analyzer.errors) (L"Parameters operation takes no arguments");
		}
	}
	else
	{
		(*expression_a.routine.analyzer.errors) (L"Parameters extension can only be used as the operation of an expression");
	}
}

void lambda_p_script::extensions::parameters::count_checked (lambda_p_io::analyzer::expression & expression_a)
{
	counts.insert (std::map <boost::shared_ptr <lambda_p::expression>, boost::shared_ptr <lambda_p_script::nodes::parameters>>::value_type (expression_a.result, boost::shared_ptr <lambda_p_script::nodes::parameters> (new lambda_p_script::nodes::parameters (expression_a.expression_m->individual_names.size ()))));
}