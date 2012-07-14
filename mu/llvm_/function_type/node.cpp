#include "node.h"

#include <mu/llvm_/context/node.h>
#include <mu/llvm_/type/build.h>

#include <llvm/DerivedTypes.h>
#include <llvm/ADT/ArrayRef.h>

mu::llvm_::function_type::node::node (mu::llvm_::context::node * context_a, llvm::FunctionType * function_type_a)
{
	mu::llvm_::type::build build (context_a, function_type_a->getReturnType ());
	output = build.type;
	for (auto i (function_type_a->param_begin ()), j (function_type_a->param_end ()); i != j; ++i)
	{
		llvm::Type * type (*i);
		mu::llvm_::type::build build (context_a, type);
		parameters.push_back (build.type);
	}
}

mu::llvm_::function_type::node::node (mu::llvm_::context::node * context_a, std::vector <mu::llvm_::type::node *> parameters_a, mu::llvm_::type::node * output_a)
	: context (context_a),
	parameters (parameters_a),
	output (output_a)
{
}

llvm::Type * mu::llvm_::function_type::node::type ()
{
	return function_type ();
}

llvm::FunctionType * mu::llvm_::function_type::node::function_type ()
{
	std::vector <llvm::Type *> parameters_l;
	for (auto i (parameters.begin ()), j (parameters.end ()); i != j; ++i)
	{
		parameters_l.push_back ((*i)->type ());
	}
	return llvm::FunctionType::get (output->type (), parameters_l, false);
}