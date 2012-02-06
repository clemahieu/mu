#pragma once

#include <boost/shared_ptr.hpp>

#include <lambda_p/node.h>
#include <lambda_p/segment.h>

namespace llvm
{
	class BasicBlock;
}
namespace lambda_p
{
	namespace errors
	{
		class error_target;
	}
}
namespace lambda_p_llvm_io
{
	class target : public lambda_p::node
	{
	public:
		virtual void operator () (boost::shared_ptr <lambda_p::errors::error_target> errors_a, llvm::BasicBlock * & context_a, std::vector <boost::shared_ptr <lambda_p::node>> & arguments) = 0;
	};
}

