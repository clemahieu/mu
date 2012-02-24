#pragma once

#include <io/ast/node.h>

namespace mu
{
	namespace io
	{
		namespace ast
		{
			class parameters : public mu::io::ast::node
			{
			public:
				parameters (mu::core::context context_a);
				std::wstring name () override;
				void operator () (mu::io::ast::visitor * visitor_a) override;
			};
		}
	}
}
