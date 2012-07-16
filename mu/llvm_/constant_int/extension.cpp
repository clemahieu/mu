#include <mu/llvm_/constant_int/extension.h>

#include <mu/core/errors/error_target.h>
#include <mu/io/analyzer/expression.h>
#include <mu/script/integer/extension.h>
#include <mu/io/ast/expression.h>
#include <mu/io/ast/identifier.h>
#include <mu/core/expression.h>
#include <mu/llvm_/value/node.h>
#include <mu/script/integer/node.h>
#include <mu/script/closure/single.h>
#include <mu/llvm_/constant_int/create.h>
#include <mu/llvm_/apint/node.h>
#include <mu/llvm_/context/node.h>
#include <mu/io/analyzer/extensions/global.h>

#include <sstream>

#include <gc_cpp.h>

mu::llvm_::constant_int::extension::extension (mu::llvm_::context::node * context_a)
	: context (context_a)
{
}

void mu::llvm_::constant_int::extension::operator () (mu::core::errors::error_target * errors_a, mu::io::analyzer::expression & expression_a)
{
	auto bits_position (expression_a.position + 1);
	auto number_position (expression_a.position + 2);
	if (expression_a.expression_m->values.size () > number_position)
	{
		expression_a.position = number_position;
		auto bits_identifier (dynamic_cast <mu::io::ast::identifier *> (expression_a.expression_m->values [bits_position]));
		if (bits_identifier != nullptr)
		{
			auto number_identifier (dynamic_cast <mu::io::ast::identifier *> (expression_a.expression_m->values [number_position]));
			if (number_identifier != nullptr)
			{
                std::wstring characters (bits_identifier->string.begin (), bits_identifier->string.end ());
				auto bits (mu::script::integer::core_d (errors_a, characters));
				if (bits != nullptr)
				{
					auto number (mu::script::integer::core (errors_a, number_identifier->string));
					if (number != nullptr)
					{
						auto node (new (GC) mu::script::closure::single (new (GC) mu::llvm_::constant_int::create));
						node->closed.push_back (context);
						node->closed.push_back (new (GC) mu::llvm_::apint::node (new llvm::APInt (64, bits->value)));
						node->closed.push_back (new (GC) mu::llvm_::apint::node (new llvm::APInt (bits->value, number->value)));
						auto result (new (GC) mu::core::expression);
						result->dependencies.push_back (node);
						expression_a.self->dependencies.push_back (result);
					}
					else
					{
						mu::stringstream message;
						message << L"Unable to parse number: ";
						message << number;
					}
				}
				else
				{
					mu::stringstream message;
					message << L"Unable to parse bits number: ";
					message << bits_identifier->string;
					(*errors_a) (message.str ());
				}
			}
			else
			{
				(*errors_a) (U"Constant_int requires the second argument to be an identifier");
			}
		}
		else
		{
			(*errors_a) (U"Constant_int requires the first argument to be an identifier");
		}
	}
	else
	{
		(*errors_a) (U"Constant_int extension requires two arguments");
	}
}