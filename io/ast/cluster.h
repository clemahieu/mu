#pragma once

#include <core/node.h>

#include <vector>

#include <boost/shared_ptr.hpp>

namespace mu
{
	namespace io
	{
		namespace ast
		{
			class expression;
			class cluster : public mu::core::node
			{
			public:
				std::vector <boost::shared_ptr <mu::io::ast::expression>> expressions;
			};
		}
	}
}

