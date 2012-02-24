#pragma once

#include <core/node.h>
#include <core/context.h>

#include <string>

namespace lambda_p_io
{
	namespace ast
	{
		class visitor;
		class node : public mu::core::node
		{
		public:
			node (mu::core::context context_a);
			virtual void operator () (lambda_p_io::ast::visitor * visitor_a) = 0;
			virtual std::wstring name () = 0;
			mu::core::context context;
		};
	}
}

