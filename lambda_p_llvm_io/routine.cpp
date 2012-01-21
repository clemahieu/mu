#include "routine.h"

#include <lambda_p/routine.h>
#include <lambda_p/order.h>
#include <lambda_p/errors/error_target.h>
#include <lambda_p_llvm/type/node.h>
#include <lambda_p_llvm/argument/node.h>
#include <lambda_p_llvm/module/node.h>
#include <lambda_p_llvm_io/expression.h>
#include <lambda_p_llvm/function/node.h>

#include <llvm/DerivedTypes.h>
#include <llvm/BasicBlock.h>
#include <llvm/Argument.h>
#include <llvm/Module.h>
#include <llvm/Instructions.h>
#include <llvm/Constants.h>

#include <map>
#include <sstream>

#include <boost/make_shared.hpp>

lambda_p_llvm_io::routine::routine (boost::shared_ptr <lambda_p::errors::error_target> errors_a, boost::shared_ptr <lambda_p::routine> routine_a, boost::shared_ptr <lambda_p_llvm::module::node> module_a, lambda_p_script::segment <boost::shared_ptr <lambda_p::node>> parameters)
{	
	bool good (true);
	lambda_p::order order (routine_a->body, routine_a->parameters);
	std::map <boost::shared_ptr <lambda_p::expression>, std::vector <boost::shared_ptr <lambda_p_llvm::value::node>>> values;
	std::vector <llvm::Type *> parameters_l;
	for (auto i (parameters.begin ()), j (parameters.end ()); i != j; ++i)
	{
		auto type (boost::dynamic_pointer_cast <lambda_p_llvm::type::node> (*i));
		if (type.get () != nullptr)
		{
			parameters_l.push_back (type->type ());
			values [routine_a->parameters].push_back (boost::shared_ptr <lambda_p_llvm::argument::node> (new lambda_p_llvm::argument::node (new llvm::Argument (type->type ()))));
		}
		else
		{
			good = false;
			std::wstringstream message;
			message << L"Arguments to function must be types, have: ";
			message << (*i)->name ();
			(*errors_a) (message.str ());
		}
	}
	if (good)
	{
		llvm::LLVMContext & context (module_a->module->getContext ());
		auto working (llvm::BasicBlock::Create (context));
		std::vector <llvm::BasicBlock *> blocks;
		blocks.push_back (working);
		for (auto i (order.expressions.begin ()), j (order.expressions.end ()); i != j; ++i)
		{
			lambda_p_llvm_io::expression expression (errors_a, working, values, *i);
		}
		if (!(*errors_a) ())
		{
			auto results (values [routine_a->body]);
			if (results.size () == 0)
			{
				auto type (llvm::FunctionType::get (llvm::Type::getVoidTy (context), parameters_l, false));
				working->getInstList ().push_back (llvm::ReturnInst::Create (context));
				add_function (module_a, blocks, type, false, values [routine_a->parameters]);
			}
			else if (results.size () == 1)
			{
				auto type (llvm::FunctionType::get (results [0]->value ()->getType (), parameters_l, false));
				working->getInstList ().push_back (llvm::ReturnInst::Create (context, results [0]->value ()));
				add_function (module_a, blocks, type, false, values [routine_a->parameters]);
			}
			else
			{
				std::vector <llvm::Type *> return_types;
				for (auto i (results.begin ()), j (results.end ()); i != j; ++i)
				{
					return_types.push_back ((*i)->value ()->getType ());
				}
				auto return_type (llvm::StructType::get (context, return_types, false));
				auto type (llvm::FunctionType::get (return_type, parameters_l, false));
				auto struct_l (new llvm::AllocaInst (return_type));
				working->getInstList ().push_back (struct_l);
				unsigned int position (0);
				for (auto i (results.begin ()), j (results.end ()); i != j; ++i, ++position)
				{
					working->getInstList ().push_back (llvm::InsertElementInst::Create (struct_l, (*i)->value (), llvm::ConstantInt::getIntegerValue (llvm::Type::getInt32Ty (context), llvm::APInt (position, 32))));
				}
				working->getInstList ().push_back (llvm::ReturnInst::Create (context, struct_l));
				add_function (module_a, blocks, type, false, values [routine_a->parameters]);
			}
		}
	}
}

void lambda_p_llvm_io::routine::add_arguments (std::vector <boost::shared_ptr <lambda_p_llvm::value::node>> & arguments, llvm::Function * function)
{
	for (auto i (arguments.begin ()), j (arguments.end ()); i != j; ++i)
	{
		auto argument (boost::dynamic_pointer_cast <lambda_p_llvm::argument::node> (*i));
		assert (argument.get () != nullptr);
		function->getArgumentList ().push_back (argument->argument ());
	}
}

void lambda_p_llvm_io::routine::add_function (boost::shared_ptr <lambda_p_llvm::module::node> module_a, std::vector <llvm::BasicBlock *> & blocks, llvm::FunctionType * type, bool multi, std::vector <boost::shared_ptr <lambda_p_llvm::value::node>> & arguments)
{
	auto function (llvm::Function::Create (type, llvm::GlobalValue::ExternalLinkage));
	function->getArgumentList ().clear ();
	add_arguments (arguments, function);
	for (auto i (blocks.begin ()), j (blocks.end ()); i != j; ++i)
	{
		function->getBasicBlockList ().push_back (*i);
	}
	module_a->module->getFunctionList ().push_back (function);
	result = boost::make_shared <lambda_p_llvm::function::node> (function, multi);
}