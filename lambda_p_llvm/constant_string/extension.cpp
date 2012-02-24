#include "extension.h"

#include <core/errors/error_target.h>
#include <io/analyzer/expression.h>
#include <io/ast/expression.h>
#include <io/ast/identifier.h>
#include <lambda_p_script/string/node.h>
#include <lambda_p_script/closure/single.h>
#include <lambda_p_llvm/constant_string/create.h>
#include <lambda_p_llvm/module/node.h>
#include <lambda_p_llvm/context/node.h>
#include <core/expression.h>

#include <boost/make_shared.hpp>

lambda_p_llvm::constant_string::extension::extension (boost::shared_ptr <lambda_p_llvm::context::node> context_a, boost::shared_ptr <lambda_p_llvm::module::node> module_a)
	: module (module_a),
	context (context_a)
{
}

void lambda_p_llvm::constant_string::extension::operator () (boost::shared_ptr <mu::core::errors::error_target> errors_a, mu::io::analyzer::expression & expression_a)
{
	auto position (expression_a.position + 1);
	if (position < expression_a.expression_m->values.size ())
	{
		expression_a.position = position;
		auto identifier (boost::dynamic_pointer_cast <mu::io::ast::identifier> (expression_a.expression_m->values [position]));
		if (identifier.get () != nullptr)
		{
			auto node (boost::make_shared <lambda_p_script::closure::single> (boost::make_shared <lambda_p_llvm::constant_string::create> ()));
			node->closed.push_back (context);
			node->closed.push_back (module);
			node->closed.push_back (boost::make_shared <lambda_p_script::string::node> (identifier->string));
			auto result (boost::make_shared <mu::core::expression> (identifier->context));
			result->dependencies.push_back (node);
			expression_a.self->dependencies.push_back (result);
		}
		else
		{
			(*errors_a) (L"Constant_string extension requires its argument to be an identifer");
		}
	}
	else
	{
		(*errors_a) (L"Constant_string extension requires one argument");
	}
}