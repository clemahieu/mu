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
namespace lambda_p_llvm
{
	namespace value
	{
		class node;
	}
	class operation : public lambda_p::node
	{
	public:
		virtual void operator () (boost::shared_ptr <lambda_p::errors::error_target> errors_a, llvm::BasicBlock * & context_a, lambda_p::segment <boost::shared_ptr <lambda_p::node>> parameters_a, std::vector <boost::shared_ptr <lambda_p::node>> & results_a) = 0;
		bool check_size (boost::shared_ptr <lambda_p::errors::error_target> errors_a, size_t expected_a, size_t actual_a);
		void invalid_type (boost::shared_ptr <lambda_p::errors::error_target> errors_a, size_t position);
	};
}

