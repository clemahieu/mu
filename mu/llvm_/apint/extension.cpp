#include "extension.h"

#include <mu/core/errors/error_target.h>
#include <mu/io/analyzer/expression.h>
#include <mu/script/integer/extension.h>
#include <mu/io/ast/expression.h>
#include <mu/io/ast/identifier.h>
#include <mu/core/expression.h>
#include <mu/llvm_/apint/node.h>
#include <mu/script/integer/node.h>

#include <boost/make_shared.hpp>

void mu::llvm_::apint::extension::operator () (mu::core::errors::error_target * errors_a, mu::io::analyzer::expression & expression_a)
{
	auto position (expression_a.position + 1);
	if (expression_a.expression_m->values.size () > position)
	{
		expression_a.position = position;
		auto value (boost::dynamic_pointer_cast <mu::io::ast::identifier> (expression_a.expression_m->values [position]));
		if (value.get () != nullptr)
		{
			auto result (mu::script::integer::core (errors_a, value->string));
			if (result.get () != nullptr)
			{
				expression_a.self->dependencies.push_back (boost::make_shared <mu::llvm_::apint::node> (new llvm::APInt (64, result->value)));
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