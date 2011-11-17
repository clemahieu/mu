#include "compile.h"

#include <lambda_p/binder/binder_implementor.h>
#include <lambda_p_llvm/module.h>
#include <lambda_p_kernel/adata.h>

#include <llvm/Target/TargetRegistry.h>
#include <llvm/Support/Host.h>
#include <llvm/Target/TargetData.h>
#include <llvm/Target/TargetMachine.h>
#include <llvm/PassManager.h>
#include <llvm/Support/FormattedStream.h>
#include <llvm/Support/raw_ostream.h>

void lambda_p_llvm::compile::bind (lambda_p::core::statement * statement, lambda_p::binder::list & nodes, lambda_p::errors::error_list & problems)
{
	check_count (0, 2, statement, problems);
	if (problems.errors.empty ())
	{
		auto module (boost::dynamic_pointer_cast <lambda_p_llvm::module> (nodes [statement->association->references [0]]));
		check_binder (module, 0, L"module", problems);
		auto name (boost::dynamic_pointer_cast <lambda_p_kernel::adata> (nodes [statement->association->references [1]]));
		check_binder (name, 1, L"adata", problems);
		if (problems.errors.empty ())
		{
			std::string error;
			std::string triple (llvm::sys::getHostTriple ());
			llvm::Target const * target (llvm::TargetRegistry::lookupTarget (triple, error));
			if (error.empty ())
			{
				llvm::TargetMachine * machine (target->createTargetMachine (triple, std::string ()));
				llvm::TargetData const * data (machine->getTargetData ());
				llvm::PassManager manager;
				manager.add (new llvm::TargetData (*data));
				std::string error_info;
				llvm::formatted_raw_ostream stream (llvm::raw_fd_ostream (name->string.c_str (), error_info));
				if (error_info.empty ())
				{
					machine->addPassesToEmitFile (manager, stream, llvm::TargetMachine::CodeGenFileType::CGFT_ObjectFile, llvm::CodeGenOpt::None);
					manager.run (*module->module_m);
				}
				else
				{
					std::wstring message (error_info.begin (), error_info.end ());
					add_error (message, problems);
				}
			}
			else
			{
				std::wstring message (error.begin (), error.end ());
				add_error (message, problems);
			}
		}
	}
}

std::wstring lambda_p_llvm::compile::binder_name ()
{
	return std::wstring (L"compile");
}