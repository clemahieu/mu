#include "extension.h"

#include <lambda_p_io/analyzer/expression.h>
#include <lambda_p_io/analyzer/routine.h>
#include <lambda_p_io/analyzer/analyzer.h>
#include <lambda_p_io/ast/expression.h>
#include <lambda_p/errors/error_target.h>
#include <lambda_p_io/ast/identifier.h>
#include <lambda_p/expression.h>
#include <lambda_p_script/astring/node.h>

#include <sstream>

void lambda_p_script::astring::extension::operator () (lambda_p_io::analyzer::expression & expression_a)
{	
	auto data_position (expression_a.position + 1);
	expression_a.position = data_position;
	if (expression_a.expression_m->values.size () > data_position)
	{
		auto data (boost::dynamic_pointer_cast <lambda_p_io::ast::identifier> (expression_a.expression_m->values [data_position]));
		if (data.get () != nullptr)
		{
			std::string string_l (data->string.begin (), data->string.end ());
			expression_a.self->dependencies.push_back (boost::shared_ptr <lambda_p_script::astring::node> (new lambda_p_script::astring::node (string_l)));
		}
		else
		{
			(*expression_a.routine.analyzer.errors) (L"AString extension requires its argument to be an identifier");
		}
	}
	else
	{
		(*expression_a.routine.analyzer.errors) (L"AString extension requires one argument");
	}
}