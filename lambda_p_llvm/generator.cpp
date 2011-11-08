#include "generator.h"

#include <lambda_p/core/statement.h>
#include <lambda_p/core/association.h>
#include <lambda_p/binder/list.h>
#include <lambda_p_llvm/type.h>
#include <lambda_p_llvm/fo_value.h>
#include <lambda_p/core/routine.h>
#include <lambda_p_llvm/generation_context.h>
#include <lambda_p_kernel/bind_procedure.h>
#include <lambda_p/binder/list.h>
#include <lambda_p/errors/error_list.h>
#include <lambda_p_llvm/module.h>

#include <llvm/Function.h>
#include <llvm/DerivedTypes.h>
#include <llvm/Module.h>
#include <llvm/Instructions.h>

#include <sstream>

void lambda_p_llvm::generator::bind (lambda_p::core::statement * statement, lambda_p::binder::list & nodes, lambda_p::errors::error_list & problems)
{
	size_t position;
	check_count (1, 3, statement, problems);
	if (problems.errors.empty ())
	{
		auto module (boost::dynamic_pointer_cast <lambda_p_llvm::module> (nodes [statement->association->references [0]]));
		check_binder (module, 0, L"module", problems);
		auto routine (boost::dynamic_pointer_cast <lambda_p::core::routine> (nodes [statement->association->references [1]]));
		check_binder (routine, 1, L"routine", problems);
		auto list (boost::dynamic_pointer_cast <lambda_p::binder::list> (nodes [statement->association->references [2]]));
		check_binder (list, 2, L"list", problems);
		if (problems.errors.empty ())
		{
			lambda_p::binder::list nodes_l;
			std::vector <size_t> open_positions;
			std::vector <llvm::Type const *> parameters;
			position = 0;
			llvm::BasicBlock * block (llvm::BasicBlock::Create (module->module_m->getContext ()));
			lambda_p_llvm::generation_context context_l (module->module_m->getContext (), module->module_m, block);
			for (auto i = list->nodes.begin (); i != list->nodes.end (); ++i, ++position)
			{
				auto instance (*i);
				auto value (boost::dynamic_pointer_cast <lambda_p_llvm::fo_value> (instance));
				if (value.get () != nullptr)
				{
					nodes_l [position] = value;
				}
				else
				{
					unexpected_binder_type_error (position, L"fo_value", problems);
				}
			}
			if (problems.errors.empty ())
			{
				//llvm::Function * function (llvm::Function::Create (llvm::FunctionType::get (return_type->type_m, parameters, false), llvm::GlobalValue::ExternalLinkage));
				//function->getBasicBlockList ().push_back (block);
				//llvm::Function::arg_iterator i (function->arg_begin ());
				//std::vector <size_t >::iterator j (open_positions.begin ());
				//for (; i != function->arg_end (); ++i, ++j)
				//{
				//	nodes_l [*j] = boost::shared_ptr <lambda_p_llvm::fo_value> (new lambda_p_llvm::fo_value (&(*i)));
				//}
				//lambda_p_kernel::bind_procedure procedure (routine, nodes_l);
				//procedure (problems);
				//if (problems.errors.empty ())
				//{
				//	auto return_value (boost::dynamic_pointer_cast <lambda_p_llvm::fo_value> (nodes_l [routine->surface->references [0]]));
				//	if (return_value.get () != nullptr)
				//	{
				//		llvm::ReturnInst * ret (llvm::ReturnInst::Create (context_l.context, return_value->value));
				//		context_l.block->getInstList ().push_back (ret);
				//		context.module->getFunctionList ().push_back (function);
				//		boost::shared_ptr <lambda_p_llvm::fo_value> value (new lambda_p_llvm::fo_value (function));
				//		nodes [statement->association->declarations [0]] = value;
				//	}
				//	else
				//	{
				//		add_error (L"result value is not an llvm value", problems);
				//	}
				//}
			}
		}
	}
}

std::wstring lambda_p_llvm::generator::binder_name ()
{
	return std::wstring (L"generator");
}
