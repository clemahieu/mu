#pragma once

#include <mu/core/node.h>
#include <mu/core/context.h>

#include <string>

namespace mu
{
	namespace io
	{
		namespace ast
		{
			class visitor;
			class node : public mu::core::node
			{
			public:
                virtual ~node ();
				node (mu::core::context context_a);
				virtual void operator () (mu::io::ast::visitor * visitor_a) = 0;
				virtual std::wstring name () = 0;
				mu::core::context context;
			};
		}
	}
}
