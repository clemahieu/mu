#pragma once

#include <mu/io/ast/node.h>

#include <vector>

#include <boost/shared_ptr.hpp>

namespace mu
{
	namespace io
	{
		namespace ast
		{
			class expression;
			namespace debugging
			{
				class stream;
			}
			class cluster : public mu::io::ast::node
			{
			public:
				cluster ();
				cluster (mu::io::debugging::context context_a);
				void operator () (mu::io::ast::visitor * visitor_a) override;
				std::wstring name () override;
				std::vector <boost::shared_ptr <mu::io::ast::expression>> expressions;
			};
		}
	}
}

