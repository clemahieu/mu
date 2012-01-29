#include "expression.h"

#include <lambda_p/expression.h>
#include <lambda_p/reference.h>
#include <lambda_p/errors/error_target.h>
#include <lambda_p_llvm/value/node.h>
#include <lambda_p_llvm/function_pointer/node.h>
#include <lambda_p_llvm/function/operation.h>
#include <lambda_p_llvm/function/node.h>
#include <lambda_p_llvm_io/routine.h>
#include <lambda_p_llvm/operation.h>
#include <lambda_p_llvm/lambda/operation.h>
#include <lambda_p/cluster.h>
#include <lambda_p/link.h>
#include <lambda_p/routine.h>

#include <llvm/Function.h>
#include <llvm/DerivedTypes.h>
#include <llvm/BasicBlock.h>
#include <llvm/Instructions.h>

#include <sstream>

#include <boost/make_shared.hpp>

lambda_p_llvm_io::expression::expression (boost::shared_ptr <lambda_p::errors::error_target> errors_a, llvm::BasicBlock * & block_a, std::map <boost::shared_ptr <lambda_p::expression>, std::vector <boost::shared_ptr <lambda_p::node>>> & values_a, boost::shared_ptr <lambda_p::expression> expression_a)
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
		if (target.get () != nullptr)
		{
			(*target) (errors_a, block_a, arguments, values [expression_a]);
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
		auto took_target (process_target (source [0]));
		auto i (source.begin () + (took_target ? 1 : 0));
		auto j (source.end ());
		for (; i != j && !(*errors) (); ++i)
		{
			arguments.push_back ((*i));
		}
	}
}

void lambda_p_llvm_io::expression::operator () (lambda_p::reference * reference_a)
{
	auto value (boost::dynamic_pointer_cast <lambda_p::reference> (current));
	auto source (values [value->expression]);
	if (source.size () > value->index)
	{
		auto value_l (source [value->index]);
		auto took_target (process_target (value_l));
		if (!took_target)
		{
			arguments.push_back (value_l);
		}
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

void lambda_p_llvm_io::expression::operator () (lambda_p::link * link_a)
{
	auto routine (link_a->routine);
	auto took_target (process_target (routine));
	if (!took_target)
	{
		arguments.push_back (current);
	}
}

void lambda_p_llvm_io::expression::operator () (lambda_p::node * node_a)
{
	auto took_target (process_target (current));
	if (!took_target)
	{
		arguments.push_back (current);
	}
}

bool lambda_p_llvm_io::expression::process_target (boost::shared_ptr <lambda_p::node> node_a)
{
	assert (node_a.get () != nullptr);
	bool result (false);
	if (target.get () == nullptr)
	{
		auto operation (boost::dynamic_pointer_cast <lambda_p_llvm::operation> (node_a));
		if (operation.get () != nullptr)
		{
			result = true;
			target = operation;
		}
		else
		{
			auto function (boost::dynamic_pointer_cast <lambda_p_llvm::function_pointer::node> (node_a));
			if (function.get () != nullptr)
			{
				result = true;
				target = boost::make_shared <lambda_p_llvm::function::operation> (function);
			}
			else
			{
				auto function (boost::dynamic_pointer_cast <lambda_p_llvm::function::node> (node_a));
				if (function.get () != nullptr)
				{
					result = true;
					target = boost::make_shared <lambda_p_llvm::function::operation> (boost::make_shared <lambda_p_llvm::function_pointer::node> (function->function (), false));
				}
				else
				{
					not_callable ();
				}
			}
		}
	}
	return result;
}

void lambda_p_llvm_io::expression::not_callable ()
{
	(*errors) (L"Target of expression is not callable");
}