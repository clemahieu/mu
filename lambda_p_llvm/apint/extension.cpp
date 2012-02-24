#include "extension.h"

#include <core/errors/error_target.h>
#include <io/analyzer/expression.h>
#include <lambda_p_script/integer/extension.h>
#include <io/ast/expression.h>
#include <io/ast/identifier.h>
#include <core/expression.h>
#include <lambda_p_llvm/apint/node.h>
#include <lambda_p_script/integer/node.h>

#include <boost/make_shared.hpp>

void lambda_p_llvm::apint::extension::operator () (boost::shared_ptr <mu::core::errors::error_target> errors_a, mu::io::analyzer::expression & expression_a)
{
	auto position (expression_a.position + 1);
	if (expression_a.expression_m->values.size () > position)
	{
		expression_a.position = position;
		auto value (boost::dynamic_pointer_cast <mu::io::ast::identifier> (expression_a.expression_m->values [position]));
		if (value.get () != nullptr)
		{
			auto result (lambda_p_script::integer::core (errors_a, value->string));
			if (result.get () != nullptr)
			{
				expression_a.self->dependencies.push_back (boost::make_shared <lambda_p_llvm::apint::node> (new llvm::APInt (64, result->value)));
			}
		}
		else
		{
			(*errors_a) (L"APInt requires its argument to be an identifier");
		}
	}
	else
	{
		(*errors_a) (L"APInt extension requires at least one argument");
	}
}