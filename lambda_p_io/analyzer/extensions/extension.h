#pragma once

#include <boost/shared_ptr.hpp>

namespace lambda_p
{
	namespace errors
	{
		class error_target;
	}
}
namespace lambda_p_io
{
	namespace analyzer
	{
		class expression;
		namespace extensions
		{
			class extension
			{
			public:
				virtual void operator () (boost::shared_ptr <lambda_p::errors::error_target> errors_a, lambda_p_io::analyzer::expression & expression_a) = 0;
			};
		}
	}
}

