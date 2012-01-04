#pragma once

#include <string>

namespace lambda_p_io
{
	namespace ast
	{
		class visitor;
		class node
		{
		public:
			virtual void operator () (lambda_p_io::ast::visitor * visitor_a) = 0;
			virtual std::wstring name () = 0;
		};
	}
}

