#pragma once

#include <mu/io/analyzer/extensions/extension.h>

namespace mu
{
	namespace io
	{
		namespace ast
		{
			class node;
			class cluster;
		}
	}
	namespace script
	{
		namespace ast
		{
			class extension : public mu::io::analyzer::extensions::extension
			{
			public:
                bool operator () () override;
				void operator () (mu::core::errors::error_target & errors_a, mu::io::analyzer::expression & expression_a, mu::string remaining) override;
				mu::io::ast::cluster * core (mu::core::errors::error_target & errors_a, mu::io::ast::node * node_a);
			};
		}
	}
}
