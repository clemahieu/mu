#pragma once

#include <lambda_p/node.h>

#include <boost/shared_ptr.hpp>

namespace lambda_p_llvm_wrapper
{
	namespace function
	{
		class node;
	}
}
namespace lambda_p_llvm_io
{
	class expression;
	class dynamic_function : public lambda_p::node
	{
	public:
		virtual boost::shared_ptr <lambda_p_llvm_wrapper::function::node> operator () (lambda_p_llvm_io::expression & expression_a) = 0;
		std::wstring name () override;
	};
}

