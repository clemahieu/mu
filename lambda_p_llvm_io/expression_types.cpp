#include "expression_types.h"

#include <lambda_p/expression.h>
#include <lambda_p/reference.h>
#include <lambda_p/errors/error_target.h>
#include <lambda_p_llvm_io/routine_types.h>
#include <lambda_p_llvm/type/node.h>
#include <lambda_p_llvm_io/cluster_types.h>
#include <lambda_p_llvm/module/node.h>

#include <llvm/DerivedTypes.h>
#include <llvm/Function.h>
#include <llvm/ADT/ArrayRef.h>
#include <llvm/Module.h>

#include <sstream>

#include <boost/make_shared.hpp>

lambda_p_llvm_io::expression_types::expression_types (boost::shared_ptr <lambda_p::errors::error_target> errors_a, lambda_p_llvm_io::routine_types & routine_a, boost::shared_ptr <lambda_p::expression> expression_a)
	: routine (routine_a),
	errors (errors_a),
	return_m (nullptr)
{
	if (expression_a->dependencies.size () > 0)
	{
		auto parameters_l (boost::dynamic_pointer_cast <lambda_p::parameters> (expression_a->dependencies [0]));
		if (parameters_l.get () != nullptr)
		{
			for (auto i (expression_a->dependencies.begin () + 1), j (expression_a->dependencies.end ()); i != j && !(*errors_a) (); ++i)
			{
				current = *i;
				(*current) (this);
			}
			routine_a.type_set = true;
			if (return_m != nullptr)
			{
				assert (routine_a.cluster.routines.find (routine_a.routine) == routine_a.cluster.routines.end ());
				auto function (llvm::Function::Create (llvm::FunctionType::get (return_m, parameters, false), llvm::GlobalValue::LinkageTypes::ExternalLinkage));
				routine_a.module->module->getFunctionList ().push_back (function);
				routine_a.cluster.routines [routine_a.routine] = boost::make_shared <lambda_p_llvm::function_pointer::node> (function);
			}
			else
			{
				(*errors_a) (L"Return type has not been set");
			}
		}
	}
}

void lambda_p_llvm_io::expression_types::operator () (lambda_p::expression * expression_a)
{
	std::wstringstream message;
	message << L"Only types may be in the function signature, have: ";
	message << current->name ();
	(*errors) (message.str ());
}

void lambda_p_llvm_io::expression_types::operator () (lambda_p::parameters * parameters_a)
{
	assert (false);
}

void lambda_p_llvm_io::expression_types::operator () (lambda_p::reference * reference_a)
{
	std::wstringstream message;
	message << L"Only types may be in the function signature, have: ";
	message << current->name ();
	(*errors) (message.str ());
}

void lambda_p_llvm_io::expression_types::operator () (lambda_p::link * link_a)
{
	std::wstringstream message;
	message << L"Only types may be in the function signature, have: ";
	message << current->name ();
	(*errors) (message.str ());
}

void lambda_p_llvm_io::expression_types::operator () (lambda_p::node * node_a)
{
	auto type (boost::dynamic_pointer_cast <lambda_p_llvm::type::node> (current));
	if (type.get () != nullptr)
	{
		if (return_m == nullptr)
		{
			return_m = type->type ();
		}
		else
		{
			parameters.push_back (type->type ());
		}
	}
	else
	{
		std::wstringstream message;
		message << L"Only types may be in the function signature, have: ";
		message << current->name ();
		(*errors) (message.str ());
	}
}