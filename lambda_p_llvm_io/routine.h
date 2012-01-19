#pragma once

#include <boost/shared_ptr.hpp>

#include <lambda_p_script/segment.h>

namespace lambda_p
{
	class node;
	class routine;
	namespace errors
	{
		class error_target;
	}
}
namespace lambda_p_llvm
{
	namespace module
	{
		class node;
	}
	namespace function
	{
		class node;
	}
}
namespace lambda_p_llvm_io
{
	class routine
	{
	public:
		routine (boost::shared_ptr <lambda_p::errors::error_target> errors_a, boost::shared_ptr <lambda_p::routine> routine_a, boost::shared_ptr <lambda_p_llvm::module::node> module_a, lambda_p_script::segment <boost::shared_ptr <lambda_p::node>> parameters);
		boost::shared_ptr <lambda_p_llvm::function::node> result;
	};
}

