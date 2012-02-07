#include "node.h"

#include <lambda_p_llvm/context/node.h>

#include <llvm/DerivedTypes.h>
#include <llvm/ADT/ArrayRef.h>

lambda_p_llvm::function_type::node::node (boost::shared_ptr <lambda_p_llvm::context::node> context_a, std::vector <boost::shared_ptr <lambda_p_llvm::type::node>> parameters_a, std::vector <boost::shared_ptr <lambda_p_llvm::type::node>> outputs_a)
	: parameters (parameters_a),
	outputs (outputs_a),
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
	llvm::Type * outputs_l;
	if (outputs.size () == 0)
	{
		outputs_l = llvm::Type::getVoidTy (context->context);
	}
	else if (outputs.size () == 1)
	{
		outputs_l = outputs [0]->type ();
	}
	else
	{
		std::vector <llvm::Type *> components;
		for (auto i (outputs.begin ()), j (outputs.end ()); i != j; ++i)
		{
			components.push_back ((*i)->type ());
		}
		outputs_l = llvm::StructType::get (context->context, components, false);
	}
	return llvm::FunctionType::get (outputs_l, parameters_l, false);
}