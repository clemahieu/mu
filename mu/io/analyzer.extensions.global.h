#pragma once

#include <mu/io/analyzer.extensions.extension.h>

#include <boost/shared_ptr.hpp>

namespace mu
{
	namespace core
	{
		class node;
	}
	namespace io
	{
		namespace analyzer
		{
			namespace extensions
			{
				class global : public mu::io::analyzer::extensions::extension
				{
				public:
					global (boost::shared_ptr <mu::core::node> node_a);
					boost::shared_ptr <mu::core::node> node;
					void operator () (boost::shared_ptr <mu::core::errors::error_target> errors_a, mu::io::analyzer::expression & expression_a) override;
				};
			}
		}
	}
}
