#include <mu/llvm_/constant_string/extension.h>

#include <mu/core/errors/error_target.h>
#include <mu/io/analyzer/expression.h>
#include <mu/io/ast/expression.h>
#include <mu/io/ast/identifier.h>
#include <mu/script/string/node.h>
#include <mu/script/closure/single.h>
#include <mu/llvm_/constant_string/create.h>
#include <mu/llvm_/module/node.h>
#include <mu/llvm_/context/node.h>
#include <mu/core/expression.h>
#include <mu/io/debugging/expression.h>
#include <mu/io/debugging/node.h>

#include <boost/make_shared.hpp>

#include <llvm/Module.h>

mu::llvm_::constant_string::extension::extension (boost::shared_ptr <mu::llvm_::module::node> module_a)
	: module (module_a)
{
}

void mu::llvm_::constant_string::extension::operator () (boost::shared_ptr <mu::core::errors::error_target> errors_a, mu::io::analyzer::expression & expression_a)
{
	auto position (expression_a.position + 1);
	if (position < expression_a.expression_m->values.size ())
	{
		expression_a.position = position;
		auto identifier (boost::dynamic_pointer_cast <mu::io::ast::identifier> (expression_a.expression_m->values [position]));
		if (identifier.get () != nullptr)
		{
			auto node (boost::make_shared <mu::script::closure::single> (boost::make_shared <mu::llvm_::constant_string::create> ()));
			node->closed.push_back (boost::make_shared <mu::llvm_::context::node> (&module->module->getContext ()));
			node->closed.push_back (module);
			node->closed.push_back (boost::make_shared <mu::script::string::node> (identifier->string));
			auto result (boost::make_shared <mu::core::expression> ());
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