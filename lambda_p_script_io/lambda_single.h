#pragma once

#include <lambda_p_io/analyzer/extensions/extension.h>

namespace lambda_p
{
	class cluster;
}
namespace lambda_p_script_io
{
	class lambda_single : public lambda_p_io::analyzer::extensions::extension
	{
	public:
		void operator () (boost::shared_ptr <lambda_p::errors::error_target> errors_a, lambda_p_io::analyzer::expression & expression_a) override;
		void add (boost::shared_ptr <lambda_p::errors::error_target> errors_a, lambda_p_io::analyzer::expression & expression_a, boost::shared_ptr <lambda_p::cluster> cluster_a);
	};
}

