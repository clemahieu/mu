#include "routine.h"

#include <lambda_p/routine.h>
#include <lambda_p/order.h>
#include <lambda_p/expression.h>
#include <lambda_p/errors/error_target.h>
#include <lambda_p/errors/error_context.h>
#include <lambda_p_llvm/type/node.h>
#include <lambda_p_llvm/argument/node.h>
#include <lambda_p_llvm/module/node.h>
#include <lambda_p_llvm_io/expression.h>
#include <lambda_p_llvm/function_pointer/node.h>
#include <lambda_p_llvm/identity/operation.h>
#include <lambda_p_llvm/function_pointer/node.h>
#include <lambda_p_llvm/function_pointer_type/node.h>

#include <llvm/DerivedTypes.h>
#include <llvm/BasicBlock.h>
#include <llvm/Argument.h>
#include <llvm/Module.h>
#include <llvm/Instructions.h>
#include <llvm/Constants.h>

#include <map>
#include <sstream>

#include <boost/make_shared.hpp>

lambda_p_llvm_io::routine::routine (boost::shared_ptr <lambda_p::errors::error_target> errors_a, boost::shared_ptr <lambda_p::routine> routine_a, boost::shared_ptr <lambda_p_llvm::module::node> module_a)
	: errors (errors_a),
	routine_m (routine_a),
	module (module_a),
	unresolved (0)
{	
	lambda_p::order order (routine_a->body);
	for (auto i (order.expressions.begin ()), j (order.expressions.end ()); i != j; ++i)
	{
		auto errors_l (boost::make_shared <lambda_p::errors::error_context> (errors_a, (*i)->context));
		lambda_p_llvm_io::expression expression (errors_l, *this, *i);
	}
	try_resolve ();
}

void lambda_p_llvm_io::routine::add_function (boost::shared_ptr <lambda_p_llvm::module::node> module_a, std::vector <llvm::BasicBlock *> & blocks, llvm::FunctionType * type, bool multi, std::vector <llvm::Argument *> & arguments)
{
	auto function (llvm::Function::Create (type, llvm::GlobalValue::ExternalLinkage));
	function->getArgumentList ().clear ();
	for (auto i (arguments.begin ()), j (arguments.end ()); i != j; ++i)
	{
		function->getArgumentList ().push_back (*i);
	}
	for (auto i (blocks.begin ()), j (blocks.end ()); i != j; ++i)
	{
		function->getBasicBlockList ().push_back (*i);
	}
	module_a->module->getFunctionList ().push_back (function);
	result = boost::make_shared <lambda_p_llvm::function_pointer::node> (function, multi);
}

void lambda_p_llvm_io::routine::try_resolve ()
{
	if (unresolved == 0)
	{
		if (!(*errors) ())
		{
			if (results.size () == 0)
			{
				auto type (llvm::FunctionType::get (llvm::Type::getVoidTy (context), parameters, false));
				working->getInstList ().push_back (llvm::ReturnInst::Create (context));
				add_function (module_a, blocks, type, false, arguments);
			}
			else if (results.size () == 1)
			{
				auto value (boost::dynamic_pointer_cast <lambda_p_llvm::value::node> (results [0]));
				if (value.get () != nullptr)
				{
					auto type (llvm::FunctionType::get (value->value ()->getType (), parameters_l, false));
					working->getInstList ().push_back (llvm::ReturnInst::Create (context, value->value ()));
					add_function (module_a, blocks, type, false, arguments);
				}
				else
				{
					std::wstringstream message;
					message << L"Only values can be returned, have: ";
					message << results [0]->name ();
					(*errors_a) (message.str ());
				}
			}
			else
			{
				std::vector <llvm::Type *> return_types;
				bool good (true);
				for (auto i (results.begin ()), j (results.end ()); i != j && good; ++i)
				{
					auto value (boost::dynamic_pointer_cast <lambda_p_llvm::value::node> (*i));
					if (value.get () != nullptr)
					{
						return_types.push_back (value->value ()->getType ());
					}
					else
					{
						std::wstringstream message;
						message << L"Only values can be returned, have: ";
						message << results [0]->name ();
						(*errors_a) (message.str ());
						good = false;
					}
				}
				if (good)
				{
					auto return_type (llvm::StructType::get (context, return_types, false));
					auto type (llvm::FunctionType::get (return_type, parameters_l, false));
					unsigned int position (0);
					llvm::Value * struct_l (llvm::UndefValue::get (return_type));
					for (auto i (results.begin ()), j (results.end ()); i != j; ++i, ++position)
					{
						auto value (boost::static_pointer_cast <lambda_p_llvm::value::node> (*i));
						std::vector <unsigned int> indicies;
						indicies.push_back (position);
						auto instruction (llvm::InsertValueInst::Create (struct_l, value->value (), indicies));
						working->getInstList ().push_back (instruction);
						struct_l = instruction;
					}
					working->getInstList ().push_back (llvm::ReturnInst::Create (context, struct_l));
					add_function (module_a, blocks, type, true, arguments);
				}
			}
		}
	}
}