//
//  load_binder.cpp
//  lambda_p_llvm
//
//  Created by Colin LeMahieu on 9/24/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#define __STDC_LIMIT_MACROS
#define __STDC_CONSTANT_MACROS

#include <lambda_p_llvm/load_inst_binder.h>
#include <lambda_p/core/statement.h>
#include <lambda_p_llvm/generation_context.h>
#include <lambda_p/core/association.h>
#include <lambda_p/binder/list.h>
#include <lambda_p/errors/error_list.h>
#include <lambda_p_llvm/value.h>
#include <lambda_p_llvm/module.h>
#include <lambda_p_llvm/type.h>

#include <llvm/Type.h>
#include <llvm/Instructions.h>
#include <llvm/BasicBlock.h>
#include <llvm/Function.h>
#include <llvm/Module.h>

#include <sstream>

void lambda_p_llvm::load_inst_binder::bind (lambda_p::core::statement * statement, lambda_p::binder::list & nodes, lambda_p::errors::error_list & problems)
{
	check_count (1, 2, statement, problems);
	if (problems.errors.empty ())
	{
		auto module (boost::dynamic_pointer_cast <lambda_p_llvm::module> (nodes [statement->association->references [0]]));
		check_binder (module, 0, L"module", problems);
		auto type (boost::dynamic_pointer_cast <lambda_p_llvm::type> (nodes [statement->association->references [1]]));
		check_binder (type, 1, L"type", problems);
		if (problems.errors.empty ())
		{
			std::vector <llvm::Type const *> arguments;
			arguments.push_back (llvm::PointerType::get (type->type_m, 0));
			auto function (llvm::Function::Create (llvm::FunctionType::get (type->type_m, arguments, false), llvm::GlobalValue::ExternalLinkage));
			module->module_m->getFunctionList ().push_back (function);
			auto block (llvm::BasicBlock::Create (module->module_m->getContext ()));
			function->getBasicBlockList ().push_back (block);
			auto load (new llvm::LoadInst (function->arg_begin ()));
			block->getInstList ().push_back (load);
			block->getInstList ().push_back (llvm::ReturnInst::Create (module->module_m->getContext (), load));
			nodes [statement->association->declarations [0]] = boost::shared_ptr <lambda_p_llvm::value> (new lambda_p_llvm::value (function));
		}
    }
}

std::wstring lambda_p_llvm::load_inst_binder::binder_name ()
{
	return std::wstring (L"load_inst_binder");
}