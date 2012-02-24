#include "extension.h"

#include <mu/io/analyzer/expression.h>
#include <mu/io/analyzer/routine.h>
#include <mu/io/analyzer/analyzer.h>
#include <mu/io/ast/expression.h>
#include <mu/core/errors/error_target.h>
#include <mu/io/ast/identifier.h>
#include <mu/core/expression.h>
#include <lambda_p_script/string/node.h>

#include <sstream>

void lambda_p_script::string::extension::operator () (boost::shared_ptr <mu::core::errors::error_target> errors_a, mu::io::analyzer::expression & expression_a)
{	
	auto data_position (expression_a.position + 1);
	if (expression_a.expression_m->values.size () > data_position)
	{
		expression_a.position = data_position;
		auto data (boost::dynamic_pointer_cast <mu::io::ast::identifier> (expression_a.expression_m->values [data_position]));
		if (data.get () != nullptr)
		{
			expression_a.self->dependencies.push_back (boost::shared_ptr <lambda_p_script::string::node> (new lambda_p_script::string::node (data->string)));
		}
		else
		{
			(*errors_a) (L"String extension requires its argument to be an identifier", mu::core::context (expression_a.expression_m->values [data_position - 1]->context.first, expression_a.expression_m->values [data_position]->context.last));
		}
	}
	else
	{
		(*errors_a) (L"String extension requires one argument", expression_a.expression_m->values [data_position - 1]->context);
	}
}