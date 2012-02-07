#pragma once

#include <boost/shared_ptr.hpp>

namespace llvm
{
	class Type;
}
namespace lambda_p_llvm
{
	namespace context
	{
		class node;
	}
	namespace type
	{
		class node;
		class build
		{
		public:
			build (boost::shared_ptr <lambda_p_llvm::context::node> context_a, llvm::Type * type_a);
			boost::shared_ptr <lambda_p_llvm::type::node> type;
		};
	}
}

