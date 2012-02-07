#pragma once

#include <lambda_p/node.h>

#include <boost/shared_ptr.hpp>

namespace llvm
{
	class Value;
}
namespace lambda_p_llvm
{
	namespace type
	{
		class node;
	}
	namespace value
	{
		class node : public lambda_p::node
		{
		public:
			node (llvm::Value * value_a, boost::shared_ptr <lambda_p_llvm::type::node> type_a);
			llvm::Value * value ();
			boost::shared_ptr <lambda_p_llvm::type::node> type;
		protected:
			llvm::Value * value_m;
		};
	}
}

