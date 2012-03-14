#pragma once

#include <mu/io/debugging/context.h>
#include <mu/io/ast/node.h>

namespace mu
{
	namespace io
	{
		namespace ast
		{
			class end : public mu::io::ast::node
			{
			public:
				end (mu::io::debugging::context context_a);
				void operator () (mu::io::ast::visitor * visitor_a) override;
				std::wstring name () override;
			};
		}
	}
}
