#pragma once

#include <boost/shared_ptr.hpp>

#include <lambda_p_script/segment.h>

namespace llvm
{
	class BasicBlock;
}
namespace lambda_p
{
	class node;
	namespace errors
	{
		class error_target;
	}
}
namespace lambda_p_llvm
{
	namespace value
	{
		class node;
	}
	class operation
	{
	public:
		virtual void operator () (boost::shared_ptr <lambda_p::errors::error_target> errors_a, llvm::BasicBlock * & context_a, lambda_p_script::segment <boost::shared_ptr <lambda_p::node>> parameters_a, std::vector <boost::shared_ptr <lambda_p_llvm::value::node>> & results_a) = 0;
	};
}

