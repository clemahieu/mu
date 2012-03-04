#pragma once

#include <mu/io/analyzer.extensions.extension.h>

namespace mu
{
	namespace core
	{
		class cluster;
	}
	namespace script_io
	{
		class lambda_single : public mu::io::analyzer::extensions::extension
		{
		public:
			void operator () (boost::shared_ptr <mu::core::errors::error_target> errors_a, mu::io::analyzer::expression & expression_a) override;
			void add (boost::shared_ptr <mu::core::errors::error_target> errors_a, mu::io::analyzer::expression & expression_a, boost::shared_ptr <mu::core::cluster> cluster_a);
		};
	}
}

