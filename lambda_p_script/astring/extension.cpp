#include "extension.h"

#include <io/analyzer/expression.h>
#include <io/analyzer/routine.h>
#include <io/analyzer/analyzer.h>
#include <io/ast/expression.h>
#include <core/errors/error_target.h>
#include <io/ast/identifier.h>
#include <core/expression.h>
#include <lambda_p_script/astring/node.h>

#include <sstream>

void lambda_p_script::astring::extension::operator () (boost::shared_ptr <mu::core::errors::error_target> errors_a, mu::io::analyzer::expression & expression_a)
{	
	auto data_position (expression_a.position + 1);
	expression_a.position = data_position;
	if (expression_a.expression_m->values.size () > data_position)
	{
		auto data (boost::dynamic_pointer_cast <mu::io::ast::identifier> (expression_a.expression_m->values [data_position]));
		if (data.get () != nullptr)
		{
			std::string string_l (data->string.begin (), data->string.end ());
			expression_a.self->dependencies.push_back (boost::shared_ptr <lambda_p_script::astring::node> (new lambda_p_script::astring::node (string_l)));
		}
		else
		{
			(*errors_a) (L"AString extension requires its argument to be an identifier");
		}
	}
	else
	{
		(*errors_a) (L"AString extension requires one argument");
	}
}