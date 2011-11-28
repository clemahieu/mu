#include "assemble_binder.h"

#include <lambda_p/binder/list.h>
#include <lambda_p/core/statement.h>
#include <lambda_p/core/association.h>
#include <lambda_p/errors/error_list.h>
#include <lambda_p_kernel/nodes/adata.h>
#include <lambda_p_llvm/module.h>
#include <lambda_p_llvm/context.h>

#include <llvm/Assembly/Parser.h>
#include <llvm/Support/SourceMgr.h>

#include <sstream>

void lambda_p_llvm::assemble_binder::bind (lambda_p::core::statement * statement, lambda_p::binder::list & nodes, lambda_p::errors::error_list & problems)
{
	check_count (1, 2, statement, problems);
	if (problems.errors.empty ())
	{
		boost::shared_ptr <lambda_p_kernel::nodes::adata> data (boost::dynamic_pointer_cast <lambda_p_kernel::nodes::adata> (nodes [statement->association->references [0]]));
		check_binder (data, 0, L"adata", problems);
		boost::shared_ptr <lambda_p_llvm::context> context (boost::dynamic_pointer_cast <lambda_p_llvm::context> (nodes [statement->association->references [1]]));
		check_binder (context, 1, L"context", problems);
		if (problems.errors.empty ())
		{
			llvm::SMDiagnostic diagnostic;
			llvm::Module * module (llvm::ParseAssemblyString (data->string.c_str (), nullptr, diagnostic, context->context_m));
			if (module != nullptr)
			{
				boost::shared_ptr <lambda_p_llvm::module> mod (new lambda_p_llvm::module (module)); 
				nodes [statement->association->declarations [0]] = mod;
			}
			else
			{
				std::wstringstream message;
				std::string amessage (diagnostic.getMessage ());
				std::wstring converted;
				converted.resize (amessage.size ());
				std::copy (amessage.begin (), amessage.end (), converted.begin ());
				message << L"Unable to assemble data:\n";
				message << converted;
				add_error (message.str (), problems);
			}
		}
	}
}

std::wstring lambda_p_llvm::assemble_binder::binder_name ()
{
	return std::wstring (L"assemble_binder");
}