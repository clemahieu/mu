#include <mu/script/astring/extension.h>

#include <mu/io/analyzer/expression.h>
#include <mu/io/analyzer/routine.h>
#include <mu/io/analyzer/analyzer.h>
#include <mu/io/ast/expression.h>
#include <mu/core/errors/error_target.h>
#include <mu/io/ast/identifier.h>
#include <mu/core/expression.h>
#include <mu/script/astring/node.h>

#include <sstream>

#include <gc_cpp.h>

void mu::script::astring::extension::operator () (mu::io::tokens::token * token_a, mu::io::debugging::context context_a)
{
    assert (false);
    /*assert (remaining.empty ());
	auto data_position (expression_a.position + 1);
	expression_a.position = data_position;
	if (expression_a.expression_m->values.size () > data_position)
	{
		auto data (dynamic_cast <mu::io::ast::identifier *> (expression_a.expression_m->values [data_position]));
		if (data != nullptr)
		{
			std::string string_l (data->string.begin (), data->string.end ());
			expression_a.self->dependencies.push_back (new (GC) mu::script::astring::node (string_l));
		}
		else
		{
			errors_a (U"AString extension requires its argument to be an identifier");
		}
	}
	else
	{
		errors_a (U"AString extension requires one argument");
	}*/
}