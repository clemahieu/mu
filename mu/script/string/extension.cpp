#include <mu/script/string/extension.h>

#include <mu/io/analyzer/expression.h>
#include <mu/io/analyzer/routine.h>
#include <mu/io/analyzer/analyzer.h>
#include <mu/io/ast/expression.h>
#include <mu/core/errors/error_target.h>
#include <mu/io/ast/identifier.h>
#include <mu/core/expression.h>
#include <mu/script/string/node.h>
#include <mu/core/errors/string_error.h>

#include <sstream>

#include <boost/make_shared.hpp>

#include <gc_cpp.h>

void mu::script::string::extension::operator () (boost::shared_ptr <mu::core::errors::error_target> errors_a, mu::io::analyzer::expression & expression_a)
{	
	auto data_position (expression_a.position + 1);
	if (expression_a.expression_m->values.size () > data_position)
	{
		expression_a.position = data_position;
		auto data (boost::dynamic_pointer_cast <mu::io::ast::identifier> (expression_a.expression_m->values [data_position]));
		if (data.get () != nullptr)
		{
			expression_a.self->dependencies.push_back (boost::shared_ptr <mu::script::string::node> (new mu::script::string::node (data->string)));
		}
		else
		{
			(*errors_a) (new (GC) mu::core::errors::string_error (L"String extension requires its argument to be an identifier"));
		}
	}
	else
	{
		(*errors_a) (new (GC) mu::core::errors::string_error (L"String extension requires one argument"));
	}
}