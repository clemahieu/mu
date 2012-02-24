#pragma once

#include <io/ast/node.h>

namespace mu
{
	namespace io
	{
		namespace ast
		{
			class identifier : public mu::io::ast::node
			{
			public:
				identifier (mu::core::context context_a, std::wstring string_a);
				std::wstring name () override;
				void operator () (mu::io::ast::visitor * visitor_a) override;
				std::wstring string;
			};
		}
	}
}
