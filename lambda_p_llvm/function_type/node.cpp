#include "node.h"

#include <lambda_p_llvm/context/node.h>
#include <lambda_p_llvm/type/build.h>

#include <llvm/DerivedTypes.h>
#include <llvm/ADT/ArrayRef.h>

lambda_p_llvm::function_type::node::node (boost::shared_ptr <lambda_p_llvm::context::node> context_a, llvm::FunctionType * function_type_a)
{
	lambda_p_llvm::type::build build (context_a, function_type_a->getReturnType ());
	output = build.type;
	for (auto i (function_type_a->param_begin ()), j (function_type_a->param_end ()); i != j; ++i)
	{
		llvm::Type * type (*i);
		lambda_p_llvm::type::build build (context_a, type);
		parameters.push_back (build.type);
	}
}

lambda_p_llvm::function_type::node::node (boost::shared_ptr <lambda_p_llvm::context::node> context_a, std::vector <boost::shared_ptr <lambda_p_llvm::type::node>> parameters_a, boost::shared_ptr <lambda_p_llvm::type::node> output_a)
	: parameters (parameters_a),
	output (output_a),
	context (context_a)
{
}

llvm::Type * lambda_p_llvm::function_type::node::type ()
{
	return function_type ();
}

llvm::FunctionType * lambda_p_llvm::function_type::node::function_type ()
{
	std::vector <llvm::Type *> parameters_l;
	for (auto i (parameters.begin ()), j (parameters.end ()); i != j; ++i)
	{
		parameters_l.push_back ((*i)->type ());
	}
	return llvm::FunctionType::get (output->type (), parameters_l, false);
}