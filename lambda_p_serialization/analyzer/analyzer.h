#pragma once

#include <boost/shared_ptr.hpp>
#include <boost/function.hpp>

namespace lambda_p
{
	namespace core
	{
		class routine;
	}
}
namespace lambda_p_serialization
{
	namespace ast
	{
		class node;
	}
	namespace analyzer
	{
		class analyzer
		{
		public:
			analyzer (boost::function <void (boost::shared_ptr <lambda_p::core::routine>)> target_a);
			void operator () (boost::shared_ptr <lambda_p_serialization::ast::node> node);
			boost::function <void (boost::shared_ptr <lambda_p::core::routine>)> target;
		};
	}
}

