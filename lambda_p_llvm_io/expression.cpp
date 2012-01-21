#include "expression.h"

#include <lambda_p/expression.h>
#include <lambda_p/reference.h>
#include <lambda_p/errors/error_target.h>
#include <lambda_p_llvm/value/node.h>
#include <lambda_p_llvm/function/node.h>
#include <lambda_p_llvm_io/routine.h>

#include <llvm/Function.h>
#include <llvm/DerivedTypes.h>
#include <llvm/BasicBlock.h>
#include <llvm/Instructions.h>

#include <sstream>

lambda_p_llvm_io::expression::expression (boost::shared_ptr <lambda_p::errors::error_target> errors_a, llvm::BasicBlock * & block_a, std::map <boost::shared_ptr <lambda_p::expression>, std::vector <boost::shared_ptr <lambda_p_llvm::value::node>>> & values_a, boost::shared_ptr <lambda_p::expression> expression_a)
	: values (values_a),
	errors (errors_a),
	block (block_a)
{
	for (auto i (expression_a->dependencies.begin ()), j (expression_a->dependencies.end ()); i != j && !(*errors) (); ++i)
	{
		current = *i;
		(*current) (this);
	}
	if (!(*errors_a) ())
	{
		if (target != nullptr)
		{
			auto function (target->function ());
			if (arguments.size () == function->getFunctionType ()->getNumParams ())
			{
				std::vector <boost::shared_ptr <lambda_p_llvm::value::node>> & destination (values [expression_a]);
				assert (destination.empty ());
				auto call (llvm::CallInst::Create (target->function (), arguments));
				block_a->getInstList ().push_back (call);
				if (target->multiple_return)
				{
					auto return_type (llvm::cast <llvm::StructType> (function->getReturnType ()));
					for (size_t i (0), j (return_type->getNumElements()); i != j; ++i)
					{
						auto element (llvm::ExtractValueInst::Create (call, i));
						block_a->getInstList ().push_back (element);
						destination.push_back (boost::shared_ptr <lambda_p_llvm::value::node> (new lambda_p_llvm::value::node (element)));
					}
				}
				else
				{
					if (!call->getType ()->isVoidTy ())
					{
						destination.push_back (boost::shared_ptr <lambda_p_llvm::value::node> (new lambda_p_llvm::value::node (call)));
					}
				}
			}
			else
			{
				(*errors_a) (L"Not enough arguments");
			}
		}
		else
		{
			(*errors_a) (L"Expression has no target");
		}
	}
}

void lambda_p_llvm_io::expression::operator () (lambda_p::expression * expression_a)
{
	auto current_l (boost::static_pointer_cast <lambda_p::expression> (current));
	auto source (values [current_l]);
	if (!source.empty ())
	{
		auto took_target (process_target (boost::dynamic_pointer_cast <lambda_p_llvm::value::node> (source [0])));
		auto i (source.begin () + (took_target ? 1 : 0));
		auto j (source.end ());
		for (; i != j && !(*errors) (); ++i)
		{
			process_value (*i);
		}
	}
}

void lambda_p_llvm_io::expression::operator () (lambda_p::reference * reference_a)
{
	auto value (boost::dynamic_pointer_cast <lambda_p::reference> (current));
	auto source (values [value->expression]);
	if (source.size () > value->index)
	{
		process_value (source [value->index]);
	}
	else
	{
		std::wstringstream message;
		message << L"Trying to index: ";
		message << value->index;
		message << L" only have: ";
		message << source.size ();
		message << L" arguments";
		(*errors) (message.str ());
	}
}

void lambda_p_llvm_io::expression::operator () (lambda_p::routine * routine_a)
{
	assert (false);
}

void lambda_p_llvm_io::expression::operator () (lambda_p::node * node_a)
{
	auto value (boost::dynamic_pointer_cast <lambda_p_llvm::value::node> (current));
	if (value.get () != nullptr)
	{
		auto took_target (process_target (value));
		if (!took_target)
		{
			process_value (value);
		}
	}
	else
	{
		std::wstringstream message;
		message << L"Node is not an LLVM value: ";
		message << current->name ();
		(*errors) (message.str ());
	}
}

void lambda_p_llvm_io::expression::process_value (boost::shared_ptr <lambda_p_llvm::value::node> node_a)
{
	assert (target != nullptr);
	auto function (target->function ());
	if (arguments.size () < function->getFunctionType ()->getNumParams ())
	{
		if (node_a->value ()->getType () == target->function ()->getFunctionType ()->getParamType (arguments.size ()))
		{
			arguments.push_back (node_a->value ());
		}
		else
		{
			std::wstringstream message;
			message << L"Actual argument type does not match formal parameter type";
			(*errors) (message.str ());
		}
	}
	else
	{
		(*errors) (L"Passing too many arguments");
	}
}

bool lambda_p_llvm_io::expression::process_target (boost::shared_ptr <lambda_p_llvm::value::node> node_a)
{
	bool result (false);
	if (target == nullptr)
	{
		auto function (boost::dynamic_pointer_cast <lambda_p_llvm::function::node> (node_a));
		if (function.get () != nullptr)
		{
			result = true;
			target = function;
		}
		else
		{
			(*errors) (L"Target of expression is not a function");
		}
	}
	return result;
}