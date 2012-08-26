#pragma once

#include <mu/io/ast/node.h>

namespace mu
{
	namespace io
	{
		namespace ast
		{
			class expression;
			namespace debugging
			{
				class stream;
			}
			class cluster : public mu::io::ast::node
			{
			public:
				cluster ();
				cluster (mu::io::context context_a);
				void operator () (mu::io::ast::visitor * visitor_a) override;
				mu::string name () override;
				mu::vector <mu::io::ast::expression *> expressions;
			};
		}
	}
}

