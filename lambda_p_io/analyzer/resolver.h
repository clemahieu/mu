#pragma once

#include <boost/shared_ptr.hpp>

namespace lambda_p
{
	class expression;
	class node;
}
namespace lambda_p_io
{
	namespace analyzer
	{
		class resolver
		{
		public:
			resolver (boost::shared_ptr <lambda_p::expression> unresolved_a, size_t position_a);
			void operator () (boost::shared_ptr <lambda_p::node> node_a);
			boost::shared_ptr <lambda_p::expression> unresolved;
			size_t position;
		};
	}
}

