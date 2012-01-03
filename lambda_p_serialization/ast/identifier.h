#pragma once

#include <lambda_p_serialization/ast/node.h>

namespace lambda_p_serialization
{
	namespace ast
	{
		class identifier : public lambda_p_serialization::ast::node
		{
		public:
			identifier (std::wstring string_a);
			std::wstring name () override;
			void operator () (lambda_p_serialization::ast::visitor * visitor_a) override;
			std::wstring string;
		};
	}
}

