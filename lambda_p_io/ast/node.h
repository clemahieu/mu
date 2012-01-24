#pragma once

#include <lambda_p/context.h>

#include <string>

namespace lambda_p_io
{
	namespace ast
	{
		class visitor;
		class node
		{
		public:
			node (lambda_p::context context_a);
			virtual void operator () (lambda_p_io::ast::visitor * visitor_a) = 0;
			virtual std::wstring name () = 0;
			lambda_p::context context;
		};
	}
}

