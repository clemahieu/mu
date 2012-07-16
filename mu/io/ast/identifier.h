#pragma once

#include <mu/io/ast/node.h>

namespace mu
{
	namespace io
	{
		namespace ast
		{
			class identifier : public mu::io::ast::node
			{
			public:
				identifier (mu::io::debugging::context context_a, mu::string string_a);
				mu::string name () override;
				void operator () (mu::io::ast::visitor * visitor_a) override;
				mu::string string;
			};
		}
	}
}
