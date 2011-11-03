#include "assemble_binder.h"

#include <lambda_p/binder/node_list.h>
#include <lambda_p/core/statement.h>
#include <lambda_p/core/association.h>
#include <lambda_p/errors/error_list.h>
#include <lambda_p_kernel/adata.h>
#include <lambda_p_llvm/module.h>

#include <llvm/Assembly/Parser.h>
#include <llvm/Support/SourceMgr.h>

lambda_p_llvm::assemble_binder::assemble_binder (llvm::LLVMContext & context_a)
	: context (context_a)
{
}

void lambda_p_llvm::assemble_binder::bind (lambda_p::core::statement * statement, lambda_p::binder::node_list & nodes, lambda_p::errors::error_list & problems)
{
	check_count (1, 1, statement, problems);
	if (problems.errors.empty ())
	{
		boost::shared_ptr <lambda_p_kernel::adata> data (boost::dynamic_pointer_cast <lambda_p_kernel::adata> (nodes [statement->association->references [0]]));
		if (data.get () != nullptr)
		{
			llvm::SMDiagnostic diagnostic;
			llvm::Module * module (llvm::ParseAssemblyString (data->string.c_str (), nullptr, diagnostic, context));
			if (module != nullptr)
			{
				boost::shared_ptr <lambda_p_llvm::module> mod (new lambda_p_llvm::module (module)); 
				nodes [statement->association->declarations [0]] = mod;
			}
			else
			{
				std::string amessage (diagnostic.getMessage ());
				std::wstring message (L"Unable to assemble data:\n");
				std::copy (amessage.begin (), amessage.end (), message.end ());
				add_error (message, problems);
			}
		}
		else
		{
			unexpected_binder_type_error (0, L"adata", problems);
		}
	}
}

std::wstring lambda_p_llvm::assemble_binder::binder_name ()
{
	return std::wstring (L"assemble_binder");
}