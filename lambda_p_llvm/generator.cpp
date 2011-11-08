#include "generator.h"

#include <lambda_p/core/statement.h>
#include <lambda_p/core/association.h>
#include <lambda_p/binder/list.h>
#include <lambda_p_llvm/type.h>
#include <lambda_p/core/routine.h>
#include <lambda_p_llvm/generation_context.h>
#include <lambda_p_kernel/bind_procedure.h>
#include <lambda_p/binder/list.h>
#include <lambda_p/errors/error_list.h>
#include <lambda_p_llvm/module.h>
#include <lambda_p_llvm/value.h>
#include <lambda_p_llvm/type_inference.h>
#include <lambda_p_kernel/apply.h>
#include <lambda_p_llvm/generator_value.h>

#include <llvm/Function.h>
#include <llvm/DerivedTypes.h>
#include <llvm/Module.h>
#include <llvm/Instructions.h>
#include <llvm/Argument.h>

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
			std::vector <llvm::Type const *> parameters;
			llvm::BasicBlock * block (llvm::BasicBlock::Create (module->module_m->getContext ()));
			boost::shared_ptr <lambda_p::binder::list> type_arguments (new lambda_p::binder::list);
			size_t position (0);
			for (auto i = list->nodes.begin (); i != list->nodes.end (); ++i, ++position)
			{
				auto instance (*i);
				auto type (boost::dynamic_pointer_cast <lambda_p_llvm::type> (instance));
				if (type.get () != nullptr)
				{
					parameters.push_back (type->type_m);
					if (type->type_m->isVoidTy ())
					{
						type_arguments->operator[] (position) = boost::shared_ptr <lambda_p_llvm::type_inference> (new lambda_p_llvm::type_inference (llvm::Type::getInt1Ty (module->module_m->getContext ())));
					}
					else
					{
						type_arguments->operator[] (position) = boost::shared_ptr <lambda_p_llvm::type_inference> (new lambda_p_llvm::type_inference (type->type_m));
					}
				}
				else
				{
					auto value (boost::dynamic_pointer_cast <lambda_p_llvm::value> (instance));
					if (value.get () != nullptr)
					{
						llvm::Function * function (llvm::dyn_cast <llvm::Function> (value->value_m));
						llvm::Type const * value_type (function != nullptr ? function->getFunctionType () : value->type ());
						type_arguments->operator[] (position) = boost::shared_ptr <lambda_p_llvm::type_inference> (new lambda_p_llvm::type_inference (value_type));
					}
					else
					{
						unexpected_binder_type_error (position, L"value or type", problems);
					}
				}
			}
			if (problems.errors.empty ())
			{
				lambda_p_kernel::apply apply;
				lambda_p::binder::list return_type;
				apply.core (routine, *type_arguments, problems, return_type);
				if (problems.errors.empty ())
				{
					auto function_type (llvm::FunctionType::get (boost::dynamic_pointer_cast <lambda_p_llvm::type_inference> (return_type [0])->type, parameters, false));
					auto llvm_function (llvm::Function::Create (function_type, llvm::GlobalValue::ExternalLinkage));
					module->module_m->getFunctionList ().push_back (llvm_function);
					auto block (llvm::BasicBlock::Create (module->module_m->getContext ()));
					llvm_function->getBasicBlockList ().push_back (block);
					auto function (boost::shared_ptr <lambda_p_llvm::value> (new lambda_p_llvm::value (llvm_function)));
					auto actual_parameters (boost::shared_ptr <lambda_p::binder::list> (new lambda_p::binder::list));
					auto arguments (llvm_function->arg_begin ());
					size_t position (0);					
					for (auto i = list->nodes.begin (); i != list->nodes.end (); ++i, ++position)
					{
						auto val (boost::dynamic_pointer_cast <lambda_p_llvm::value> (*i));
						if (val.get () == nullptr)
						{
							actual_parameters->operator[] (position) = boost::shared_ptr <lambda_p_llvm::generator_value> (new lambda_p_llvm::generator_value (arguments, block));
							++arguments;
						}
						else
						{
							actual_parameters->operator[] (position) = boost::shared_ptr <lambda_p_llvm::generator_value> (new lambda_p_llvm::generator_value (val->value_m, block));
						}
					}
					lambda_p_kernel::apply apply;
					lambda_p::binder::list return_value;
					apply.core (routine, *actual_parameters, problems, return_value);
					if (problems.errors.empty ())
					{
						boost::shared_ptr <lambda_p_llvm::generator_value> value (boost::dynamic_pointer_cast <lambda_p_llvm::generator_value> (return_value [0]));
						if (value->value->getType ()->isVoidTy ())
						{
							block->getInstList ().push_back (llvm::ReturnInst::Create (module->module_m->getContext ()));
						}
						else
						{
							block->getInstList ().push_back (llvm::ReturnInst::Create (module->module_m->getContext (), value->value));
						}
						nodes [statement->association->declarations [0]] = function;
					}
				}
			}
		}
	}
}

std::wstring lambda_p_llvm::generator::binder_name ()
{
	return std::wstring (L"generator");
}
