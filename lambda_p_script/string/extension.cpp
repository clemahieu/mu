#include "extension.h"

#include <lambda_p_io/analyzer/expression.h>
#include <lambda_p_io/analyzer/routine.h>
#include <lambda_p_io/analyzer/analyzer.h>
#include <lambda_p_io/ast/expression.h>
#include <lambda_p/errors/error_target.h>
#include <lambda_p_io/ast/identifier.h>
#include <lambda_p/expression.h>
#include <lambda_p_script/string/node.h>

#include <sstream>

void lambda_p_script::string::extension::operator () (boost::shared_ptr <lambda_p::errors::error_target> errors_a, lambda_p_io::analyzer::expression & expression_a)
{	
	auto data_position (expression_a.position + 1);
	if (expression_a.expression_m->values.size () > data_position)
	{
		expression_a.position = data_position;
		auto data (boost::dynamic_pointer_cast <lambda_p_io::ast::identifier> (expression_a.expression_m->values [data_position]));
		if (data.get () != nullptr)
		{
			expression_a.self->dependencies.push_back (boost::shared_ptr <lambda_p_script::string::node> (new lambda_p_script::string::node (data->string)));
		}
		else
		{
			(*errors_a) (L"String extension requires its argument to be an identifier", lambda_p::context (expression_a.expression_m->values [data_position - 1]->context.first, expression_a.expression_m->values [data_position]->context.last));
		}
	}
	else
	{
		(*errors_a) (L"String extension requires one argument", expression_a.expression_m->values [data_position - 1]->context);
	}
}