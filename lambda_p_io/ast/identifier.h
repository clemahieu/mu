#pragma once

#include <lambda_p_io/ast/node.h>

namespace lambda_p_io
{
	namespace ast
	{
		class identifier : public lambda_p_io::ast::node
		{
		public:
			identifier (lambda_p::context context_a, std::wstring string_a);
			std::wstring name () override;
			void operator () (lambda_p_io::ast::visitor * visitor_a) override;
			std::wstring string;
		};
	}
}

