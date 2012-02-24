#pragma once

#include <core/node.h>

#include <vector>

#include <boost/shared_ptr.hpp>

namespace lambda_p_io
{
	namespace ast
	{
		class expression;
		class cluster : public mu::core::node
		{
		public:
			std::vector <boost::shared_ptr <lambda_p_io::ast::expression>> expressions;
		};
	}
}

