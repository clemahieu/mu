#include "module_get_function.h"

#include <lambda_p/errors/error_list.h>
#include <lambda_p_llvm/module.h>
#include <lambda_p/core/statement.h>
#include <lambda_p/core/association.h>
#include <lambda_p/binder/list.h>
#include <lambda_p_kernel/adata.h>
#include <lambda_p_llvm/value.h>

#include <llvm/Module.h>

#include <sstream>

void lambda_p_llvm::module_get_function::bind (lambda_p::core::statement * statement, lambda_p::binder::list & nodes, lambda_p::errors::error_list & problems)
{
	check_count (1, 2, statement, problems);
	if (problems.errors.empty ())
	{
		boost::shared_ptr <lambda_p_llvm::module> module (boost::dynamic_pointer_cast <lambda_p_llvm::module> (nodes [statement->association->references [0]]));
		check_binder (module, 0, L"module", problems);
		boost::shared_ptr <lambda_p_kernel::adata> name (boost::dynamic_pointer_cast <lambda_p_kernel::adata> (nodes [statement->association->references [1]]));
		check_binder (name, 1, L"adata", problems);
		if (problems.errors.empty ())
		{
			llvm::Function * function (module->module_m->getFunction (name->string));
			if (function != nullptr)
			{
				boost::shared_ptr <lambda_p_llvm::value> function (new lambda_p_llvm::value (function));
				nodes [statement->association->declarations [0]] = function;
			}
			else
			{
				std::wstringstream message;
				message << L"No function named: ";
				std::wstring wname;
				std::copy (name->string.begin (), name->string.end (), wname.begin ());
				message << wname;
				message << L" in module";
				add_error (message.str (), problems);
			}
		}
	}
}

std::wstring lambda_p_llvm::module_get_function::binder_name ()
{
	return std::wstring (L"module_get_function");
}