#include "raw_fd_ostream_binder.h"

#include <lambda_p/binder/binder_implementor.h>
#include <lambda_p_kernel/nodes/adata.h>
#include <lambda_p_llvm/raw_fd_ostream.h>

#include <llvm/Support/raw_ostream.h>

#include <string>

void lambda_p_llvm::raw_fd_ostream_binder::bind (lambda_p::core::statement * statement, lambda_p::binder::list & nodes, lambda_p::errors::error_list & problems)
{
	check_count (1, 1, statement, problems);
	if (problems.errors.empty ())
	{
		auto name (boost::dynamic_pointer_cast <lambda_p_kernel::nodes::adata> (nodes [statement->association->references [0]]));
		check_binder (name, 0, L"adata", problems);
		if (problems.errors.empty ())
		{
			std::string error_info;
			auto stream (new llvm::raw_fd_ostream (name->string.c_str (), error_info));
			if (error_info.empty ())
			{
				nodes [statement->association->declarations [0]] = boost::shared_ptr <lambda_p_llvm::raw_fd_ostream> (new lambda_p_llvm::raw_fd_ostream (stream));
			}
			else
			{
				std::wstring message (error_info.begin (), error_info.end ());
				add_error (message, problems);

			}
		}
	}
}

std::wstring lambda_p_llvm::raw_fd_ostream_binder::binder_name ()
{
	return std::wstring (L"raw_fd_ostream");
}