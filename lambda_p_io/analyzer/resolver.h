#pragma once

#include <boost/shared_ptr.hpp>

namespace lambda_p
{
	class expression;
}
namespace lambda_p_io
{
	namespace analyzer
	{
		class unresolved;
		class resolver
		{
		public:
			resolver (boost::shared_ptr <lambda_p_io::analyzer::unresolved> unresolved_a, boost::shared_ptr <lambda_p::expression> expression_a);
			boost::shared_ptr <lambda_p_io::analyzer::unresolved> unresolved;
			boost::shared_ptr <lambda_p::expression> expression;
			size_t index;
		};
	}
}

