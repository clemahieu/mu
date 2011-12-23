#pragma once

#include <lambda_p_serialization/ast/node.h>

namespace lambda_p_serialization
{
	namespace ast
	{
		class naming : public lambda_p_serialization::ast::node
		{
		public:
			lambda_p_serialization::ast::node_ids node_id () override;
			std::wstring name () override;
		};
	}
}

