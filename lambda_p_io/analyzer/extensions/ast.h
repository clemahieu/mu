#pragma once

#include <lambda_p_io/analyzer/extensions/extension.h>

namespace lambda_p_io
{
	namespace ast
	{
		class node;
		class cluster;
	}
	namespace analyzer
	{
		namespace extensions
		{
			class ast : public lambda_p_io::analyzer::extensions::extension
			{
			public:
				void operator () (boost::shared_ptr <lambda_p::errors::error_target> errors_a, lambda_p_io::analyzer::expression & expression_a) override;
				boost::shared_ptr <lambda_p_io::ast::cluster> core (boost::shared_ptr <lambda_p::errors::error_target> errors_a, boost::shared_ptr <lambda_p_io::ast::node> node_a);
			};
		}
	}
}

