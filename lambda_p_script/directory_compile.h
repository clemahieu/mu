#pragma once

#include <lambda_p/binder/binder.h>

#include <boost/filesystem/operations.hpp>

namespace lambda_p_kernel
{
	class package;
	class directory_compile : public lambda_p::binder::binder
	{
	public:
		void bind (lambda_p::core::statement * statement, lambda_p::binder::list & nodes, lambda_p::errors::error_list & problems) override;
		void package_directory (lambda_p::errors::error_list & problems, boost::shared_ptr <lambda_p_kernel::package> & package, boost::filesystem3::directory_iterator & directory);
		std::wstring binder_name () override;
	};
}

