#pragma once

#include <core/context.h>
#include <io/ast/node.h>

namespace mu
{
	namespace io
	{
		namespace ast
		{
			class end : public mu::io::ast::node
			{
			public:
				end (mu::core::context context_a);
				void operator () (mu::io::ast::visitor * visitor_a) override;
				std::wstring name () override;
			};
		}
	}
}
