#pragma once

#include <lambda_p_io/analyzer/extension.h>

namespace lambda_p_script
{
	namespace string
	{
		class extension : public lambda_p_io::analyzer::extension
		{
		public:
			void operator () (lambda_p_io::analyzer::expression & expression_a) override;
		};
	}
}
