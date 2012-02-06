#pragma once

#include <boost/shared_ptr.hpp>

#include <map>

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
	namespace function_pointer
	{
		class node;
	}
	namespace module
	{
		class node;
	}
}
namespace lambda_p_llvm_io
{
	class cluster_types
	{
	public:
		cluster_types (boost::shared_ptr <lambda_p::errors::error_target> errors_a, boost::shared_ptr <lambda_p::cluster> cluster_a, boost::shared_ptr <lambda_p_llvm::module::node> module_a);
		std::map <boost::shared_ptr <lambda_p::routine>, boost::shared_ptr <lambda_p_llvm::function_pointer::node>> routines;
	};
}

