#pragma once

#include <mu/io/analyzer/extensions/extension.h>

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
					global (mu::core::node * node_a);
					mu::core::node * node;
                    bool operator () () override;
					void operator () (mu::core::errors::error_target * errors_a, mu::io::analyzer::expression & expression_a, mu::string remaining) override;
				};
			}
		}
	}
}
