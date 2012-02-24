#pragma once

#include <boost/shared_ptr.hpp>

namespace mu
{
	namespace core
	{
		namespace errors
		{
			class error_target;
		}
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
				virtual void operator () (boost::shared_ptr <mu::core::errors::error_target> errors_a, lambda_p_io::analyzer::expression & expression_a) = 0;
			};
		}
	}
}

