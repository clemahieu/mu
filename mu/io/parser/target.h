#pragma once

#include <boost/shared_ptr.hpp>

namespace mu
{
	namespace io
	{
		namespace ast
		{
			class expression;
		}
		namespace parser
		{
			class target
			{
			public:
				virtual void operator () (boost::shared_ptr <mu::io::ast::expression> expression_a) = 0;
			};
		}
	}
}