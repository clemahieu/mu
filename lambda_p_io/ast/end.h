#pragma once

#include <lambda_p/context.h>
#include <lambda_p_io/ast/node.h>

namespace lambda_p_io
{
	namespace ast
	{
		class end : public lambda_p_io::ast::node
		{
		public:
			end (lambda_p::context context_a);
			void operator () (lambda_p_io::ast::visitor * visitor_a) override;
			std::wstring name () override;
		};
	}
}

