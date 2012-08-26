#include <mu/llvm_/apint/extension.h>

#include <mu/core/errors/error_target.h>
#include <mu/script/integer/extension.h>
#include <mu/io/ast/expression.h>
#include <mu/io/ast/identifier.h>
#include <mu/llvm_/apint/node.h>
#include <mu/script/integer/node.h>

#include <gc_cpp.h>

mu::llvm_::apint::extension::extension (mu::io::keywording::keywording & keywording_a):
keywording (keywording_a)
{
}

void mu::llvm_::apint::extension::operator () (mu::io::tokens::token * token_a)
{
    assert (false);/*
    assert (remaining.empty ());
	auto position (expression_a.position + 1);
	if (expression_a.expression_m->values.size () > position)
	{
		expression_a.position = position;
		auto value (dynamic_cast <mu::io::ast::identifier *> (expression_a.expression_m->values [position]));
		if (value != nullptr)
		{
			auto result (mu::script::integer::core (errors_a, value->string));
			if (result != nullptr)
			{
				expression_a.self->dependencies.push_back (new (GC) mu::llvm_::apint::node (new llvm::APInt (64, result->value)));
			}
		}
		else
		{
			errors_a (U"APInt requires its argument to be an identifier");
		}
	}
	else
	{
		errors_a (U"APInt extension requires at least one argument");
	}*/
}