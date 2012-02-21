#include "extension.h"

#include <lambda_p/errors/error_target.h>
#include <lambda_p_io/analyzer/expression.h>
#include <lambda_p_io/ast/expression.h>
#include <lambda_p_io/ast/identifier.h>
#include <lambda_p_script/string/node.h>
#include <lambda_p_script/closure/single.h>
#include <lambda_p_llvm/constant_string/create.h>
#include <lambda_p_llvm/module/node.h>
#include <lambda_p_llvm/context/node.h>
#include <lambda_p/expression.h>

#include <boost/make_shared.hpp>

lambda_p_llvm::constant_string::extension::extension (boost::shared_ptr <lambda_p_llvm::context::node> context_a, boost::shared_ptr <lambda_p_llvm::module::node> module_a)
	: module (module_a),
	context (context_a)
{
}

void lambda_p_llvm::constant_string::extension::operator () (boost::shared_ptr <lambda_p::errors::error_target> errors_a, lambda_p_io::analyzer::expression & expression_a)
{
	auto position (expression_a.position + 1);
	if (position < expression_a.expression_m->values.size ())
	{
		expression_a.position = position;
		auto identifier (boost::dynamic_pointer_cast <lambda_p_io::ast::identifier> (expression_a.expression_m->values [position]));
		if (identifier.get () != nullptr)
		{
			auto result (boost::make_shared <lambda_p_script::closure::single> (boost::make_shared <lambda_p_llvm::constant_string::create> ()));
			result->closed.push_back (context);
			result->closed.push_back (module);
			result->closed.push_back (boost::make_shared <lambda_p_script::string::node> (identifier->string));
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