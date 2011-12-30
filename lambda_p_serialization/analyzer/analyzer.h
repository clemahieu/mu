#pragma once

#include <boost/shared_ptr.hpp>

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
			void operator () (boost::shared_ptr <lambda_p_serialization::ast::node> node);
		};
	}
}

