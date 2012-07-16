#pragma once

#include <mu/core/node.h>
#include <mu/io/debugging/context.h>

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
				node (mu::io::debugging::context context_a);
				virtual void operator () (mu::io::ast::visitor * visitor_a) = 0;
				virtual mu::string name () = 0;
				mu::io::debugging::context context;
			};
		}
	}
}
