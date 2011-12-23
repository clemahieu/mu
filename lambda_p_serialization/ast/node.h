#pragma once

#include <string>

namespace lambda_p_serialization
{
	namespace ast
	{
		enum node_ids
		{
			expression,
			naming
		};
		class node
		{
		public:
			virtual lambda_p_serialization::ast::node_ids node_id () = 0;
			virtual std::wstring name () = 0;
		};
	}
}

