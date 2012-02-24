#pragma once

#include <lambda_p_io/ast/node.h>

namespace lambda_p_io
{
	namespace ast
	{
		class parameters : public lambda_p_io::ast::node
		{
		public:
			parameters (mu::core::context context_a);
			std::wstring name () override;
			void operator () (lambda_p_io::ast::visitor * visitor_a) override;
		};
	}
}

