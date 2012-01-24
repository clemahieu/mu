#pragma once

#include <lambda_p_io/analyzer/extensions/extension.h>

#include <boost/shared_ptr.hpp>

namespace lambda_p
{
	class routine;
}
namespace lambda_p_io
{
	namespace analyzer
	{
		namespace extensions
		{
			class lambda : public lambda_p_io::analyzer::extensions::extension
			{
			public:
				void operator () (boost::shared_ptr <lambda_p::errors::error_target> errors_a, lambda_p_io::analyzer::expression & expression_a) override;
				void add (lambda_p_io::analyzer::expression & expression_a, boost::shared_ptr <lambda_p::routine> routine_a);
			};
		}
	}
}

