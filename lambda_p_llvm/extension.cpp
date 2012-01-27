#include "extension.h"

#include <lambda_p/errors/error_target.h>
#include <lambda_p_io/analyzer/expression.h>
#include <lambda_p_script/integer/extension.h>
#include <lambda_p_io/ast/expression.h>
#include <lambda_p/expression.h>
#include <lambda_p_script/integer/node.h>
#include <lambda_p_llvm/analyzer/operation.h>

#include <boost/make_shared.hpp>

void lambda_p_llvm::extension::operator () (boost::shared_ptr <lambda_p::errors::error_target> errors_a, lambda_p_io::analyzer::expression & expression_a)
{
	auto position (expression_a.position + 1);
	if (expression_a.expression_m->values.size () > position)
	{
		expression_a.position = position;
		auto value (boost::dynamic_pointer_cast <lambda_p_io::ast::expression> (expression_a.expression_m->values [position]));
		if (value.get () != nullptr)
		{
			lambda_p_llvm::analyzer::operation operation;
			std::vector <boost::shared_ptr <lambda_p::node>> arguments;
			arguments.push_back (value);
			std::vector <boost::shared_ptr <lambda_p::node>> results;
			operation (errors_a, arguments, results);
			if (results.size () != 0)
			{
				expression_a.self->dependencies.push_back (results [0]);
			}
		}
		else
		{
			(*errors_a) (L"LLVM requires its argument to be an expression");
		}
	}
	else
	{
		(*errors_a) (L"LLVM extension requires at least one argument");
	}
}