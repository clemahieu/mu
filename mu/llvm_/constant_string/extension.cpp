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

#include <llvm/Module.h>

#include <gc_cpp.h>

mu::llvm_::constant_string::extension::extension (mu::llvm_::module::node * module_a)
	: module (module_a)
{
}

void mu::llvm_::constant_string::extension::operator () (mu::core::errors::error_target * errors_a, mu::io::analyzer::expression & expression_a, mu::string remaining)
{
    assert (remaining.empty ());
	auto position (expression_a.position + 1);
	if (position < expression_a.expression_m->values.size ())
	{
		expression_a.position = position;
		auto identifier (dynamic_cast <mu::io::ast::identifier *> (expression_a.expression_m->values [position]));
		if (identifier != nullptr)
		{
			auto node (new (GC) mu::script::closure::single (new (GC) mu::llvm_::constant_string::create ()));
			node->closed.push_back (new (GC) mu::llvm_::context::node (&module->module->getContext ()));
			node->closed.push_back (module);
			node->closed.push_back (new (GC) mu::script::string::node (identifier->string));
			auto result (new (GC) mu::core::expression);
			result->dependencies.push_back (node);
			expression_a.self->dependencies.push_back (result);
		}
		else
		{
			(*errors_a) (U"Constant_string extension requires its argument to be an identifer");
		}
	}
	else
	{
		(*errors_a) (U"Constant_string extension requires one argument");
	}
}

bool mu::llvm_::constant_string::extension::operator () ()
{
    return false;
}