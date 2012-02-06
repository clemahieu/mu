#pragma once

#include <boost/shared_ptr.hpp>

namespace lambda_p
{
	class cluster;
	class routine;
	namespace errors
	{
		class error_target;
	}
}
namespace lambda_p_llvm
{
	class cluster;
	namespace module
	{
		class node;
	}
	namespace function_pointer
	{
		class node;
	}
}
namespace lambda_p_llvm_io
{
	class cluster
	{
	public:
		cluster (boost::shared_ptr <lambda_p::errors::error_target> errors_a, boost::shared_ptr <lambda_p::cluster> cluster_a, boost::shared_ptr <lambda_p_llvm::module::node> module_a);
		boost::shared_ptr <lambda_p_llvm::cluster> result;
		std::map <boost::shared_ptr <lambda_p::routine>, boost::shared_ptr <lambda_p_llvm::function_pointer::node>> routines;
	};
}

